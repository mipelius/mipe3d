#pragma once

#include <vec3.hpp>
#include <mat4x4.hpp>
#include <list>

namespace mipe3d
{

class Transform
{
public:
    Transform();

    glm::mat4x4 getMatrix() const;

    const glm::vec3 &getPosition() const;
    void setPosition(const glm::vec3 &position);

    const glm::vec3 &getEulerAngles() const;
    void setEulerAngles(const glm::vec3 &rotation);

    const glm::vec3 &getScale() const;
    void setScale(const glm::vec3 &scale);

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

} // namespace mipe3d