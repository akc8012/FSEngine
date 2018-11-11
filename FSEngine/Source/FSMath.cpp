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

// Returns a quaternion such that q*start = dest
quat FSMath::RotationBetweenVectors(vec3 start, vec3 dest)
{
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f)
	{
		// special case when vectors in opposite directions :
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		// This implementation favors a rotation around the Up axis,
		// since it's often what you want to do.
		rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), start);
		if (length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return angleAxis(glm::radians(180.0f), rotationAxis);
	}

	// Implementation from Stan Melax's Game Programming Gems 1 article
	rotationAxis = cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);
}

// Returns a quaternion that will make your object looking towards 'direction'.
// Similar to RotationBetweenVectors, but also controls the vertical orientation.
// This assumes that at rest, the object faces +Z.
// Beware, the first parameter is a direction, not the target point !
quat FSMath::LookAt(vec3 direction, vec3 desiredUp)
{
	if (length2(direction) < 0.0001f)
		return quat();

	// Recompute desiredUp so that it's perpendicular to the direction
	// You can skip that part if you really want to force desiredUp
	vec3 right = cross(direction, desiredUp);
	desiredUp = cross(right, direction);

	// Find the rotation between the front of the object (that we assume towards +Z,
	// but this depends on your model) and the desired direction
	quat rot1 = RotationBetweenVectors(vec3(0.0f, 0.0f, 1.0f), direction);
	// Because of the 1rst rotation, the up is probably completely screwed up. 
	// Find the rotation between the "up" of the rotated object, and the desired up
	vec3 newUp = rot1 * vec3(0.0f, 1.0f, 0.0f);
	quat rot2 = RotationBetweenVectors(newUp, desiredUp);

	// Apply them
	return rot2 * rot1; // remember, in reverse order.
}

float FSMath::RayIntersectPlaneDistance(const plane& plane, const ray& ray)
{
	// assuming vectors are all normalized
	vec3 originDifference = plane.origin - ray.origin;
	float denominator = glm::dot(plane.normal, ray.direction);

	return glm::dot(originDifference, plane.normal) / denominator;
}
