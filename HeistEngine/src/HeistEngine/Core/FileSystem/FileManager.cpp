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

  std::shared_ptr<ModelCollection3D> FileManager::CreateModelFromRawData(const std::shared_ptr<RawModelCollection3D> rawModelColelction, const std::shared_ptr<Material3D> material, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture)
	{
		std::shared_ptr<ModelCollection3D> modelCollection = std::make_shared<ModelCollection3D>(ModelCollection3D());
		for (auto modelPair : rawModelColelction->models) {
			auto model = modelPair.second;
			std::shared_ptr<VertexArray> vertexArray(VertexArray::Create());

			// Verticies
			std::shared_ptr<VertexBuffer> vertexBuffer(
				VertexBuffer::Create(model->dataBuffer.data(), model->dataBuffer.size() * sizeof(model->dataBuffer[0]), model->verticiesNum)
			);
			BufferLayout bufferLayout({
				{ ShaderDataType::Float3, "Position" },
				{ ShaderDataType::Float2, "Texture Coords" },
				{ ShaderDataType::Float3, "Normals" },
				});
			vertexBuffer->SetLayout(bufferLayout);

			// Indicies
			vertexArray->AddVertexBuffer(vertexBuffer);
			if (model->indicies.size() > 0) {
				std::shared_ptr<IndexBuffer> indexBuffer(
					IndexBuffer::Create(model->indicies.data(), model->indicies.size())
				);
				vertexArray->SetIndexBuffer(indexBuffer);
			}

			if (material)
				modelCollection->models.push_back(std::make_shared<Model3D>(Model3D(shader, material, vertexArray, model->indicies.size() > 0)));
			else
				modelCollection->models.push_back(std::make_shared<Model3D>(Model3D(shader, model->rawMaterial, vertexArray, model->indicies.size() > 0)));
		}

		return modelCollection;
	}

  std::shared_ptr<RawModelCollection3D> FileManager::ReadOBJFile(const char* filePath, const char* fileName)
	{
    std::shared_ptr<RawModelCollection3D> collection = std::make_shared<RawModelCollection3D>(RawModelCollection3D());
		std::ifstream fileStream;

		std::vector<real32> verticies;
		std::vector<real32> normals;
		std::vector<real32> textureCoord;

    char filePathAndName[50];
    std::strcpy(filePathAndName, filePath);
    std::strcat(filePathAndName, fileName);

		fileStream.open(filePathAndName);
		HS_CORE_ASSERT(!fileStream.fail(), "Cannot open file path: " + std::string(filePathAndName));

		std::string line;

		std::string tag, mtlFileName;
		real32 v1, v2, v3, v4, v5;
		std::string currentObjectName;

    bool useMtl = false;

		while (std::getline(fileStream, line)) {
			uint32 faceIndex = 0;
			std::stringstream sl(line);
			sl >> tag;
      if (tag == "mtllib") {
        useMtl = true;
        sl >> mtlFileName;
      }

      if (tag == "o") {
        sl >> currentObjectName;
		collection->models[currentObjectName] = std::make_shared<RawModel3D>(RawModel3D());
      } else if (tag == "usemtl") {
        sl >> collection->models[currentObjectName]->materialName;
      } else if (tag == "v") {
				sl >> v1 >> v2 >> v3;
				verticies.push_back(v1);
				verticies.push_back(v2);
				verticies.push_back(v3);
			} else if (tag == "f") {
				for (uint64 i; sl >> i;) {
					faceIndex++;
					if (faceIndex == 1) { // indicies
						// model.indicies.push_back(i - 1); // obj index start at 1
						collection->models[currentObjectName]->dataBuffer.push_back(verticies[(i - 1) * 3 + 0]);
						collection->models[currentObjectName]->dataBuffer.push_back(verticies[(i - 1) * 3 + 1]);
						collection->models[currentObjectName]->dataBuffer.push_back(verticies[(i - 1) * 3 + 2]);
					} else if (faceIndex == 2) {
						collection->models[currentObjectName]->dataBuffer.push_back(textureCoord[(i - 1) * 2 + 0]);
						collection->models[currentObjectName]->dataBuffer.push_back(textureCoord[(i - 1) * 2 + 1]);
					} else if (faceIndex == 3) {
						collection->models[currentObjectName]->dataBuffer.push_back(normals[(i - 1) * 3 + 0]);
						collection->models[currentObjectName]->dataBuffer.push_back(normals[(i - 1) * 3 + 1]);
						collection->models[currentObjectName]->dataBuffer.push_back(normals[(i - 1) * 3 + 2]);
					}
					if (sl.peek() == '/' || sl.peek() == ' ') {
						if (sl.peek() == ' ')
							faceIndex = 0;
						sl.ignore();
					}
				}
				collection->models[currentObjectName]->verticiesNum += 3;
			} else if (tag == "vn") {
				sl >> v1 >> v2 >> v3;
				normals.push_back(v1);
				normals.push_back(v2);
				normals.push_back(v3);
			} else if (tag == "vt") {
				sl >> v1 >> v2;
				textureCoord.push_back(v1);
				textureCoord.push_back(v2);
			}
		}

		fileStream.close();

    if (useMtl) {
      std::string path(filePath);
      path.append(mtlFileName);
      std::unordered_map<std::string, std::shared_ptr<RawMaterial3D>> mat = ReadMTLFile(path.c_str());
      for (std::pair<const std::string, std::shared_ptr<RawModel3D>> model : collection->models) {
        model.second->SetRawMaterial(mat[model.second->materialName]);
      }
    }

		return collection;
	}

	json FileManager::ReadJSON(const char* filePath)
	{
		std::string content = ReadFile(filePath);
		auto jsonContent = json::parse(content);

		return jsonContent;
	}

  std::unordered_map<std::string, std::shared_ptr<RawMaterial3D>> FileManager::ReadMTLFile(const char* filePath) {
    std::unordered_map<std::string, std::shared_ptr<RawMaterial3D>> materials;
		std::ifstream fileStream;
		fileStream.open(filePath);
		HS_CORE_ASSERT(!fileStream.fail(), "Cannot open file path: " + std::string(filePath));

		std::string line;
		std::string tag;
    std::string currentMaterialIndex;

		while (std::getline(fileStream, line)) {
			std::stringstream sl(line);
			sl >> tag;

      if (tag == "newmtl") {
        sl >> currentMaterialIndex;
        materials[currentMaterialIndex] = std::make_shared<RawMaterial3D>(RawMaterial3D());
      } else if (tag == "Ns") {
        real64 shininess;
        sl >> shininess;
        materials[currentMaterialIndex]->shininess = shininess;
			} else if (tag == "Ka") {
        real32 a1, a2, a3;
        sl >> a1 >> a2 >> a3;
        materials[currentMaterialIndex]->ambientColor = { a1, a2, a3 };
      } else if (tag == "Kd") {
        real32 d1, d2, d3;
        sl >> d1 >> d2 >> d3;
        materials[currentMaterialIndex]->diffuseColor = { d1, d2, d3 };
      } else if (tag == "Ks") {
        real32 s1, s2, s3;
        sl >> s1 >> s2 >> s3;
        materials[currentMaterialIndex]->specularColor = { s1, s2, s3 };
      } else if (tag == "illum") {
        int8 illum;
        sl >> illum;
        if (illum == 1) {
          materials[currentMaterialIndex]->specularHighlight = false;
        } else {
          materials[currentMaterialIndex]->specularHighlight = true;
        }
      }
    }
    fileStream.close();

    return materials;
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
