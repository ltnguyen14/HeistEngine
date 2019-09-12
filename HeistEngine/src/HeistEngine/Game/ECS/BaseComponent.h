#pragma once
#include "Macro.h"

namespace Heist {
	
	static int32 s_componentId;
	
	class BaseComponent {
	public:

		BaseComponent();
		~BaseComponent();

		static int32 componentTypeId;
	};

}