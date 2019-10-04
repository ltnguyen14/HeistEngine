#include "hspch.h"
#include "FileManager.h"
#include "Platform/Assertions.h"
#include "Platform/Assertions.h"

#define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image.h"

namespace Heist {

	TextureData::~TextureData() {
		if (img) {
			stbi_image_free(img);
		}
	}

	FileManager::FileManager() {
	}

	FileManager::~FileManager() {
	}

	std::string FileManager::ReadFile(const char* filePath) {
		std::ifstream file(filePath);
		HS_CORE_ASSERT(!file.fail(), "Cannot open file path: " + std::string(filePath));
		std::string content;

		file.seekg(0, std::ios::end);
		content.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		content.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		file.close();
		return content;
	}

	Model3D* FileManager::CreateModelFromRawData(RawModel3D* rawModel, const std::shared_ptr<Material3D> material, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture)
	{
		std::shared_ptr<VertexArray> vertexArray(VertexArray::Create());

		// Verticies
		HS_CORE_ASSERT(rawModel->verticies.size() > 0, "No verticies passed in");
		std::shared_ptr<VertexBuffer> vertexBuffer(
			VertexBuffer::Create(rawModel->dataBuffer.data(), rawModel->dataBuffer.size() * sizeof(rawModel->dataBuffer[0]), rawModel->verticiesNum) 
		);
		BufferLayout bufferLayout({
			{ ShaderDataType::Float3, "Position" },
			{ ShaderDataType::Float3, "Normals" },
			});
		vertexBuffer->SetLayout(bufferLayout);

		// Indicies
		vertexArray->AddVertexBuffer(vertexBuffer);
		if (rawModel->indicies.size() > 0) {
			std::shared_ptr<IndexBuffer> indexBuffer(
				IndexBuffer::Create(rawModel->indicies.data(), rawModel->indicies.size())
			);
			vertexArray->SetIndexBuffer(indexBuffer);
			return new Model3D(shader, material, texture, vertexArray, true);
		}

		return new Model3D(shader, material, texture, vertexArray, false);
	}

	RawModel3D FileManager::ReadOBJFile(const char* filePath)
	{
		RawModel3D model;
		std::ifstream fileStream;
		fileStream.open(filePath);
		HS_CORE_ASSERT(!fileStream.fail(), "Cannot open file path: " + std::string(filePath));

		std::string line;

		std::string tag;
		real32 v1, v2, v3, v4, v5;

		while (std::getline(fileStream, line)) {
			uint32 faceIndex = 0;
			std::stringstream sl(line);
			sl >> tag;
			if (tag == "v") {
				sl >> v1 >> v2 >> v3;
				model.verticies.push_back(v1);
				model.verticies.push_back(v2);
				model.verticies.push_back(v3);
			} else if (tag == "f") {
				for (uint64 i; sl >> i;) {
					faceIndex++;
					if (faceIndex == 1) { // indicies
						// model.indicies.push_back(i - 1); // obj index start at 1
						model.dataBuffer.push_back(model.verticies[(i - 1) * 3 + 0]);
						model.dataBuffer.push_back(model.verticies[(i - 1) * 3 + 1]);
						model.dataBuffer.push_back(model.verticies[(i - 1) * 3 + 2]);
					} else if (faceIndex == 3) {
						model.dataBuffer.push_back(model.normals[(i - 1) * 3 + 0]);
						model.dataBuffer.push_back(model.normals[(i - 1) * 3 + 1]);
						model.dataBuffer.push_back(model.normals[(i - 1) * 3 + 2]);
					}
					if (sl.peek() == '/' || sl.peek() == ' ') {
						if (sl.peek() == ' ')
							faceIndex = 0;
						sl.ignore();
					}
				}
				model.verticiesNum += 3;
			} else if (tag == "vn") {
				sl >> v1 >> v2 >> v3;
				model.normals.push_back(v1);
				model.normals.push_back(v2);
				model.normals.push_back(v3);
			}
		}

		fileStream.close();
		return model;
	}

	json FileManager::ReadJSON(const char* filePath)
	{
		std::string content = ReadFile(filePath);
		auto jsonContent = json::parse(content);

		return jsonContent;
	}

	void FileManager::WriteFile() {
	}

	TextureData FileManager::ReadTexture(const char* texturePath) {
		int32 width, height, comp;
		// stbi_set_flip_vertically_on_load(1);
		unsigned char* img = stbi_load(texturePath, &width, &height, &comp, 4);

		if (!img) {
			HS_CORE_ERROR("Fail to load texture: {}", texturePath);
		} else {
			HS_CORE_TRACE("Texture loaded: {}", texturePath);
		}
		
		return {width, height, comp, img};
	}

}