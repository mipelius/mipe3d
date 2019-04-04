#include "Mipe3DCamera.h"

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
    return 0.0f;
}
void Camera::setFieldOfView(float fieldOfView)
{
}
float Camera::getNear()
{
    return 0.0f;
}
void Camera::setNear(float near)
{
}
float Camera::getFar()
{
    return 0.0f;
}
void Camera::setFar(float far)
{
}

const glm::vec3& Camera::getPosition()
{
    return m_position;
}
void Camera::setPosition(const glm::vec3& position)
{
    m_position = position;
}
const glm::vec3& Camera::getEulerAngles()
{
    return m_rotation;
}
void Camera::setEulerAngles(const glm::vec3& eulerAngles)
{
    m_rotation = eulerAngles;
}

glm::mat4x4 Camera::getProjectionMatrix()
{
    return glm::mat4x4();
}
glm::mat4x4 Camera::getViewMatrix()
{
    return glm::mat4x4();
}


Camera& camera()
{
    static Camera cameraInstance;
    return cameraInstance;
}

} // namespace mipe3d
