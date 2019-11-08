#include "GUIManager.h"
#include "Core/Manager/InputManager.h"
#include "Core/FileSystem/FileManager.h"
#undef max
#undef min

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

  real32 GUIManager::GetTextWidth(const std::string& text, real32 scale) {
    // Find line width
    real32 lineWidth = 0.0f;
    for (auto character : text) {
      auto charData = fontData->data[character];
      lineWidth += charData.width * scale + charData.xOffset * scale;
    }

    return lineWidth;
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

  bool GUIManager::ButtonP(vec3 rect, vec4 color, const std::string& text, vec4 textColor, real32 padding, bool breakLines) {
    real32 textHeight = 0.0f;
    if (breakLines) {
      textHeight = Text(text, {rect.x + padding, rect.y + padding, rect.z - 2 * padding, 0.0f}, textColor);
    } else {
      textHeight = Text(text, {rect.x + padding, rect.y + padding, rect.z - 2 * padding}, textColor);
    }

    return ButtonP({rect.x, rect.y, rect.z, 2 * padding + textHeight}, color);
  }

  bool GUIManager::ButtonP(vec4 rect, vec4 color, const std::string& text, vec4 textColor, real32 padding, bool breakLines) {
    real32 textHeight = 0.0f;
    if (breakLines) {
      textHeight = Text(text, {rect.x + padding, rect.y + padding, rect.z - 2 * padding, 0.0f}, textColor);
    } else {
      textHeight = Text(text, {rect.x + padding, rect.y + padding, rect.z - 2 * padding}, textColor);
    }

    return ButtonP({rect.x, rect.y, rect.z, 2 * padding + rect.h}, color);
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

  bool GUIManager::Button(vec2 size, vec4 color, const std::string& text, vec4 textColor, real32 padding, bool breakLines) {
    if (autoLayouts.size() >= 1) {
      GUIAutoLayout& layout = autoLayouts.back();

      bool triggered = ButtonP({layout.xOffset + layout.rect.x, layout.yOffset + layout.rect.y, size.x, size.y}, color, text, textColor, padding, breakLines);

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

  bool GUIManager::Button(real32 width, vec4 color, const std::string& text, vec4 textColor, real32 padding, bool breakLines) {
    if (autoLayouts.size() >= 1) {
      GUIAutoLayout& layout = autoLayouts.back();

      bool triggered = ButtonP({layout.xOffset + layout.rect.x, layout.yOffset + layout.rect.y, width}, color, text, textColor, padding, breakLines);

      if (layout.xCount == layout.dimensionLimit.x - 1) {
        layout.xCount = 0;
        layout.xOffset = 0;

        layout.yCount++;
        layout.yOffset += layout.rect.h;

        HS_ASSERT(layout.yCount < layout.dimensionLimit.y || layout.dimensionLimit.y < 0, "AutoLayout dimension limit violated!");
      } else {
        layout.xCount++;
        layout.xOffset += width + layout.rect.w;
      }

      return triggered;
    } else return false;
  }

  real32 GUIManager::Text(const std::string& text, const vec4& rect, const vec4& color, real32 scale) {
    real32 fontPaddingOffset = 10.0f;
    vec2 cursorPos = {rect.x, rect.y};
    real32 lineHeight = -1;

    // Find line height
    for (auto character : text) {
      auto charData = fontData->data[character];
      lineHeight = std::max(lineHeight, charData.height * scale + charData.yOffset * scale);
    }

    for (int32 index = 0; index < text.size(); index++) {
      const char character = text[index];
      bool breakline = false;
      auto charData = fontData->data[character];
      Renderer2D::DrawText({cursorPos.x + charData.xOffset * scale, cursorPos.y + charData.yOffset * scale, charData.width * scale, charData.height * scale},
                           {charData.x / fontData->width, 1 - (charData.y + charData.height) / fontData->height, charData.width / fontData->width, charData.height / fontData->height}, color);

      cursorPos.x += charData.xAdvance * scale - fontPaddingOffset * scale;

      if (character == ' ') {
        real32 widthTillSpace = 0.0f;
        auto runner = index + 1;
        auto ch = text[runner];
        while (ch != '\0' && ch != ' ') {
          widthTillSpace += fontData->data[ch].width * scale;
          ch = text[++runner];
        }

        if (widthTillSpace + cursorPos.x > rect.w + rect.x)
          breakline = true;
      }

      if (breakline) {
        cursorPos.x = rect.x;
        cursorPos.y += lineHeight * scale;
      }
    }

    return (cursorPos.y - rect.y + lineHeight);
  }

  real32 GUIManager::Text(const std::string& text, const vec3& rect, const vec4& color, real32 scale) {
    real32 fontPaddingOffset = 10.0f;
    vec2 cursorPos = {rect.x, rect.y};
    real32 totalWidth = 0.0f;
    real32 lineHeight = -1.0f;

    for (auto character : text) {
      auto charData = fontData->data[character];
      totalWidth += charData.width * scale;
      lineHeight = std::max(lineHeight, charData.height * scale + charData.yOffset * scale);
    }
    real32 fitScale = rect.z / totalWidth;

    for (int32 index = 0; index < text.size(); index++) {
      const char character = text[index];
      auto charData = fontData->data[character];
      Renderer2D::DrawText(
                           { cursorPos.x + charData.xOffset * scale * fitScale,
                               cursorPos.y + charData.yOffset * scale * fitScale - fontPaddingOffset * scale / 2,
                               charData.width * scale * fitScale,
                               charData.height * scale * fitScale
                               },
                           {
                             charData.x / fontData->width,
                               1 - (charData.y + charData.height) / fontData->height,
                               charData.width / fontData->width, charData.height / fontData->height
                               },
                           color);

      cursorPos.x += charData.xAdvance * scale * fitScale - fontPaddingOffset * scale * fitScale;

    }
    return lineHeight * fitScale - fontPaddingOffset * scale / 2;
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
