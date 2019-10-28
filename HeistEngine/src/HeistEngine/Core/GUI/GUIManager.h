#pragma once
#include "GUI.h"
#include "Core/Event/EventNode.h"
#include "Core/Math/Math.h"
#include "Core/Renderer/Renderer2D.h"

namespace Heist {

	class GUIManager : public EventNode {
	public:
		static GUIManager* Instance();
		~GUIManager();

		void StartUp() override;
		void ShutDown() override;

		void OnNotify(Event* event) override;

    static void BeginFrame();
    static void EndFrame(); // Actual rendering things
    static bool Button();
    static std::vector<GUIElement> guis;

	private:
		GUIManager() : EventNode("GUIManager") {}
		GUIManager(GUIManager const&) : EventNode("GUIManager") {}
		GUIManager& operator=(GUIManager const&) {}

		static GUIManager* g_guiManager;
	};

}
