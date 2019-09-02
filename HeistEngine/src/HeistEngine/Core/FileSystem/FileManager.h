#pragma once

namespace Heist {

	struct FileManager
	{
		FileManager();
		~FileManager();

		static std::string ReadFile(const char* filePath);
		void WriteFile();
	};
}