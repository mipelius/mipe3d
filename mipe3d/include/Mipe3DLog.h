#pragma once

#include "apidef.h"

#include <iostream>
#include <string>
#include <vec3.hpp>
#include <mat4x4.hpp>

// NOTE: for verbose logging (showing file, line number)
// #define MIPE3D_LOG_VERBOSE

// ---- internal helpers, not meant to be used by the client code ----

MIPE3D_API std::ostream& operator << (
    std::ostream& out, const glm::vec3& vec3);

MIPE3D_API std::ostream& operator << (
    std::ostream& out, const glm::mat4x4& mat4x4);

#ifdef MIPE3D_LOG_VERBOSE
#define _MIPE3D_LOG_INTERNAL(outputStream, preMessage, message) \
    outputStream << preMessage << message <<                    \
    " [" << __FILE__ << ", " << __LINE__ << "]" << std::endl;
#else
#define _MIPE3D_LOG_INTERNAL(outputStream, preMessage, message) \
    outputStream << preMessage << message << std::endl;
#endif

// ---- actual logging macros for client ----

#define MIPE3D_LOG(message)                                 \
    _MIPE3D_LOG_INTERNAL(std::cout, "", message)

#define MIPE3D_LOG_WARNING(message)                         \
    _MIPE3D_LOG_INTERNAL(std::cout, "WARNING: ", message)

#define MIPE3D_LOG_ERROR(message)                           \
    _MIPE3D_LOG_INTERNAL(std::cerr, "ERROR: ", message)