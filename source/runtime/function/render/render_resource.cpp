#include "runtime/function/render/render_resource.h"
#include "runtime/function/render/render_camera.h"
#include "runtime/function/render/render_helper.h"
#include "runtime/function/render/opengl/opengl_rhi.h"
#include "runtime/function/render/passes/main_camera_pass.h"
#include "runtime/core/base/macro.h"
#include <stdexcept>
#include <algorithm>
#include <filesystem>
#include <vector>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
namespace Toon
{
    void RenderResource::clear()
    {
    }

    void RenderResource::uploadGlobalRenderResource(std::shared_ptr<RHI> rhi, LevelResourceDesc level_resource_desc)
    {
        //// sky box irradiance
        //SkyBoxIrradianceMap skybox_irradiance_map = level_resource_desc.m_ibl_resource_desc.m_skybox_irradiance_map;
        //std::shared_ptr<Texture2D> irradiace_pos_x_map = Texture2D::Create(skybox_irradiance_map.m_positive_x_map);
        //std::shared_ptr<Texture2D> irradiace_neg_x_map = Texture2D::Create(skybox_irradiance_map.m_negative_x_map);
        //std::shared_ptr<Texture2D> irradiace_pos_y_map = Texture2D::Create(skybox_irradiance_map.m_positive_y_map);
        //std::shared_ptr<Texture2D> irradiace_neg_y_map = Texture2D::Create(skybox_irradiance_map.m_negative_y_map);
        //std::shared_ptr<Texture2D> irradiace_pos_z_map = Texture2D::Create(skybox_irradiance_map.m_positive_z_map);
        //std::shared_ptr<Texture2D> irradiace_neg_z_map = Texture2D::Create(skybox_irradiance_map.m_negative_z_map);

        //// sky box specular
        //SkyBoxSpecularMap            skybox_specular_map = level_resource_desc.m_ibl_resource_desc.m_skybox_specular_map;
        //std::shared_ptr<Texture2D> specular_pos_x_map = Texture2D::Create(skybox_specular_map.m_positive_x_map);
        //std::shared_ptr<Texture2D> specular_neg_x_map = Texture2D::Create(skybox_specular_map.m_negative_x_map);
        //std::shared_ptr<Texture2D> specular_pos_y_map = Texture2D::Create(skybox_specular_map.m_positive_y_map);
        //std::shared_ptr<Texture2D> specular_neg_y_map = Texture2D::Create(skybox_specular_map.m_negative_y_map);
        //std::shared_ptr<Texture2D> specular_pos_z_map = Texture2D::Create(skybox_specular_map.m_positive_z_map);
        //std::shared_ptr<Texture2D> specular_neg_z_map = Texture2D::Create(skybox_specular_map.m_negative_z_map);

        //// brdf
        //std::shared_ptr<Texture2D> brdf_map = Texture2D::Create(level_resource_desc.m_ibl_resource_desc.m_brdf_map);


        //// create IBL textures, take care of the texture order
        //std::array<std::shared_ptr<Texture2D>, 6> irradiance_maps = { irradiace_pos_x_map,
        //                                                               irradiace_neg_x_map,
        //                                                               irradiace_pos_z_map,
        //                                                               irradiace_neg_z_map,
        //                                                               irradiace_pos_y_map,
        //                                                               irradiace_neg_y_map };
        //std::array<std::shared_ptr<Texture2D>, 6> specular_maps = { specular_pos_x_map,
        //                                                             specular_neg_x_map,
        //                                                             specular_pos_z_map,
        //                                                             specular_neg_z_map,
        //                                                             specular_pos_y_map,
        //                                                             specular_neg_y_map };
       
    }

