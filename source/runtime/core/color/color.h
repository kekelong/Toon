#pragma once
#include "runtime/core/meta/reflection/reflection.h"

#include "runtime/core/math/vector4.h"

namespace Toon
{
    REFLECTION_TYPE(Color)
    CLASS(Color, Fields)
    {
        REFLECTION_BODY(Color);

    public:
        float r;
        float g;
        float b;
        float a;

        Vector4 toVector4() const { return Vector4(r, g, b, a); }
    };
}