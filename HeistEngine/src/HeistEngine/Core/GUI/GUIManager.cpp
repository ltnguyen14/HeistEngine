#include "GUIManager.h"

namespace Heist {
	GUIManager* GUIManager::g_guiManager = nullptr;
  std::vector<GUIElement> GUIManager::guis;

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

  bool GUIManager::Button() {
    guis.push_back({ 1 });
    return false;
  }

	void GUIManager::OnNotify(Event* event) {

	}

  void GUIManager::BeginFrame() {
    guis.clear();
  }

  void GUIManager::EndFrame() {
    for (auto gui : guis) {
      Renderer2D::DrawSprite({0, 0, 0}, {400.0f, 700.0f}, {0.18f, 0.77f, 0.71f, 0.5f});
    }
  }
}
