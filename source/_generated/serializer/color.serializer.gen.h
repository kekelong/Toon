#pragma once
#include "runtime\core\color\color.h"

namespace Toon{
    template<>
    Json Serializer::write(const Color& instance);
    template<>
    Color& Serializer::read(const Json& json_context, Color& instance);
}//namespace

