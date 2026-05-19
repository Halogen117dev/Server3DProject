#include "GameManager.h"


Camera::Camera(GameManager* game, float aspectRatio, float fov, float nearPlane, float farPlane)
    :
    Game(game),
    AspectRatio(aspectRatio),
    FOV(fov),
    NearPlane(nearPlane),
    FarPlane(farPlane)
{
    Speed = 0.5f;
    Sensitivity = 1.25f;

    Position = glm::vec3(0.0f, 1.0f, 4.0f);
    Rotation = glm::vec3(0.0f, -90.0f, 0.0f);

    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);

    ViewMatrix = glm::mat4(1.0f);
    ViewMatrix = glm::lookAt(Position, Position + Front, Up);

    UpdateProjectionMatrix();
}

Camera::~Camera()
{
}

void Camera::Update()
{
    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(Rotation.y)) * glm::cos(glm::radians(Rotation.x));
    direction.z = glm::sin(glm::radians(Rotation.y)) * glm::cos(glm::radians(Rotation.x));
    direction.y = glm::sin(glm::radians(Rotation.x));
    Front = glm::normalize(direction);


    glm::vec3 trans(0.0f);
    if (Game->Input->IsKeyPressed("W"))
    {
        trans += 1.0f * Front;
    }
    if (Game->Input->IsKeyPressed("S"))
    {
        trans -= 1.0f * Front;
    }
    if (Game->Input->IsKeyPressed("A"))
    {
        trans -= 1.0f * glm::normalize(glm::cross(Front, Up));
    }
    if (Game->Input->IsKeyPressed("D"))
    {
        trans += 1.0f * glm::normalize(glm::cross(Front, Up));
    }

    if (Game->Input->IsKeyPressed("UP"))
    {
        trans += 1.0f * Up;
    }
    if (Game->Input->IsKeyPressed("DOWN"))
    {
        trans -= 1.0f * Up;
    }

    if (Game->Input->IsKeyPressed("RMB") && !Game->Input->IsKeyPressed("LMB"))
    {
        wxPoint delta = Game->Input->GetCapturedMouseDelta();

        if (delta.y > 0)
            Rotation.x += 1.0f * Sensitivity;
        if (delta.y < 0)
            Rotation.x -= 1.0f * Sensitivity;
        if (delta.x > 0)
            Rotation.y += 1.0f * Sensitivity;
        if (delta.x < 0)
            Rotation.y -= 1.0f * Sensitivity;
    }

    if (Rotation.x > 75.0f)
        Rotation.x = 75.0f;
    if (Rotation.x < -75.0f)
        Rotation.x = -75.0f;

    if (Rotation.y > 360.0f)
        Rotation.y = Rotation.y - 360.0f;
    if (Rotation.y < -360.0f)
        Rotation.y = Rotation.y + 360.0f;

    //trans = glm::normalize(trans);
    if(glm::length(trans))
        trans = trans / glm::length(trans);

    if(Game->Input->IsKeyPressed("Shift"))
        Translate(trans * Speed * 2.0f * 0.000005f * GLfloat(Game->DeltaTime()));
    else
        Translate(trans * Speed * 0.000005f * GLfloat(Game->DeltaTime()));


    UpdateProjectionMatrix();
    UpdateViewMatrix();
}


void Camera::SetTransform(glm::vec3 pos, glm::vec3 rot)
{
    Position = pos;
    Rotation = rot;
}

//TRANSFORMATION SLOP
void Camera::Transform(glm::vec3 pos, glm::vec3 rot)
{
    Position += pos;
    Rotation += rot;
}

void Camera::SetPosition(glm::vec3 pos)
{
    Position = pos;
}

glm::vec3 Camera::GetPosition()
{
    return Position;
}

void Camera::SetRotation(glm::vec3 rot)
{
    Rotation = rot;
}


void Camera::Translate(glm::vec3 translationVal)
{
    Position += translationVal;
}

void Camera::Rotate(glm::vec3 rotationVal)
{
    Rotation += rotationVal;
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

void Camera::SetNearPlane(float nearPlane)
{
    NearPlane = nearPlane;
    UpdateProjectionMatrix();
}

float Camera::GetNearPlane()
{
    return NearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
    FarPlane = farPlane;
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

void Camera::UpdateViewMatrix()
{
    ViewMatrix = glm::mat4(1.0f);
    ViewMatrix = glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetViewMatrix()
{
    return ViewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return ProjectionMatrix;
}

