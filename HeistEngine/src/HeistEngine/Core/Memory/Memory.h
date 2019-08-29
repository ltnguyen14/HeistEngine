#pragma once
#include "Macro.h"

namespace Heist {
	
	class MemoryManager
	{
	public:
		MemoryManager(uintmax stackSize_mb); // stack size is in megabyte
		~MemoryManager();

		void* Alloc(uintmax size_byte);
		void ClearStack();

		void* marker;
		void* startPointer;
		void* endPointer;
		uintmax stackSize_mb;
	};

}