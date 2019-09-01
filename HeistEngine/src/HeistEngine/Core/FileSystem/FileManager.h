#pragma once

namespace Heist {

	struct FileManager
	{
		FileManager();
		~FileManager();

		const char* ReadFile() const;
		void WriteFile();

	};


}