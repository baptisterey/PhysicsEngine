#pragma once

#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"
#include "../Math/Quaternion.h";

#include <GL\glew.h>
#include <SDL_opengl.h>

class Camera
{
public:
	Camera(float viewAngle, float nearPlane, float farPlane,
		int viewWidth = 1, int viewHeight = 1,
		Vector3 position = Vector3(0.f, 0.f, 0.f),
		Quaternion rotation = Quaternion::fromEulerAngles(0.f, 0.f, 0.f));
	~Camera();

#define CAMERA_TRANSLATE_FUNCTIONS {
	void translate(Vector3 translationVector);
	void translateX(float x);
	void translateY(float y);
	void translateZ(float z);
	Vector3 getPosition();
#define CAMERA_TRANSLATE_FUNCTIONS_END }

#define CAMERA_ROTATION_FUNCTIONS {
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void validateCurrentRotation();    // End a rotation of the camera (update the camera axes)
#define CAMERA_ROTATION_FUNCTIONS_END }

#define CAMERA_PROJECTION_FUNCTIONS {
	void setAspectRatio(int viewWidth, int viewHeight);
	void setPlanes(float nearPlane, float farPlane);
	void setViewAngle(float angle);
	Matrix4 getViewMatrix();
	Matrix4 getProjectionMatrix();
	Matrix4 getViewProjectionMatrix();
#define CAMERA_PROJECTION_FUNCTIONS_END }

private:
#define CAMERA_POSITION_AND_ROTATION {
	Vector3 position;
	Quaternion rotation;
	Vector3 currentRotationChanges;  // Changes during a camera rotation
	Quaternion getCurrentRotation();  // The camera rotation with the changes of the current rotation
#define CAMERA_POSITION_AND_ROTATION_END }

#define CAMERA_AXES {
	static const Vector3 initialDirectionVector;
	static const Vector3 initialUpVector;
	// If "useCurrentAxis" is true, the current rotation changes are taken into account
	void getCameraAxis(Vector3& directionAxis, Vector3& upAxis, bool useCurrentAxis = false);
	void getCameraAxis(Vector3& directionAxis, Vector3& upAxis, Vector3& xAxis, bool useCurrentAxis = false);
#define CAMERA_AXES_END }

#define CAMERA_PROJECTION_PARAMS {
	float viewAngle;
	float aspectRatio;
	float nearPlane;
	float farPlane;
#define CAMERA_PROJECTION_PARAMS_END }

#define CAMERA_MATRIXES {
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;
	Matrix4 viewProjectionMatrix;
	void computeViewMatrix();
	void computeProjectionMatrix();
#define CAMERA_MATRIXES_END }
};
