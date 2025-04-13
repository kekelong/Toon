#pragma once
#include "runtime\core\color\color.h"

namespace Toon{
    class Color;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeColorOperator{
    public:
        static const char* getClassName(){ return "Color";}
        static void* constructorWithJson(const Json& json_context){
            Color* ret_instance= new Color;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(Color*)instance);
        }
        // base class
        static int getColorBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_r(){ return "r";}
        static const char* getFieldTypeName_r(){ return "float";}
        static void set_r(void* instance, void* field_value){ static_cast<Color*>(instance)->r = *static_cast<float*>(field_value);}
        static void* get_r(void* instance){ return static_cast<void*>(&(static_cast<Color*>(instance)->r));}
        static bool isArray_r(){ return false; }
        static const char* getFieldName_g(){ return "g";}
        static const char* getFieldTypeName_g(){ return "float";}
        static void set_g(void* instance, void* field_value){ static_cast<Color*>(instance)->g = *static_cast<float*>(field_value);}
        static void* get_g(void* instance){ return static_cast<void*>(&(static_cast<Color*>(instance)->g));}
        static bool isArray_g(){ return false; }
        static const char* getFieldName_b(){ return "b";}
        static const char* getFieldTypeName_b(){ return "float";}
        static void set_b(void* instance, void* field_value){ static_cast<Color*>(instance)->b = *static_cast<float*>(field_value);}
        static void* get_b(void* instance){ return static_cast<void*>(&(static_cast<Color*>(instance)->b));}
        static bool isArray_b(){ return false; }
        static const char* getFieldName_a(){ return "a";}
        static const char* getFieldTypeName_a(){ return "float";}
        static void set_a(void* instance, void* field_value){ static_cast<Color*>(instance)->a = *static_cast<float*>(field_value);}
        static void* get_a(void* instance){ return static_cast<void*>(&(static_cast<Color*>(instance)->a));}
        static bool isArray_a(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Color(){
        FieldFunctionTuple* field_function_tuple_r=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeColorOperator::set_r,
            &TypeFieldReflectionOparator::TypeColorOperator::get_r,
            &TypeFieldReflectionOparator::TypeColorOperator::getClassName,
            &TypeFieldReflectionOparator::TypeColorOperator::getFieldName_r,
            &TypeFieldReflectionOparator::TypeColorOperator::getFieldTypeName_r,
            &TypeFieldReflectionOparator::TypeColorOperator::isArray_r);
        REGISTER_FIELD_TO_MAP("Color", field_function_tuple_r);
        FieldFunctionTuple* field_function_tuple_g=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeColorOperator::set_g,
            &TypeFieldReflectionOparator::TypeColorOperator::get_g,
            &TypeFieldReflectionOparator::TypeColorOperator::getClassName,
            &TypeFieldReflectionOparator::TypeColorOperator::getFieldName_g,
            &TypeFieldReflectionOparator::TypeColorOperator::getFieldTypeName_g,
            &TypeFieldReflectionOparator::TypeColorOperator::isArray_g);
        REGISTER_FIELD_TO_MAP("Color", field_function_tuple_g);
        FieldFunctionTuple* field_function_tuple_b=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeColorOperator::set_b,
            &TypeFieldReflectionOparator::TypeColorOperator::get_b,
            &TypeFieldReflectionOparator::TypeColorOperator::getClassName,
            &TypeFieldReflectionOparator::TypeColorOperator::getFieldName_b,
            &TypeFieldReflectionOparator::TypeColorOperator::getFieldTypeName_b,
            &TypeFieldReflectionOparator::TypeColorOperator::isArray_b);
        REGISTER_FIELD_TO_MAP("Color", field_function_tuple_b);
        FieldFunctionTuple* field_function_tuple_a=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeColorOperator::set_a,
            &TypeFieldReflectionOparator::TypeColorOperator::get_a,
            &TypeFieldReflectionOparator::TypeColorOperator::getClassName,
            &TypeFieldReflectionOparator::TypeColorOperator::getFieldName_a,
            &TypeFieldReflectionOparator::TypeColorOperator::getFieldTypeName_a,
            &TypeFieldReflectionOparator::TypeColorOperator::isArray_a);
        REGISTER_FIELD_TO_MAP("Color", field_function_tuple_a);

        
        
        
        ClassFunctionTuple* class_function_tuple_Color=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeColorOperator::getColorBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeColorOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeColorOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Color", class_function_tuple_Color);
    }
namespace TypeWrappersRegister{
    void Color()
    {
        TypeWrapperRegister_Color();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace Toon

