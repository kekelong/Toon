#pragma once

#include "runtime/core/math/matrix4.h"
#include "runtime/core/math/vector3.h"
#include "runtime/core/math/vector4.h"
#include "runtime/function/render/render_type.h"
#include "runtime/function/render/opengl/opengl_rhi.h"

namespace Toon
{
    static const uint32_t s_point_light_shadow_map_dimension       = 2048;
    static const uint32_t s_directional_light_shadow_map_dimension = 4096;

    // TODO: 64 may not be the best
    static uint32_t const s_mesh_per_drawcall_max_instance_count = 64;
    static uint32_t const s_mesh_vertex_blending_max_joint_count = 1024;
    static uint32_t const s_max_point_light_count                = 15;
    // should sync the macros in "shader_include/constants.h"

    struct VulkanSceneDirectionalLight
    {
        Vector3 direction;
        float   _padding_direction;
        Vector3 color;
        float   _padding_color;
    };

    struct VulkanScenePointLight
    {
        Vector3 position;
        float   radius;
        Vector3 intensity;
        float   _padding_intensity;
    };

    struct MeshPerframeStorageBufferObject
    {
        Matrix4x4                   proj_view_matrix;
        Vector3                     camera_position;
        float                       _padding_camera_position;
        Vector3                     ambient_light;
        float                       _padding_ambient_light;
        uint32_t                    point_light_num;
        uint32_t                    _padding_point_light_num_1;
        uint32_t                    _padding_point_light_num_2;
        uint32_t                    _padding_point_light_num_3;
        VulkanScenePointLight       scene_point_lights[s_max_point_light_count];
        VulkanSceneDirectionalLight scene_directional_light;
        Matrix4x4                   directional_light_proj_view;
    };

    struct VulkanMeshInstance
    {
        float     enable_vertex_blending;
        float     _padding_enable_vertex_blending_1;
        float     _padding_enable_vertex_blending_2;
        float     _padding_enable_vertex_blending_3;
        Matrix4x4 model_matrix;
    };

    struct MeshPerdrawcallStorageBufferObject
    {
        VulkanMeshInstance mesh_instances[s_mesh_per_drawcall_max_instance_count];
    };

    struct MeshPerdrawcallVertexBlendingStorageBufferObject
    {
        Matrix4x4 joint_matrices[s_mesh_vertex_blending_max_joint_count * s_mesh_per_drawcall_max_instance_count];
    };

    struct MeshPerMaterialUniformBufferObject
    {
        Vector4 baseColorFactor {0.0f, 0.0f, 0.0f, 0.0f};

        float metallicFactor    = 0.0f;
        float roughnessFactor   = 0.0f;
        float normalScale       = 0.0f;
        float occlusionStrength = 0.0f;

        Vector3  emissiveFactor  = {0.0f, 0.0f, 0.0f};
        uint32_t is_blend        = 0;
        uint32_t is_double_sided = 0;
    };

    struct MeshPointLightShadowPerframeStorageBufferObject
    {
        uint32_t point_light_num;
        uint32_t _padding_point_light_num_1;
        uint32_t _padding_point_light_num_2;
        uint32_t _padding_point_light_num_3;
        Vector4  point_lights_position_and_radius[s_max_point_light_count];
    };

    struct MeshPointLightShadowPerdrawcallStorageBufferObject
    {
        VulkanMeshInstance mesh_instances[s_mesh_per_drawcall_max_instance_count];
    };

    struct MeshPointLightShadowPerdrawcallVertexBlendingStorageBufferObject
    {
        Matrix4x4 joint_matrices[s_mesh_vertex_blending_max_joint_count * s_mesh_per_drawcall_max_instance_count];
    };

    struct MeshDirectionalLightShadowPerframeStorageBufferObject
    {
        Matrix4x4 light_proj_view;
    };

    struct MeshDirectionalLightShadowPerdrawcallStorageBufferObject
    {
        VulkanMeshInstance mesh_instances[s_mesh_per_drawcall_max_instance_count];
    };

    struct MeshDirectionalLightShadowPerdrawcallVertexBlendingStorageBufferObject
    {
        Matrix4x4 joint_matrices[s_mesh_vertex_blending_max_joint_count * s_mesh_per_drawcall_max_instance_count];
    };

    struct ParticleCollisionPerframeStorageBufferObject
    {
        Matrix4x4 view_matrix;
        Matrix4x4 proj_view_matrix;
        Matrix4x4 proj_inv_matrix;
    };

    // mesh
    struct OpenGLMesh
    {
        std::shared_ptr<VertexArray> VAO;
    };

    // material
    struct OpenGLMaterial
    {
        
    };

    // nodes
    struct RenderMeshNode
    {
        const Matrix4x4*   model_matrix {nullptr};
        OpenGLMesh*        ref_mesh {nullptr};
        OpenGLMaterial* ref_material {nullptr};
        uint32_t           node_id;
    };
 
} // namespace Toon
