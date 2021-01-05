#include "Camera.h"

void Camera::update(Controls* control)
{
	position += front * control->forward;
	position += up * control->up;
	position += (front.cross(up)).normalize() * control->right;

	control->forward = 0.0f;
	control->right = 0.0f;
	control->up = 0.0f;

	Maths::mat4 rollRotation = Maths::mat4::rotation(control->roll, front);
	up = Maths::vec3(
		(rollRotation * Maths::vec4(up, 1.0f)).values[0],
		(rollRotation * Maths::vec4(up, 1.0f)).values[1],
		(rollRotation * Maths::vec4(up, 1.0f)).values[2]
	).normalize();

	Maths::mat4 yawRotation = Maths::mat4::rotation(control->yaw, up);
	front = Maths::vec3(
		(yawRotation * Maths::vec4(front, 1.0f)).values[0],
		(yawRotation * Maths::vec4(front, 1.0f)).values[1],
		(yawRotation * Maths::vec4(front, 1.0f)).values[2]
	).normalize();

	Maths::mat4 pitchRotation = Maths::mat4::rotation(control->pitch, front.cross(up));
	front = Maths::vec3(
		(pitchRotation * Maths::vec4(front, 1.0f)).values[0],
		(pitchRotation * Maths::vec4(front, 1.0f)).values[1],
		(pitchRotation * Maths::vec4(front, 1.0f)).values[2]
	).normalize();
	up = Maths::vec3(
		(pitchRotation * Maths::vec4(up, 1.0f)).values[0],
		(pitchRotation * Maths::vec4(up, 1.0f)).values[1],
		(pitchRotation * Maths::vec4(up, 1.0f)).values[2]
	).normalize();

	control->pitch = 0.0f;
	control->yaw = 0.0f;
	control->roll = 0.0f;

	viewMatrix = Maths::mat4::lookat(position, front, up);
}
