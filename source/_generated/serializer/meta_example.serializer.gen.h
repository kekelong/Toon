#pragma once
#include "runtime\core\meta\meta_example.h"

namespace Toon{
    template<>
    Json Serializer::write(const BaseTest& instance);
    template<>
    BaseTest& Serializer::read(const Json& json_context, BaseTest& instance);
    template<>
    Json Serializer::write(const Test1& instance);
    template<>
    Test1& Serializer::read(const Json& json_context, Test1& instance);
    template<>
    Json Serializer::write(const Test2& instance);
    template<>
    Test2& Serializer::read(const Json& json_context, Test2& instance);
}//namespace

