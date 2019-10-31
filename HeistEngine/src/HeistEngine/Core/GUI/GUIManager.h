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

    // Raw GUIs
    static bool ButtonP(vec4 rect, vec4 color);

    // Layouted GUIs
    static bool Button(vec2 size, vec4 color);

    // Layout
    static void Layout(vec4 rect, vec2 dimensionLimit);
    static void PopLayout();

    static std::vector<GUIElement> guis;
    static std::vector<GUIAutoLayout> autoLayouts;
    static uint32 hot_id;
    static uint32 active_id;
    static uint32 id_runner;

	private:
		GUIManager() : EventNode("GUIManager") {}
		GUIManager(GUIManager const&) : EventNode("GUIManager") {}
		GUIManager& operator=(GUIManager const&) {}

		static GUIManager* g_guiManager;
	};

}