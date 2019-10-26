#include "GUIManager.h"

namespace Heist {
	GUIManager* GUIManager::g_guiManager = nullptr;

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

	void GUIManager::OnNotify(Event* event) {

	}
}
