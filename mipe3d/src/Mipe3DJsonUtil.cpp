#include "Mipe3DJsonUtil.h"
#include "Mipe3DLog.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

namespace mipe3d
{

// ---- internal functions ----

nlohmann::json getJsonValue(
    const nlohmann::json& json,
    const std::string& key,
    JsonValueParserStatus& statusOut)
{
    auto resultJson = json.find(key);

    if (resultJson == json.end())
    {
        statusOut.error = JsonValueParserError::NOT_FOUND;
        statusOut.errorMessage =
            std::string("Key \"") + key + "\" missing.";
        return nullptr;
    }
    statusOut.error = JsonValueParserError::NONE;

    return *resultJson;
}

// ---- public functions ----

bool loadJson(const std::string& filePath, nlohmann::json& jsonOut)
{
    std::ifstream filestream(filePath, std::ifstream::in);
    if (!filestream.good())
    {
        MIPE3D_LOG_ERROR(
            std::string("Could not read file \"") + filePath + "\"."
        );
        return false;
    }
    try
    {
        filestream >> jsonOut;
    }
    catch (nlohmann::json::parse_error)
    {
        MIPE3D_LOG_ERROR(
            std::string("Corrupted json \"") + filePath + "\"."
        );
        return false;
    }
    catch (...)
    {
        MIPE3D_LOG_ERROR(
            std::string("Failed parsing json \"") + filePath + "\"."
        );
        return false;
    }

    return true;
}

std::string parseStringFromJson(
    const nlohmann::json& json,
    const std::string& key,
    JsonValueParserStatus& statusOut)
{
    auto resultJson = getJsonValue(json, key, statusOut);
    std::string result;

    if (statusOut.error != JsonValueParserError::NONE)
    {
        return result;
    }
    if (!resultJson.is_string())
    {
        statusOut.error = JsonValueParserError::INCORRECT_TYPE;
        statusOut.errorMessage =
            std::string("Value type of \"") +
            key + \
            "\" must be string.";

        return result;
    }

    return resultJson.get<std::string>();
}

} // namespace mipe3d