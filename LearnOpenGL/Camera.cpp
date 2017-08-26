#include "Camera.h"

#include <iostream>
//This is an FPS style camera using quaternions to prevent gimble lock
//The default coordinate system is given below
/*
             +y
              |
			  |     +z
			  |    /
			  |   /
			  |  /
			  | /
+X ------------/
*/


// An abstract camera class that processes input and calculates the corresponding View Matrices using quaternions for use in OpenGL
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float roll) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM), RollSpeed(ROLL_SPEED)
	{
		Position = position;
		WorldUp = glm::normalize(up);
		Yaw = yaw;
		Pitch = pitch;
		Roll = roll;
		Right = glm::normalize(glm::cross(WorldUp, Front));
		Front = glm::normalize(glm::cross(Right, WorldUp));
		glm::quat QuatAroundX = glm::angleAxis(glm::radians(Pitch), Right); //diffierence in how this works due coord-anite difference between program and glm
		glm::quat QuatAroundZ = glm::angleAxis(glm::radians(Roll), Front);
		glm::quat QuatAroundY = glm::angleAxis(glm::radians(Yaw), WorldUp);
		rotation_quat = glm::conjugate(QuatAroundZ * QuatAroundY * QuatAroundX); //* QuatAroundZ;
		
	}

	// Returns the view matrix calculated using quaternions to mat 4 conversion
glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 test = glm::mat4_cast(rotation_quat);
	test = glm::translate(test, Position* 1.0f);
	return glm::translate(glm::mat4_cast(rotation_quat), -Position); //WOOOOOOOOOOOOOOOOOOT
	//return glm::lookAt(Position, Position + Front, Up);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += glm::conjugate(rotation_quat)* (Front * velocity);
	if (direction == BACKWARD)
		Position -= glm::conjugate(rotation_quat)* (Front * velocity);
	if (direction == LEFT)
		Position += glm::conjugate(rotation_quat)* (Right * velocity);
	if (direction == RIGHT)
		Position -= glm::conjugate(rotation_quat)* (Right * velocity);

	if(direction == ROLL_LEFT)
		rotation_quat = glm::normalize(glm::rotate(rotation_quat, glm::radians(RollSpeed), rotation_quat * Front));

	if(direction == ROLL_RIGHT)
		rotation_quat = glm::normalize(glm::rotate(rotation_quat, glm::radians(RollSpeed), rotation_quat * (Front * -1.0f)));

	std::cout << "x:" << Position.x << std::endl;
	std::cout << "z:" << Position.z << std::endl;
}
glm::vec3 Camera::GetPostion() {
	return glm::vec3(Position);
}

glm::vec3 Camera::GetFront() {
	return glm::vec3(glm::conjugate(rotation_quat) *Front);
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;
	
	glm::quat QuatAroundX = glm::angleAxis(glm::radians(yoffset), Right); //diffierence in how this works due coord-anite difference between program and glm
	glm::quat QuatAroundY = glm::angleAxis(glm::radians(xoffset), WorldUp);
	rotation_quat = QuatAroundX * rotation_quat * QuatAroundY; 
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}
