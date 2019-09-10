#pragma once
#include "Macro.h"

namespace Heist {
	
	class MemoryManager
	{
	public:
		static MemoryManager* Instance();

		void StartUp(uintmax stackSize_mb);
		void ShutDown();

		void* Alloc(uintmax size_byte);
		void ClearStack();

		void* marker;
		void* startPointer;
		void* endPointer;
		uintmax stackSize_mb;

	private:
		MemoryManager() {};
		MemoryManager(MemoryManager const&) {};
		MemoryManager& operator=(MemoryManager const&) {};

		static MemoryManager* g_memoryManager;
	};

}