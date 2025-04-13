#pragma once

#include <chrono>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include "runtime/function/ui/window_ui.h"

namespace Toon
{
	class ToonEditor;
	class WindowSystem;
	class EditorUI : WindowUI
	{
	public:
		EditorUI();

	private:

		void showEditorUI();
		void showEditorMenu(bool* p_open);
		void showEditorDetailWindow(bool* p_open);
		void setUIColorStyle();

	public:
		virtual void initialize(WindowUIInitInfo init_info) override final;
		virtual void preRender() override final;

	private:

		bool m_editor_menu_window_open = true;
		bool m_detail_window_open = true;
	};
} // namespace Toon