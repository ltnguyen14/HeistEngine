#pragma once
#include "Macro.h"

namespace Heist {
	
	class MemoryManager
	{
	public:
		MemoryManager(uint32 stackSize);
		~MemoryManager();

		void* Alloc(uint32 size_byte);
		void ClearStack();

		void* marker;
		void* startPointer;
		void* endPointer;
	};

}