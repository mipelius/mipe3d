// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#include "Mipe3DCamera.h"

#include <gtx/transform.hpp>
#include <gtc/quaternion.hpp>

namespace mipe3d
{

Camera::Camera()
{

}
Camera::~Camera()
{

}
float Camera::getFieldOfView()
{
    return m_fieldOfView;
}
void Camera::setFieldOfView(float fieldOfView)
{
    m_fieldOfView = fieldOfView;
}
float Camera::getNear()
{
    return m_near;
}
void Camera::setNear(float near)
{
    m_near = near;
}
float Camera::getFar()
{
    return m_far;
}
void Camera::setFar(float far)
{
    m_far = far;
}

const glm::vec3& Camera::getPosition()
{
    return m_position;
}
void Camera::setPosition(const glm::vec3& position)
{
    m_position = position;
}
glm::vec3 Camera::getEulerAngles()
{
    return glm::eulerAngles(m_rotation);
}
void Camera::setEulerAngles(const glm::vec3& eulerAngles)
{
    m_rotation = glm::quat(eulerAngles);
}

glm::mat4x4 Camera::getProjectionMatrix()
{
    // NOTE: aspect ratio is fixed 4/3 for now
    static const float aspectRatio = 4.0f / 3.0f;
    return glm::perspective(m_fieldOfView, aspectRatio, m_near, m_far);
}

glm::mat4x4 Camera::getViewMatrix()
{
    auto translationMatrix = glm::translate(-m_position);
    auto rotationMatrix = glm::inverse(glm::mat4_cast(m_rotation));

    return rotationMatrix * translationMatrix;
}


Camera& camera()
{
    static Camera cameraInstance;
    return cameraInstance;
}

} // namespace mipe3d
