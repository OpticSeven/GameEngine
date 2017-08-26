#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ROLL_LEFT,
	ROLL_RIGHT,
};

// Default camera values
const float YAW =  0.0f;
const float PITCH = 0.0f;
const float ROLL = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVTY = 0.1f;
const float ZOOM = 45.0f;
const float ROLL_SPEED = 5.0f;

class Camera
{
public:
	float MovementSpeed;
	float RollSpeed;
	float MouseSensitivity;
	float Zoom;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float roll = ROLL);

	// Returns the view matrix calculated using quaternions to mat 4 conversion
	glm::mat4 GetViewMatrix();

	glm::vec3 Camera::GetPostion();

	glm::vec3 Camera::GetFront();

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);
private:
	// Camera Attributes
	glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);;
	glm::vec3 Position;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	glm::quat rotation_quat;
	// Eular Angles
	float Yaw;
	float Pitch;
	float Roll;

};

#endif