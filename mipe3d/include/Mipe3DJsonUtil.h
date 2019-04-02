#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>

namespace mipe3d
{

enum class JsonValueParserError
{
    NONE,
    NOT_FOUND,
    INCORRECT_TYPE
};

struct JsonValueParserStatus
{
    JsonValueParserError error;
    std::string errorMessage;
};

bool loadJson(const std::string& filePath, nlohmann::json& jsonOut);

std::string parseStringFromJson(
    const nlohmann::json& json,
    const std::string& key,
    JsonValueParserStatus& statusOut);

} // namespace mipe3d