#include "hspch.h"
#include "Memory.h"
#include "Platform/Assertions.h"

namespace Heist {

	MemoryManager::MemoryManager(uint32 stackSize) 
	{
		startPointer = malloc(stackSize);
		endPointer = (char*)startPointer + stackSize;

		marker = startPointer;
	}

	MemoryManager::~MemoryManager()
	{
		free(startPointer);
	}

	void* MemoryManager::Alloc(uint32 size_byte)
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