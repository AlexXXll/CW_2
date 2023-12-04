#include <cmath>
#include <vector>
#include <iostream>

class GraphicSpace
{
    GLFWwindow *window;

    static void errorOccurred(const char[]) noexcept(false);

    static void initGLFW() noexcept;

    static void initGLEW() noexcept;

    void resizeWindow(GLsizei *, GLsizei *) noexcept;

public:
    Window(GLsizei *, GLsizei *, const char *) noexcept;

    void SetWindowSizeCallback(GLFWwindowsizefun) noexcept;

    void SetKeyCallback(GLFWkeyfun) noexcept;

    void SetMouseButtonCallback(GLFWmousebuttonfun) noexcept;

    void SetCursorPosCallback(GLFWcursorposfun) noexcept;

    void Loop(void(*)(GLfloat)) noexcept;

    void Destroy() noexcept;
};

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    void updateCameraVectors() noexcept;

public:
    explicit
    Camera(glm::vec3 = glm::vec3(0.0f),
           glm::vec3 = glm::vec3(0.0f, 1.0f, 0.0f),
           GLfloat = -90.0f, GLfloat = 0.0f) noexcept;

    [[nodiscard]]
    glm::mat4 GetViewMatrix() const noexcept;

    void ProcessKeyboard(CameraMovement, GLfloat) noexcept;

    void ProcessMouseMovement(GLfloat, GLfloat, GLboolean = true) noexcept;
};

void Camera::updateCameraVectors() noexcept {
    glm::vec3 newFront;

    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) noexcept
        : front(glm::vec3(0.0f, 0.0f, -1.0f)),
          position(position),
          worldUp(up),
          yaw(yaw),
          pitch(pitch),
          right(glm::vec3(0.0f)),
          up(glm::vec3(0.0f)) {
    updateCameraVectors();
}

[[nodiscard]]
glm::mat4 Camera::GetViewMatrix() const noexcept {
    return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(const CameraMovement direction, const GLfloat deltaTime) noexcept {
    const GLfloat SPEED = 3.0f;
    GLfloat velocity = SPEED * deltaTime;
    switch (direction) {
    case FORWARD:
        position += glm::normalize(glm::vec3(front.x, 0, front.z)) * velocity;
        return;
    case BACKWARD:
        position -= glm::normalize(glm::vec3(front.x, 0, front.z)) * velocity;
        return;
    case LEFT:
        position -= glm::normalize(glm::vec3(right.x, 0, right.z)) * velocity;
        return;
    case RIGHT:
        position += glm::normalize(glm::vec3(right.x, 0, right.z)) * velocity;
        return;
    case UP:
        position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
        return;
    case DOWN:
        position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
        return;
    }
}

void Camera::ProcessMouseMovement(
        GLfloat xOffset, GLfloat yOffset,
        const GLboolean constrainPitch
) noexcept {
    const GLfloat SENSITIVITY = 0.18f;
    xOffset *= SENSITIVITY;
    yOffset *= SENSITIVITY;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }

    this->updateCameraVectors();
}

class MVec
{
public:
    
};

typedef MVec<float> MVecf;

class Sphere
{
public:
    MVec center;
    float radius, radius2;
    MVec surfaceColor, emissionColor;
    float transparency, reflection;
    Sphere(
        

};

MVec trace(

void render(const std::vector<Sphere> &spheres)
{
}

int main()
{
    return 0;
}