#include "Camera.h"


Camera::Camera(float aspectRatio, float fov, float near, float far)
    :
    AspectRatio(aspectRatio),
    FOV(fov),
    NearPlane(near),
    FarPlane(far)
{
    glm::vec3 camPos(0.0f, 0.0f, 1.0f);
    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    glm::vec3 camFront(0.0f, 0.0f, -1.0f);
    ViewMatrix = glm::mat4(1.0f);
    ViewMatrix = glm::lookAt(camPos, camPos + camFront, worldUp);

    UpdateProjectionMatrix();
}

Camera::~Camera()
{
}

//SETTERS AND GETTERS
void Camera::SetFOV(float fov)
{
    FOV = fov;
    UpdateProjectionMatrix();
}

float Camera::GetFOV()
{
    return FOV;
}

void Camera::SetNearPlane(float near)
{
    NearPlane = near;
    UpdateProjectionMatrix();
}

float Camera::GetNearPlane()
{
    return NearPlane;
}

void Camera::SetFarPlane(float far)
{
    FarPlane = far;
    UpdateProjectionMatrix();
}

float Camera::GetFarPlane()
{
    return FarPlane;
}

void Camera::SetAspectRatio(float aspectRatio)
{
    AspectRatio = aspectRatio;
    UpdateProjectionMatrix();
}

float Camera::GetAspectRatio()
{
    return AspectRatio;
}
//SETTERS AND GETTERS
//END


void Camera::UpdateProjectionMatrix()
{
    ProjectionMatrix = glm::perspective(
        glm::radians(FOV),
        static_cast<float>(AspectRatio),
        NearPlane,
        FarPlane
    );
}

glm::mat4 Camera::GetViewMatrix()
{
    return ViewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return ProjectionMatrix;
}

