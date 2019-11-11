#pragma once
#include "GUI.h"
#include "Core/Event/EventNode.h"
#include "Core/Math/Math.h"
#include "Core/Renderer/Renderer2D.h"
#include "Core/Renderer/Texture.h"

namespace Heist {

	class GUIManager : public EventNode {
	public:
		static GUIManager* Instance();
		~GUIManager();

		void StartUp() override;
		void ShutDown() override;

		void OnNotify(Event* event) override;

    static void SetupFont(const std::string& fontPath, const std::string& fontDataPath);
    static void BeginFrame();
    static void EndFrame(); // Actual rendering things

    // Utils
    static real32 GetTextWidth(const std::string& text, real32 scale = 1.0f);

    // Raw GUIs
    static bool ButtonP(vec4 rect, vec4 color);
    static bool ButtonP(vec3 rect, vec4 color, const std::string& text, vec4 textColor, real32 scale = 1.0f, real32 padding = 0.0f, bool breakLines = false);
    static bool ButtonP(vec4 rect, vec4 color, const std::string& text, vec4 textColor, real32 scale = 1.0f, real32 padding = 0.0f, bool breakLines = false);

    // Layouted GUIs
    static bool Button(vec2 size, vec4 color);
    static bool Button(vec2 size, vec4 color, const std::string& text, vec4 textColor, real32 scale = 1.0f, real32 padding = 0.0f, bool breakLines = false);
    static bool Button(real32 width, vec4 color, const std::string& text, vec4 textColor, real32 scale = 1.0f, real32 padding = 0.0f, bool breakLines = false);

    // Text Rendering
    static real32 Text(const std::string& text, const vec4& rect, const vec4& color, real32 scale = 1.0f);
    static real32 Text(const std::string& text, const vec3& rect, const vec4& color, real32 scale = 1.0f);

    // Layout
    static void Layout(vec4 rect, vec2 dimensionLimit);
    static void PopLayout();

    static std::vector<GUIElement> guis;
    static std::vector<GUIAutoLayout> autoLayouts;
    static uint32 hot_id;
    static uint32 active_id;
    static uint32 id_runner;
    static std::shared_ptr<Texture> fontTexture;
    static std::shared_ptr<FontData> fontData;

	private:
		GUIManager() : EventNode("GUIManager") {}
		GUIManager(GUIManager const&) : EventNode("GUIManager") {}
		GUIManager& operator=(GUIManager const&) {}

		static GUIManager* g_guiManager;
	};
}