    void RenderResource::uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi, 
        RenderEntity render_entity, 
        RenderMeshData mesh_data, 
        RenderMaterialData material_data)
    {
        getOrCreateOpenGLMesh(rhi, render_entity, mesh_data);
        getOrCreateOpenGLMaterial(rhi, render_entity, material_data);
    }

    void RenderResource::uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi, 
        RenderEntity render_entity, 
        RenderMeshData mesh_data)
    {
        getOrCreateOpenGLMesh(rhi, render_entity, mesh_data);
    }

    void RenderResource::uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi, 
        RenderEntity render_entity, 
        RenderMaterialData material_data)
    {
        getOrCreateOpenGLMaterial(rhi, render_entity, material_data);
    }

    void RenderResource::updatePerFrameBuffer(std::shared_ptr<RenderScene> render_scene, std::shared_ptr<RenderCamera> camera)
    {

    }
    OpenGLMesh& RenderResource::getEntityMesh(RenderEntity entity)
    {
        size_t assetid = entity.m_mesh_asset_id;

        auto it = m_opengl_meshes.find(assetid);
        if (it == m_opengl_meshes.end())
        {
            LOG_FATAL("ailed to get entity mesh");
            
        }
        return it->second;
    }

    OpenGLMaterial& RenderResource::getEntityMaterial(RenderEntity entity)
    {
        size_t assetid = entity.m_material_asset_id;

        auto it = m_opengl_pbr_materials.find(assetid);
        if (it == m_opengl_pbr_materials.end())
        {
            LOG_FATAL("failed to get entity material");
            
        }
        return it->second;
    }

    RenderMeshData RenderResource::loadMeshData(const MeshSourceDesc& source, AxisAlignedBox& bounding_box)
    {
        std::shared_ptr<AssetManager> asset_manager = g_runtime_global_context.m_asset_manager;
        ASSERT(asset_manager);

        RenderMeshData ret;

        if (std::filesystem::path(source.m_mesh_file).extension() == ".obj")
        {
            ret.m_static_mesh_data = loadStaticMesh(source.m_mesh_file, bounding_box);
        }
        else
        {
            //anim
        }

        m_bounding_box_cache_map.insert(std::make_pair(source, bounding_box));

        return ret;
    }

    RenderMaterialData RenderResource::loadMaterialData(const MaterialSourceDesc& source)
    {
        return RenderMaterialData();
    }

    AxisAlignedBox RenderResource::getCachedBoudingBox(const MeshSourceDesc& source) const
    {
        return AxisAlignedBox();
    }

    StaticMeshData RenderResource::loadStaticMesh(std::string filename, AxisAlignedBox& bounding_box)
    {
        StaticMeshData mesh_data;

        tinyobj::ObjReader       reader;
        tinyobj::ObjReaderConfig reader_config;
        reader_config.vertex_color = false;
        if (!reader.ParseFromFile(filename, reader_config))
        {
            if (!reader.Error().empty())
            {
                LOG_ERROR("loadMesh {} failed, error: {}", filename, reader.Error());
            }
            assert(0);
        }

        if (!reader.Warning().empty())
        {
            LOG_WARN("loadMesh {} warning, warning: {}", filename, reader.Warning());
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();

        std::vector<MeshVertexDataDefinition> mesh_vertices;

        for (size_t s = 0; s < shapes.size(); s++)
        {
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                bool with_normal = true;
                bool with_texcoord = true;

                Vector3 vertex[3];
                Vector3 normal[3];
                Vector2 uv[3];

                // only deals with triangle faces
                if (fv != 3)
                {
                    continue;
                }

                // expanding vertex data is not efficient and is for testing purposes only
                for (size_t v = 0; v < fv; v++)
                {
                    auto idx = shapes[s].mesh.indices[index_offset + v];
                    auto vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                    auto vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                    auto vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                    vertex[v].x = static_cast<float>(vx);
                    vertex[v].y = static_cast<float>(vy);
                    vertex[v].z = static_cast<float>(vz);

                    bounding_box.merge(Vector3(vertex[v].x, vertex[v].y, vertex[v].z));

                    if (idx.normal_index >= 0)
                    {
                        auto nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                        auto ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                        auto nz = attrib.normals[3 * size_t(idx.normal_index) + 2];

                        normal[v].x = static_cast<float>(nx);
                        normal[v].y = static_cast<float>(ny);
                        normal[v].z = static_cast<float>(nz);
                    }
                    else
                    {
                        with_normal = false;
                    }

                    if (idx.texcoord_index >= 0)
                    {
                        auto tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                        auto ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];

                        uv[v].x = static_cast<float>(tx);
                        uv[v].y = static_cast<float>(ty);
                    }
                    else
                    {
                        with_texcoord = false;
                    }
                }
                index_offset += fv;

                if (!with_normal)
                {
                    Vector3 v0 = vertex[1] - vertex[0];
                    Vector3 v1 = vertex[2] - vertex[1];
                    normal[0] = v0.crossProduct(v1).normalisedCopy();
                    normal[1] = normal[0];
                    normal[2] = normal[0];
                }

                if (!with_texcoord)
                {
                    uv[0] = Vector2(0.5f, 0.5f);
                    uv[1] = Vector2(0.5f, 0.5f);
                    uv[2] = Vector2(0.5f, 0.5f);
                }

                Vector3 tangent{ 1, 0, 0 };
                {
                    Vector3 edge1 = vertex[1] - vertex[0];
                    Vector3 edge2 = vertex[2] - vertex[1];
                    Vector2 deltaUV1 = uv[1] - uv[0];
                    Vector2 deltaUV2 = uv[2] - uv[1];

                    auto divide = deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y;
                    if (divide >= 0.0f && divide < 0.000001f)
                        divide = 0.000001f;
                    else if (divide < 0.0f && divide > -0.000001f)
                        divide = -0.000001f;

                    float df = 1.0f / divide;
                    tangent.x = df * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
                    tangent.y = df * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
                    tangent.z = df * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
                    tangent = (tangent).normalisedCopy();
                }

                for (size_t i = 0; i < 3; i++)
                {
                    MeshVertexDataDefinition mesh_vert{};

                    mesh_vert.x = vertex[i].x;
                    mesh_vert.y = vertex[i].y;
                    mesh_vert.z = vertex[i].z;

                    mesh_vert.nx = normal[i].x;
                    mesh_vert.ny = normal[i].y;
                    mesh_vert.nz = normal[i].z;

                    mesh_vert.u = uv[i].x;
                    mesh_vert.v = uv[i].y;

                    mesh_vert.tx = tangent.x;
                    mesh_vert.ty = tangent.y;
                    mesh_vert.tz = tangent.z;

                    mesh_vertices.push_back(mesh_vert);
                }
            }
        }

        uint32_t stride = sizeof(MeshVertexDataDefinition);
        mesh_data.m_vertex_buffer = std::make_shared<BufferData>(mesh_vertices.size() * stride);
        mesh_data.m_index_buffer = std::make_shared<BufferData>(mesh_vertices.size() * sizeof(uint32_t));

        assert(mesh_vertices.size() <= std::numeric_limits<uint32_t>::max());
 

        uint32_t* indices = (uint32_t*)mesh_data.m_index_buffer->m_data;
        for (size_t i = 0; i < mesh_vertices.size(); i++)
        {
            ((MeshVertexDataDefinition*)(mesh_data.m_vertex_buffer->m_data))[i] = mesh_vertices[i];
            indices[i] = static_cast<uint32_t>(i);
        }
        return mesh_data;
    }

    OpenGLMesh& RenderResource::getOrCreateOpenGLMesh(std::shared_ptr<RHI> rhi, RenderEntity entity, RenderMeshData mesh_data)
    {
        size_t assetid = entity.m_mesh_asset_id;

        auto it = m_opengl_meshes.find(assetid);
        if (it != m_opengl_meshes.end())
        {
            return it->second;
        }
        else
        {
            OpenGLMesh temp;
            auto       res = m_opengl_meshes.insert(std::make_pair(assetid, std::move(temp)));
            assert(res.second);

            uint32_t index_buffer_size = static_cast<uint32_t>(mesh_data.m_static_mesh_data.m_index_buffer->m_size);
            void* index_buffer_data = mesh_data.m_static_mesh_data.m_index_buffer->m_data;

            uint32_t vertex_buffer_size = static_cast<uint32_t>(mesh_data.m_static_mesh_data.m_vertex_buffer->m_size);
            MeshVertexDataDefinition* vertex_buffer_data = reinterpret_cast<MeshVertexDataDefinition*>(mesh_data.m_static_mesh_data.m_vertex_buffer->m_data);

            OpenGLMesh& now_mesh = res.first->second;
            updateMeshData(rhi, index_buffer_size, index_buffer_data, vertex_buffer_size, vertex_buffer_data, now_mesh);

            return now_mesh;
        }
    }

    OpenGLMaterial& RenderResource::getOrCreateOpenGLMaterial(std::shared_ptr<RHI> rhi, RenderEntity entity, RenderMaterialData material_data)
    {
        size_t assetid = entity.m_material_asset_id;

        auto it = m_opengl_pbr_materials.find(assetid);
        if (it != m_opengl_pbr_materials.end())
        {
            return it->second;
        }
        else
        {
            OpenGLMaterial temp;
            auto              res = m_opengl_pbr_materials.insert(std::make_pair(assetid, std::move(temp)));
            assert(res.second);

            OpenGLMaterial& now_material = res.first->second;

            return now_material;
        }


    }
    void RenderResource::updateMeshData(std::shared_ptr<RHI> rhi, uint32_t index_buffer_size, void* index_buffer_data, uint32_t vertex_buffer_size, MeshVertexDataDefinition* vertex_buffer_data, OpenGLMesh& now_mesh)
    {
        now_mesh.VAO = VertexArray::Create();

        assert(0 == (vertex_buffer_size % sizeof(MeshVertexDataDefinition)));   

        std::shared_ptr<BufferLayout> layout = std::make_shared<BufferLayout>();
        layout->push("position", DataType::Float3);
        layout->push("normal", DataType::Float3);
        layout->push("tangent", DataType::Float3);     

        std::shared_ptr<VertexBuffer> vbo = VertexBuffer::Create(reinterpret_cast<float*>(vertex_buffer_data), vertex_buffer_size * sizeof(MeshVertexDataDefinition));
        std::shared_ptr<IndexBuffer> ibo = IndexBuffer::Create(reinterpret_cast<uint32_t*>(index_buffer_data), index_buffer_size * sizeof(uint32_t));
        
        now_mesh.VAO->AddBuffer(layout, vbo);
        now_mesh.VAO->SetIndexBuffer(ibo);
    }
}