#pragma once
namespace Toon
{
    class RenderDebugConfig
    {
    public:
        struct GameObject
        {
            bool show_bounding_box = false;
        };
        GameObject gameObject;
    };
}