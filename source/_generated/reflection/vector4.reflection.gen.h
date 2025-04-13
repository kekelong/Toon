#pragma once
#include "runtime\core\math\vector4.h"

namespace Toon{
    class Vector4;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeVector4Operator{
    public:
        static const char* getClassName(){ return "Vector4";}
        static void* constructorWithJson(const Json& json_context){
            Vector4* ret_instance= new Vector4;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(Vector4*)instance);
        }
        // base class
        static int getVector4BaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_x(){ return "x";}
        static const char* getFieldTypeName_x(){ return "float";}
        static void set_x(void* instance, void* field_value){ static_cast<Vector4*>(instance)->x = *static_cast<float*>(field_value);}
        static void* get_x(void* instance){ return static_cast<void*>(&(static_cast<Vector4*>(instance)->x));}
        static bool isArray_x(){ return false; }
        static const char* getFieldName_y(){ return "y";}
        static const char* getFieldTypeName_y(){ return "float";}
        static void set_y(void* instance, void* field_value){ static_cast<Vector4*>(instance)->y = *static_cast<float*>(field_value);}
        static void* get_y(void* instance){ return static_cast<void*>(&(static_cast<Vector4*>(instance)->y));}
        static bool isArray_y(){ return false; }
        static const char* getFieldName_z(){ return "z";}
        static const char* getFieldTypeName_z(){ return "float";}
        static void set_z(void* instance, void* field_value){ static_cast<Vector4*>(instance)->z = *static_cast<float*>(field_value);}
        static void* get_z(void* instance){ return static_cast<void*>(&(static_cast<Vector4*>(instance)->z));}
        static bool isArray_z(){ return false; }
        static const char* getFieldName_w(){ return "w";}
        static const char* getFieldTypeName_w(){ return "float";}
        static void set_w(void* instance, void* field_value){ static_cast<Vector4*>(instance)->w = *static_cast<float*>(field_value);}
        static void* get_w(void* instance){ return static_cast<void*>(&(static_cast<Vector4*>(instance)->w));}
        static bool isArray_w(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Vector4(){
        FieldFunctionTuple* field_function_tuple_x=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector4Operator::set_x,
            &TypeFieldReflectionOparator::TypeVector4Operator::get_x,
            &TypeFieldReflectionOparator::TypeVector4Operator::getClassName,
            &TypeFieldReflectionOparator::TypeVector4Operator::getFieldName_x,
            &TypeFieldReflectionOparator::TypeVector4Operator::getFieldTypeName_x,
            &TypeFieldReflectionOparator::TypeVector4Operator::isArray_x);
        REGISTER_FIELD_TO_MAP("Vector4", field_function_tuple_x);
        FieldFunctionTuple* field_function_tuple_y=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector4Operator::set_y,
            &TypeFieldReflectionOparator::TypeVector4Operator::get_y,
            &TypeFieldReflectionOparator::TypeVector4Operator::getClassName,
            &TypeFieldReflectionOparator::TypeVector4Operator::getFieldName_y,
            &TypeFieldReflectionOparator::TypeVector4Operator::getFieldTypeName_y,
            &TypeFieldReflectionOparator::TypeVector4Operator::isArray_y);
        REGISTER_FIELD_TO_MAP("Vector4", field_function_tuple_y);
        FieldFunctionTuple* field_function_tuple_z=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector4Operator::set_z,
            &TypeFieldReflectionOparator::TypeVector4Operator::get_z,
            &TypeFieldReflectionOparator::TypeVector4Operator::getClassName,
            &TypeFieldReflectionOparator::TypeVector4Operator::getFieldName_z,
            &TypeFieldReflectionOparator::TypeVector4Operator::getFieldTypeName_z,
            &TypeFieldReflectionOparator::TypeVector4Operator::isArray_z);
        REGISTER_FIELD_TO_MAP("Vector4", field_function_tuple_z);
        FieldFunctionTuple* field_function_tuple_w=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector4Operator::set_w,
            &TypeFieldReflectionOparator::TypeVector4Operator::get_w,
            &TypeFieldReflectionOparator::TypeVector4Operator::getClassName,
            &TypeFieldReflectionOparator::TypeVector4Operator::getFieldName_w,
            &TypeFieldReflectionOparator::TypeVector4Operator::getFieldTypeName_w,
            &TypeFieldReflectionOparator::TypeVector4Operator::isArray_w);
        REGISTER_FIELD_TO_MAP("Vector4", field_function_tuple_w);

        
        
        
        ClassFunctionTuple* class_function_tuple_Vector4=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector4Operator::getVector4BaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeVector4Operator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeVector4Operator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Vector4", class_function_tuple_Vector4);
    }
namespace TypeWrappersRegister{
    void Vector4()
    {
        TypeWrapperRegister_Vector4();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace Toon

