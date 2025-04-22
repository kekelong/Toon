#include "runtime/function/framework/level/level_debugger.h"
#include "runtime/engine.h"
#include "runtime/core/meta/reflection/reflection.h"
#include "runtime/function/framework/component/component.h"
#include "runtime/resource/asset_manager.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/render/debugdraw/debug_draw_manager.h"
#include "runtime/function/render/render_debug_config.h"
#include "core/math/math_headers.h"
namespace Toon
{
    void LevelDebugger::tick(std::shared_ptr<Level> level) const
    {
        if (g_runtime_global_context.m_render_debug_config->gameObject.show_bounding_box)
        {
            showAllBoundingBox(level);
        }
    }

  
    void LevelDebugger::showAllBoundingBox(std::shared_ptr<Level> level) const
    {
        const LevelObjectsMap& go_map = level->getAllGObjects();
        for (const auto& gobject_pair : go_map)
        {
            drawBoundingBox(gobject_pair.second);
        }
    }

    void LevelDebugger::showBoundingBox(std::shared_ptr<Level> level, GObjectID go_id) const
    {
        std::shared_ptr<GObject> gobject = level->getGObjectByID(go_id).lock();
        drawBoundingBox(gobject);
    }
    void LevelDebugger::drawBoundingBox(std::shared_ptr<GObject> object) const
    {
        std::vector<AxisAlignedBox> bounding_boxes;
        //TODO
    }
  
} // namespace Toon