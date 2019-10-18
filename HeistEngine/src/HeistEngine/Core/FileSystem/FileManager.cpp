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
			{ ShaderDataType::Float2, "Texture Coords" },
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

      if (material)
        return new Model3D(shader, material, vertexArray, true);
      else
        return new Model3D(shader, rawModel->rawMaterial, vertexArray, true);
		}

    if (material)
      return new Model3D(shader, material, vertexArray, false);
    else
      return new Model3D(shader, rawModel->rawMaterial, vertexArray, false);
	}

	RawModel3D FileManager::ReadOBJFile(const char* filePath, const char* fileName)
	{
		RawModel3D model;
		std::ifstream fileStream;

	char filePathAndName[50];
    std::strcpy(filePathAndName, filePath);
    std::strcat(filePathAndName, fileName);

		fileStream.open(filePathAndName);
		HS_CORE_ASSERT(!fileStream.fail(), "Cannot open file path: " + std::string(filePathAndName));

		std::string line;

		std::string tag, mtlFileName;
		real32 v1, v2, v3, v4, v5;
    bool useMtl = false;

		while (std::getline(fileStream, line)) {
			uint32 faceIndex = 0;
			std::stringstream sl(line);
			sl >> tag;
      if (tag == "mtllib") {
        useMtl = true;
        sl >> mtlFileName;
      }
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
					} else if (faceIndex == 2) {
						model.dataBuffer.push_back(model.textureCoord[(i - 1) * 2 + 0]);
						model.dataBuffer.push_back(model.textureCoord[(i - 1) * 2 + 1]);
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
			} else if (tag == "vt") {
				sl >> v1 >> v2;
				model.textureCoord.push_back(v1);
				model.textureCoord.push_back(v2);
			}
		}

		fileStream.close();

    if (useMtl) {
      std::string path(filePath);
      path.append(mtlFileName);
      std::shared_ptr<RawMaterial3D> mat = std::make_shared<RawMaterial3D>(ReadMTLFile(path.c_str()));
      model.SetRawMaterial(mat);
    }

		return model;
	}

	json FileManager::ReadJSON(const char* filePath)
	{
		std::string content = ReadFile(filePath);
		auto jsonContent = json::parse(content);

		return jsonContent;
	}

  RawMaterial3D FileManager::ReadMTLFile(const char* filePath) {
    RawMaterial3D material;
		std::ifstream fileStream;
		fileStream.open(filePath);
		HS_CORE_ASSERT(!fileStream.fail(), "Cannot open file path: " + std::string(filePath));

		std::string line;

		std::string tag;

		while (std::getline(fileStream, line)) {
			std::stringstream sl(line);
			sl >> tag;
			if (tag == "Ns") {
        real64 shininess;
        sl >> shininess;
        material.shininess = shininess;
			} else if (tag == "Ka") {
        real32 a1, a2, a3;
        sl >> a1 >> a2 >> a3;
        material.ambientColor = { a1, a2, a3 };
      } else if (tag == "Kd") {
        real32 d1, d2, d3;
        sl >> d1 >> d2 >> d3;
        material.diffuseColor = { d1, d2, d3 };
      } else if (tag == "Ks") {
        real32 s1, s2, s3;
        sl >> s1 >> s2 >> s3;
        material.specularColor = { s1, s2, s3 };
      } else if (tag == "illum") {
        int8 illum;
        sl >> illum;
        if (illum == 1) {
          material.specularHighlight = false;
        } else {
          material.specularHighlight = true;
        }
      }
    }
    fileStream.close();

    return material;
  }

	void FileManager::WriteFile() {
	}

	TextureData FileManager::ReadTexture(const char* texturePath) {
		int32 width, height, comp;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* img = stbi_load(texturePath, &width, &height, &comp, 4);

		if (!img) {
			HS_CORE_ERROR("Fail to load texture: {}", texturePath);
		} else {
			HS_CORE_TRACE("Texture loaded: {}", texturePath);
		}

		return {width, height, comp, img};
	}

}
