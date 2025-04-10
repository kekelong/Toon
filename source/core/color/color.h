#pragma once
#include "core/math/vector3.h"
#include "core/math/vector4.h"

namespace Toon
{
    class Color
    {
    public:
        float r;
        float g;
        float b;
        float a;

        Vector3 toVector3() const { return Vector3(r, g, b); }
        Vector4 toVector4() const { return Vector4(r, g, b, a); }
    };

}