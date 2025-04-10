#pragma once

namespace Toon {

	class WindowUI;

	class RenderImgui {

	public:
		void initialize(WindowUI* window_ui);

		void tick(float delta_time);

		void clear();
	private:
		WindowUI* m_window_ui;
	};
}