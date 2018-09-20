#include "../Header/FSMath.h"

vec3 FSMath::EulerAngleToDirectionVector(const vec3& angle)
{
	float pitch = glm::radians(angle.x);
	float yaw = glm::radians(angle.y);
	float roll = glm::radians(angle.z);

	vec3 directionVector;
	directionVector.x = cos(pitch) * cos(yaw);
	directionVector.y = sin(pitch);
	directionVector.z = cos(pitch) * sin(yaw);

	return glm::normalize(directionVector);
}

vec3 FSMath::NanToZero(vec3 vector)
{
	vector.x = std::isnan(vector.x) ? 0 : vector.x;
	vector.y = std::isnan(vector.y) ? 0 : vector.y;
	vector.z = std::isnan(vector.z) ? 0 : vector.z;

	return vector;
}
