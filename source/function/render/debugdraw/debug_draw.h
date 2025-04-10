#pragma once
namespace Toon
{
	class DebugDraw
	{
	public:
		virtual void draw(float delta_time) = 0;

		virtual void initialize() = 0;

		virtual void clear() = 0;
	};
}