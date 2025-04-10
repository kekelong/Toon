#include "engine.h"
#include "core/base/macro.h"
#include "editor.h"
#include "editor_ui.h"
#include "function/global/global_context.h"
namespace Toon
{
	ToonEditor::ToonEditor()
	{

	}

	ToonEditor::~ToonEditor() {}

	void ToonEditor::initialize(ToonEngine* engine_runtime)
	{
		ASSERT(engine_runtime);
		m_engine_runtime = engine_runtime;	
		m_editor_ui = std::make_shared<EditorUI>();
		WindowUIInitInfo ui_init_info = { g_runtime_global_context.m_window_system,
										 g_runtime_global_context.m_render_system };
		m_editor_ui->initialize(ui_init_info);
	}

	void ToonEditor::clear() {  }

	void ToonEditor::run()
	{
		ASSERT(m_engine_runtime);
		ASSERT(m_editor_ui);
		float delta_time;
		while (true)
		{
			delta_time = m_engine_runtime->calculateDeltaTime();
			if (!m_engine_runtime->tickOneFrame(delta_time))
				return;
		}
	}
} // namespace Toon
