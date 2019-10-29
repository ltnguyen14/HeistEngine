#include "GUIManager.h"
#include "Core/Manager/InputManager.h"

namespace Heist {
	GUIManager* GUIManager::g_guiManager = nullptr;
  std::vector<GUIElement> GUIManager::guis;
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

  bool GUIManager::Button(vec4 rect, vec4 color) {
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

	void GUIManager::OnNotify(Event* event) {

	}

  void GUIManager::BeginFrame() {
    guis.clear();
  }

  void GUIManager::EndFrame() {
    for (auto gui : guis) {
      auto rect = gui.rect;
      Renderer2D::DrawSprite({ rect.x, rect.y, 0.0f }, { rect.w, rect.h }, gui.color);
    }

    id_runner = 0;
  }
}
