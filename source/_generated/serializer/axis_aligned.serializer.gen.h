#pragma once
#include "runtime\core\math\axis_aligned.h"

namespace Toon{
    template<>
    Json Serializer::write(const AxisAlignedBox& instance);
    template<>
    AxisAlignedBox& Serializer::read(const Json& json_context, AxisAlignedBox& instance);
}//namespace

