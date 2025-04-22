#pragma once
#include "runtime/function/framework/level/level.h"
#include "runtime/function/framework/object/object.h"

namespace Toon
{
    class LevelDebugger
    {
    public:
        void tick(std::shared_ptr<Level> level) const;
        // show all bindingBox in a level
        void showAllBoundingBox(std::shared_ptr<Level> level) const;
        // show boundingBox of a object
        void showBoundingBox(std::shared_ptr<Level> level, GObjectID go_id) const;

    private:
        void drawBoundingBox(std::shared_ptr<GObject> object) const;
    };
} // namespace Toon