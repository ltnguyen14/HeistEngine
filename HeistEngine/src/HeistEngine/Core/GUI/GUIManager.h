#pragma once
#include "Core/Event/EventNode.h"
#include "Core/Math/Math.h"

namespace Heist {

	class GUIManager : public EventNode {
	public:
		static GUIManager* Instance();
		~GUIManager();

		void StartUp() override;
		void ShutDown() override;

		void OnNotify(Event* event) override;

	private:

		GUIManager() : EventNode("GUIManager") {}
		GUIManager(GUIManager const&) : EventNode("GUIManager") {}
		GUIManager& operator=(GUIManager const&) {}

		static GUIManager* g_guiManager;

	};

}
