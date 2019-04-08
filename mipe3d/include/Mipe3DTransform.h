#pragma once

#include "apidef.h"

#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/quaternion.hpp>

namespace mipe3d
{

class Transform
{
public:
    Transform();

    MIPE3D_API glm::mat4x4 getMatrix() const;

    MIPE3D_API const glm::vec3 &getPosition() const;
    MIPE3D_API void setPosition(const glm::vec3 &position);

    MIPE3D_API glm::vec3 getEulerAngles() const;
    MIPE3D_API void setEulerAngles(const glm::vec3 &rotation);

    MIPE3D_API const glm::vec3 &getScale() const;
    MIPE3D_API void setScale(const glm::vec3 &scale);

private:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::quat m_rotation = glm::quat();
    glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

} // namespace mipe3d