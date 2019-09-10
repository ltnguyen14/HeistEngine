#include "hspch.h"
#include "Memory.h"
#include "Platform/Assertions.h"

namespace Heist {

	void MemoryManager::StartUp(uintmax stackSize_mb) {
		this->stackSize_mb = stackSize_mb;
		HS_CORE_TRACE("Memory initialized with the size of {}MB", stackSize_mb);
		startPointer = malloc(stackSize_mb * 1024 * 1024);
		endPointer = (char*)startPointer + stackSize_mb * 1024 * 1024;

		marker = startPointer;
	}

	MemoryManager* MemoryManager::g_memoryManager = nullptr;

	MemoryManager* MemoryManager::Instance() {
		if (!g_memoryManager) {
			g_memoryManager = new MemoryManager();
		}

		return g_memoryManager;
	}

	void MemoryManager::ShutDown()
	{
		free(startPointer);
	}

	void* MemoryManager::Alloc(uintmax size_byte)
	{
		HS_CORE_ASSERT((char*)marker + size_byte < endPointer, "Not enough dynamic memory to allocate!");
		void* returnPointer = marker;
		marker = (char*)marker + size_byte;
		return returnPointer;
	}

	void MemoryManager::ClearStack()
	{
		marker = startPointer;
	}

}