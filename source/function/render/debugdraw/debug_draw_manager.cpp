#include "function/render/debugdraw/debug_draw_manager.h"
#include "function/render/debugdraw/debug_draw.h"
#include "function/render/debugdraw/debug_draw_primitive.h"


namespace Toon
{
	DebugDrawManager::DebugDrawManager()
	{

	}

	void DebugDrawManager::initialize()
	{
		DebugDrawGroup["DebugDrawPrimitive"] = std::make_shared<DebugDrawPrimitive>();
		debugdraw = DebugDrawGroup["DebugDrawPrimitive"];

		if (debugdraw)
		{
			debugdraw->initialize();
		}
	}

	void DebugDrawManager::destory()
	{

	}

	void DebugDrawManager::clear()
	{
		if (debugdraw)
		{
			debugdraw->clear();
		}
	}

	void DebugDrawManager::tick(float delta_time)
	{
		if (debugdraw)
		{
			debugdraw->draw(delta_time);
		}
	}

	DebugDrawManager::~DebugDrawManager()
	{
		destory();
	}

}