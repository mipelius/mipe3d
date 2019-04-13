// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#include "Mipe3DTransform.h"

#include <gtx/transform.hpp>

namespace mipe3d
{

Transform::Transform()
{
}

glm::mat4x4 Transform::getMatrix() const
{
    auto scaleMatrix = glm::scale(m_scale);
    auto rotationMatrix = glm::mat4_cast(m_rotation);
    auto translationMatrix = glm::translate(m_position);

    return translationMatrix * rotationMatrix * scaleMatrix;
}

const glm::vec3 &Transform::getPosition() const
{
    return m_position;
}

void Transform::setPosition(const glm::vec3 &position)
{
    m_position = position;
}

glm::vec3 Transform::getEulerAngles() const
{
    return glm::eulerAngles(m_rotation);
}

void Transform::setEulerAngles(const glm::vec3 &rotation)
{
    m_rotation = glm::quat(rotation);
}

const glm::vec3 &Transform::getScale() const
{
    return m_scale;
}

void Transform::setScale(const glm::vec3 &scale)
{
    m_scale = scale;
}

} // namespace mipe3d