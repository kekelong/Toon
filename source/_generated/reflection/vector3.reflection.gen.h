#pragma once
#include "runtime\core\math\vector3.h"

namespace Toon{
    class Vector3;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeVector3Operator{
    public:
        static const char* getClassName(){ return "Vector3";}
        static void* constructorWithJson(const Json& json_context){
            Vector3* ret_instance= new Vector3;
            Serializer::read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::write(*(Vector3*)instance);
        }
        // base class
        static int getVector3BaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        static const char* getFieldName_x(){ return "x";}
        static const char* getFieldTypeName_x(){ return "float";}
        static void set_x(void* instance, void* field_value){ static_cast<Vector3*>(instance)->x = *static_cast<float*>(field_value);}
        static void* get_x(void* instance){ return static_cast<void*>(&(static_cast<Vector3*>(instance)->x));}
        static bool isArray_x(){ return false; }
        static const char* getFieldName_y(){ return "y";}
        static const char* getFieldTypeName_y(){ return "float";}
        static void set_y(void* instance, void* field_value){ static_cast<Vector3*>(instance)->y = *static_cast<float*>(field_value);}
        static void* get_y(void* instance){ return static_cast<void*>(&(static_cast<Vector3*>(instance)->y));}
        static bool isArray_y(){ return false; }
        static const char* getFieldName_z(){ return "z";}
        static const char* getFieldTypeName_z(){ return "float";}
        static void set_z(void* instance, void* field_value){ static_cast<Vector3*>(instance)->z = *static_cast<float*>(field_value);}
        static void* get_z(void* instance){ return static_cast<void*>(&(static_cast<Vector3*>(instance)->z));}
        static bool isArray_z(){ return false; }

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Vector3(){
        FieldFunctionTuple* field_function_tuple_x=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector3Operator::set_x,
            &TypeFieldReflectionOparator::TypeVector3Operator::get_x,
            &TypeFieldReflectionOparator::TypeVector3Operator::getClassName,
            &TypeFieldReflectionOparator::TypeVector3Operator::getFieldName_x,
            &TypeFieldReflectionOparator::TypeVector3Operator::getFieldTypeName_x,
            &TypeFieldReflectionOparator::TypeVector3Operator::isArray_x);
        REGISTER_FIELD_TO_MAP("Vector3", field_function_tuple_x);
        FieldFunctionTuple* field_function_tuple_y=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector3Operator::set_y,
            &TypeFieldReflectionOparator::TypeVector3Operator::get_y,
            &TypeFieldReflectionOparator::TypeVector3Operator::getClassName,
            &TypeFieldReflectionOparator::TypeVector3Operator::getFieldName_y,
            &TypeFieldReflectionOparator::TypeVector3Operator::getFieldTypeName_y,
            &TypeFieldReflectionOparator::TypeVector3Operator::isArray_y);
        REGISTER_FIELD_TO_MAP("Vector3", field_function_tuple_y);
        FieldFunctionTuple* field_function_tuple_z=new FieldFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector3Operator::set_z,
            &TypeFieldReflectionOparator::TypeVector3Operator::get_z,
            &TypeFieldReflectionOparator::TypeVector3Operator::getClassName,
            &TypeFieldReflectionOparator::TypeVector3Operator::getFieldName_z,
            &TypeFieldReflectionOparator::TypeVector3Operator::getFieldTypeName_z,
            &TypeFieldReflectionOparator::TypeVector3Operator::isArray_z);
        REGISTER_FIELD_TO_MAP("Vector3", field_function_tuple_z);

        
        
        
        ClassFunctionTuple* class_function_tuple_Vector3=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector3Operator::getVector3BaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeVector3Operator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeVector3Operator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Vector3", class_function_tuple_Vector3);
    }
namespace TypeWrappersRegister{
    void Vector3()
    {
        TypeWrapperRegister_Vector3();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace Toon

