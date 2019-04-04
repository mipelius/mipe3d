#include "Mipe3DTransform.h"

namespace mipe3d
{

Transform::Transform()
{
}

glm::mat4x4 Transform::getMatrix() const
{
    return glm::mat4x4(1);
}

const glm::vec3 &Transform::getPosition() const
{
    return m_position;
}

void Transform::setPosition(const glm::vec3 &position)
{
    m_position = position;
}

const glm::vec3 &Transform::getEulerAngles() const
{
    return m_rotation;
}

void Transform::setEulerAngles(const glm::vec3 &rotation)
{
    m_rotation = rotation;
}

const glm::vec3 &Transform::getScale() const
{
    return m_scale;
}

void Transform::setScale(const glm::vec3 &scale)
{
    m_scale = scale;
}

} // namespace Ape