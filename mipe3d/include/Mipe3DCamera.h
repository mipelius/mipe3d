// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "apidef.h"
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/quaternion.hpp>

namespace mipe3d
{

class Camera
{
    friend MIPE3D_API Camera& camera();

public:
    MIPE3D_API float getFieldOfView();
    MIPE3D_API void setFieldOfView(float fieldOfView);
    MIPE3D_API float getNear();
    MIPE3D_API void setNear(float near);
    MIPE3D_API float getFar();
    MIPE3D_API void setFar(float far);

    MIPE3D_API const glm::vec3& getPosition();
    MIPE3D_API void setPosition(const glm::vec3& position);
    MIPE3D_API glm::vec3 getEulerAngles();
    MIPE3D_API void setEulerAngles(const glm::vec3& eulerAngles);

    MIPE3D_API glm::mat4x4 getProjectionMatrix();
    MIPE3D_API glm::mat4x4 getViewMatrix();

private:
    Camera();
    ~Camera();

    float m_fieldOfView = glm::radians(45.0f);
    float m_near = 0.1f;
    float m_far = 100.0f;

    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::quat m_rotation = glm::quat();
};

// ---- singleton accessor ----

MIPE3D_API Camera& camera();

} // namespace mipe3d