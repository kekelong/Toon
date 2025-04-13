#pragma once
#include "runtime/core/meta/serializer/serializer.h"
#include <memory>

namespace Toon
{

	class ToonEngine;
	class EditorUI;

	class ToonEditor
	{
	public:
		ToonEditor();
		virtual ~ToonEditor();

		void initialize(ToonEngine* engine_runtime);
		void clear();

		void run();

	protected:
		ToonEngine* m_engine_runtime{ nullptr };
		std::shared_ptr<EditorUI> m_editor_ui;
	};
} // namespace Toon
