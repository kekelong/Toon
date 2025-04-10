#pragma once
#include <map>
#include <memory>
#include <string>

namespace Toon
{
	class DebugDraw;

	class DebugDrawManager
	{
	public:
		DebugDrawManager();
		void initialize();
		void destory();
		void clear();
		void tick(float delta_time);		
		~DebugDrawManager();

	private:
		std::map<std::string, std::shared_ptr<DebugDraw>> DebugDrawGroup;
		std::shared_ptr<DebugDraw> debugdraw;
	};

}
