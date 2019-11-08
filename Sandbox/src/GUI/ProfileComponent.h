#pragma once
#include <HeistEngine.h>

void DrawProfile(Heist::vec4 rect) {
  Heist::GUIManager::ButtonP(rect, {0.2f, 0.6f, 0.8f, 1.0f});
  Heist::GUIManager::Layout({rect.x, rect.y, 0.0f, rect.h / 2.0f}, {3, -1});
  {
    Heist::GUIManager::Button(rect.w / 7.0f * 2.0f, {0.2f, 0.3f, 0.8f, 1.0f}, "no. 10", {0.8f, 0.2f, 0.6f, 1.0f}, 8.0f);
    Heist::GUIManager::Button(rect.w / 7.0f * 3.0f, {0.2f, 0.3f, 0.4f, 1.0f}, "picture", {0.8f, 0.2f, 0.6f, 1.0f}, 8.0f);
    Heist::GUIManager::Button(rect.w / 7.0f * 2.0f, {0.2f, 0.3f, 0.8f, 1.0f}, "age 19", {0.8f, 0.2f, 0.6f, 1.0f}, 8.0f);
  } Heist::GUIManager::PopLayout();
}
