#include "GUIManager.h"
#include "Core/Manager/InputManager.h"
#include "Core/FileSystem/FileManager.h"

namespace Heist {
	GUIManager* GUIManager::g_guiManager = nullptr;

  std::vector<GUIAutoLayout> GUIManager::autoLayouts;
  std::vector<GUIElement> GUIManager::guis;
  std::shared_ptr<Texture> GUIManager::fontTexture;
  std::shared_ptr<FontData> GUIManager::fontData;
  uint32 GUIManager::hot_id = 0;
  uint32 GUIManager::active_id = 0;
  uint32 GUIManager::id_runner = 0;

	GUIManager* GUIManager::Instance() {
		if (!g_guiManager) {
			g_guiManager = new GUIManager();
		};

		return g_guiManager;
	}

	GUIManager::~GUIManager() {}

	void GUIManager::StartUp() {
		g_guiManager = GUIManager::Instance();
	}

	void GUIManager::ShutDown() {
		delete g_guiManager;
	}

  void GUIManager::Layout(vec4 rect, vec2 dimensionLimit) {
    autoLayouts.push_back({rect, dimensionLimit });
  }

  void GUIManager::PopLayout() {
    autoLayouts.pop_back();
  }

  void GUIManager::SetupFont(const std::string& fontPath, const std::string& fontDataPath) {
    fontTexture.reset(Texture::Create(fontPath.c_str()));
    fontData = FileManager::ReadFontFile(fontDataPath.c_str());
  }

  bool GUIManager::ButtonP(vec4 rect, vec4 color) {
    uint32 guiId = ++id_runner;
    bool isTriggered = false;

    guis.push_back({ guiId, rect, color });

    vec2 cursorPos = InputManager::Instance()->GetMousePosition();
    bool leftMouseDown = InputManager::Instance()->GetKey(HS_MOUSE_BUTTON_1);
    bool cursorIsOver = {
      cursorPos.x >= rect.x &&
      cursorPos.x <= rect.x + rect.w &&
      cursorPos.y >= rect.y &&
      cursorPos.y <= rect.y + rect.h
    };

    // Check if gui is hot
    if (cursorIsOver) {
      hot_id = guiId;
    } else if (guiId == hot_id) {
      hot_id = 0;
    }

    // Check if it's active
    if (active_id == guiId && !leftMouseDown) {
      isTriggered = hot_id == guiId;
      active_id = 0;
    } else if (hot_id == guiId && leftMouseDown) {
      active_id = guiId;
    }

    return isTriggered;
  }

  bool GUIManager::Button(vec2 size, vec4 color) {
    if (autoLayouts.size() >= 1) {
      GUIAutoLayout& layout = autoLayouts.back();

      bool triggered = ButtonP({layout.xOffset + layout.rect.x, layout.yOffset + layout.rect.y, size.x, size.y}, color);

      if (layout.xCount == layout.dimensionLimit.x - 1) {
        layout.xCount = 0;
        layout.xOffset = 0;

        layout.yCount++;
        layout.yOffset += size.y + layout.rect.h;

        HS_ASSERT(layout.yCount < layout.dimensionLimit.y || layout.dimensionLimit.y < 0, "AutoLayout dimension limit violated!");
      } else {
        layout.xCount++;
        layout.xOffset += size.x + layout.rect.w;
      }

      return triggered;
    } else return false;
  }

  void GUIManager::Text(const std::string& text, const vec3& position, const vec4& color) {
    // NOTE(LAM): Ignoring position.z for now
    vec2 cursorPos = {position.x, position.y};
    for (auto character : text) {
      auto charData = fontData->data[character];
      Renderer2D::DrawText({cursorPos.x + charData.xOffset, cursorPos.y + charData.yOffset, charData.width, charData.height},
                           {charData.x / fontData->width, 1 - (charData.y + charData.height) / fontData->height, charData.width / fontData->width, charData.height / fontData->height}, color);

      cursorPos.x += charData.xAdvance;
    }
  }

	void GUIManager::OnNotify(Event* event) {

	}

  void GUIManager::BeginFrame() {
    guis.clear();
    Renderer2D::LoadFontTexture(fontTexture);
  }

  void GUIManager::EndFrame() {
    for (auto gui : guis) {
      auto rect = gui.rect;
      Renderer2D::DrawSprite({ rect.x, rect.y, 0.0f }, { rect.w, rect.h }, gui.color);
    }

    id_runner = 0;
    autoLayouts.clear();
  }
}
