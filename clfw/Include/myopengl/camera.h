#ifndef  CAMERA_H
#define  CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

//摄像机默认值
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;//灵敏度
const float ZOOM = 45.0f;
class Camera {
public:
	//摄像机属性
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	//欧拉角
	float Yaw;
	float Pitch;

	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	/*
		Constructor with vectors
	*/
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f),float yaw = YAW,
		float pitch = PITCH):Front(glm::vec3(0.0f,0.0f,-1.0f)), MovementSpeed(SPEED),MouseSensitivity(SENSITIVITY),Zoom(ZOOM)
	{
		Position = pos;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	/*
	Constructor with scalar values
	*/
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
		:Front(glm::vec3(0.0f,0.0f,-1.0f)),MovementSpeed(SPEED),MouseSensitivity(SENSITIVITY),Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	/*
	返回 view 矩阵
	*/
	glm::mat4 GetViewMatrix() {
		return glm::lookAt(Position, Position + Front, Up);
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD) {
			Position += Front * velocity;

		}
		else if (direction == BACKWARD) {
			Position -= Front * velocity;
		}
		else if (direction == LEFT) {
			Position -= Right * velocity;
		}
		else if (direction == RIGHT) {
			Position += Right * velocity;
		}
	}
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}
	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

private :
	void updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
		front.y = sin(glm::radians(Pitch));
		front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
		Front = glm::normalize(front);
		//重新计算right and up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};
#endif // ! CAMERA_H

