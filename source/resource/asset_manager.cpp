#include "core/base/macro.h"
#include "resource/asset_manager.h"
#include "resource/config_manager.h"
#include "function/global/global_context.h"
#include <filesystem>
#include <filesystem>

namespace Toon
{
    std::filesystem::path AssetManager::getFullPath(const std::string& relative_path) const
    {
        return std::filesystem::absolute(g_runtime_global_context.m_config_manager->getRootFolder() / relative_path);
    }

    std::pair<std::string, bool> AssetManager::ReadFile(const std::string& filepath) const {
        std::string result;
        bool fileExists = false;
        std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
        if (in)
        {
            fileExists = true;
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
            }
            else 
            {
                LOG_ERROR("Could not read from file '{0}'", filepath);
            }
        }
        else 
        {
            LOG_ERROR("Could not open file '{0}'", filepath);
        }

        return std::make_pair(std::move(result), fileExists);
    }


    bool AssetManager::WriteFile(const std::string& filepath, const std::string& content) const
    {
        std::ofstream out(filepath, std::ios::out | std::ios::binary);
        if (out) 
        {
            out.write(content.c_str(), content.size());
            out.close();
            return true;
        }
        else 
        {
            LOG_ERROR("Could not open file '{0}' for writing", filepath);
            return false;
        }
    }

    bool AssetManager::WriteFile(const std::string& filepath, const std::vector<uint32_t>& content) const {
        std::ofstream out(filepath, std::ios::out | std::ios::binary);
        if (out) 
        {
            out.write(reinterpret_cast<const char*>(content.data()), content.size() * sizeof(uint32_t));
            out.close();
            return true;
        }
        else 
        {
            LOG_ERROR("Could not open file '{0}' for writing", filepath);
            return false;
        }
    }

} // namespace Toon