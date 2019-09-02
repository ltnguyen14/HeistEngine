#include "hspch.h"
#include "FileManager.h"
#include "Platform/Assertions.h"

namespace Heist {

	FileManager::FileManager() {
	}

	FileManager::~FileManager() {
	}

	std::string FileManager::ReadFile(const char* filePath) {
		char buf[256];
		GetCurrentDirectoryA(256, buf);
		std::cout << std::string(buf) + '\\' << std::endl;

		std::ifstream file(filePath);
		HS_CORE_ASSERT(!file.fail(), "Cannot open file path: " + std::string(filePath));
		std::string content;

		file.seekg(0, std::ios::end);
		content.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		content.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		return content;
	}

	void FileManager::WriteFile()
	{
	}

}