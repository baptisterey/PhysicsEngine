#include "camera.h"

Camera::Camera(float viewAngle, float nearPlane, float farPlane, int viewWidth, int viewHeight, Vector3 position, Quaternion rotation) :
	position(position), rotation(rotation), currentRotationChanges(0.f, 0.f, 0.f),
	viewAngle(viewAngle), nearPlane(nearPlane), farPlane(farPlane)
{
	computeViewMatrix();
	setAspectRatio(viewWidth, viewHeight);   // Contains a call to "computeProjectionMatrix"
}

Camera::~Camera()
{
}

#define PROJECTION_FUNCTIONS {
void Camera::setAspectRatio(int viewWidth, int viewHeight) {
	aspectRatio = viewWidth * 1.0f / viewHeight;
	computeProjectionMatrix();
}
void Camera::setPlanes(float nearPlane, float farPlane) {
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	computeProjectionMatrix();
}
void Camera::setViewAngle(float angle) {
	this->viewAngle = angle;
	computeProjectionMatrix();
}
#define PROJECTION_FUNCTIONS_END }

#define TRANSLATE_FUNCTIONS {
void Camera::translate(Vector3 translationVector) {
	Vector3 directionVector, upVector, xVector;
	getCameraAxis(directionVector, upVector, xVector);

	// Translation from the camera point of view (not from the point of view of the global axes)
	Vector3 newPosition = xVector * translationVector.x + upVector * translationVector.y + directionVector * translationVector.z;
	position += newPosition;

	computeViewMatrix();
}
void Camera::translateX(float x) {
	translate(Vector3(x, 0, 0));
}
void Camera::translateY(float y) {
	translate(Vector3(0, y, 0));
}
void Camera::translateZ(float z) {
	translate(Vector3(0, 0, z));
}
Vector3 Camera::getPosition() {
	return position;
}
#define TRANSLATE_FUNCTIONS_END }

#define ROTATION_FUNCTIONS {
void Camera::rotateX(float angle) {
	currentRotationChanges.x += angle;
	computeViewMatrix();
}
void Camera::rotateY(float angle) {
	currentRotationChanges.y += angle;
	computeViewMatrix();
}
void Camera::rotateZ(float angle) {
	currentRotationChanges.z += angle;
	computeViewMatrix();
}
void Camera::validateCurrentRotation() {
	rotation = getCurrentRotation();
	currentRotationChanges = Vector3(0, 0, 0);
}
Quaternion Camera::getCurrentRotation() {
	Vector3 directionVector, upVector, xVector;
	getCameraAxis(directionVector, upVector, xVector);

	// Rotation around the global y axis and the camera x axis
	Quaternion newRotation = Quaternion::fromAngleAndAxis(currentRotationChanges.y, Vector3(0.f, 1.f, 0.f));
	newRotation *= Quaternion::fromAngleAndAxis(currentRotationChanges.x, xVector);

	return (newRotation * rotation).normalized();
}
#define ROTATION_FUNCTIONS_END }

#define MATRIXES_FUNCTIONS {
void Camera::computeViewMatrix() {
	Vector3 directionVector, upVector;
	getCameraAxis(directionVector, upVector, true);

	projectionMatrix = Matrix4::Identity();
	viewMatrix = Matrix4::LookAt(position, position + directionVector, upVector);
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}
void Camera::computeProjectionMatrix() {
	projectionMatrix = Matrix4::PerspectiveFov(viewAngle, aspectRatio, nearPlane, farPlane);
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}
Matrix4 Camera::getViewMatrix() {
	return viewMatrix;
}
Matrix4 Camera::getProjectionMatrix() {
	return projectionMatrix;
}
Matrix4 Camera::getViewProjectionMatrix()
{
	return viewProjectionMatrix;
}
#define MATRIXES_FUNCTIONS_END }

#define AXES {
const Vector3 Camera::initialDirectionVector(0.f, 0.f, -1.f);
const Vector3 Camera::initialUpVector(0.f, -1.f, 0.f);

void Camera::getCameraAxis(Vector3& directionAxis, Vector3& upAxis, bool useCurrentAxis) {
	Quaternion cameraRotation;

	if (!useCurrentAxis) {
		cameraRotation = rotation;
	}
	else {
		cameraRotation = getCurrentRotation();
	}

	directionAxis = Vector3::Normalized(cameraRotation.rotatedVector(initialDirectionVector));
	upAxis = Vector3::Normalized(cameraRotation.rotatedVector(initialUpVector));
}

void Camera::getCameraAxis(Vector3& directionAxis, Vector3& upAxis, Vector3& xAxis, bool useCurrentAxis) {
	getCameraAxis(directionAxis, upAxis, useCurrentAxis);
	xAxis = Vector3::Normalized(Vector3::Cross(directionAxis, upAxis));
}
#define AXES_END }
