#include "RigidBody.h"

RigidBody::RigidBody(float mass, float radius, float linearDamping, float angularDamping) : linearDamping(linearDamping), angularDamping(angularDamping), IPhysicComponent(), IForceGenerator()
{
	SetMass(mass);
	SetLocalInverseInertialTensorFromSphere(radius);
}

RigidBody::RigidBody(float mass, float dx, float dy, float dz, float linearDamping, float angularDamping) : linearDamping(linearDamping), angularDamping(angularDamping)
{
	SetMass(mass);
	SetLocalInverseInertialTensformFromBox(dx, dy, dz);
}

RigidBody::~RigidBody()
{

}


void RigidBody::UpdatePhysics(float deltaTime)
{
	if (GetInvertedMass() < 0 || deltaTime <= 0) {
		return;
	}
	

	// Calculate acceleration
	acceleration = accumForce * GetInvertedMass();

	// Calculate angularAcceleration
	angularAcceleration = globalInverseInertialTensor * accumTorque;

	// Update velocity
	velocity = (velocity * pow(linearDamping, deltaTime)) + accumForce * deltaTime;

	// Update angular velocity
	angularVelocity = angularVelocity * pow(angularDamping, deltaTime) + angularAcceleration * deltaTime;

	// Update position
	GetOwner()->GetTransform()->SetPosition(GetOwner()->GetTransform()->GetPosition() + velocity * deltaTime);

	// Update rotation
	GetOwner()->GetTransform()->SetRotation(Quaternion::RotateByVector(GetOwner()->GetTransform()->GetRotation(), angularVelocity));

	// Update the globaInverseInertialTensor for this object (the transform matrix is handle by the transform object)
	globalInverseInertialTensor = GetOwner()->GetTransform()->GetTransformMatrix().matrix3Inverse() * localInverseInertialTensor * GetOwner()->GetTransform()->GetTransformMatrix();

	// Clean forces
	ClearAccumForce();
	ClearAccumTorqueForce();
}

std::vector<IForce*> RigidBody::GetForces(float time)
{
	std::vector<IForce*> forces = std::vector<IForce*>();

	if (gravity) {
		forces.push_back(new GravityForce(this));
	}

	return forces;
}

void RigidBody::SetGravity(bool value)
{
	gravity = value;
}

bool RigidBody::GetGravity()
{
	return gravity;
}

void RigidBody::SetLocalInverseInertialTensorFromSphere(float radius)
{
	float value = (2 / 5) * GetMass() * radius * radius;
	localInverseInertialTensor = (Matrix3() * value).matrix3Inverse();
}

void RigidBody::SetLocalInverseInertialTensformFromBox(float dx, float dy, float dz)
{
	float k = (1 / 12) * GetMass();
	localInverseInertialTensor = Matrix3(k*(dy*dy + dz * dz), 0, 0, 0, k*(dx*dx + dz * dz), 0, 0, 0, k*(dx*dx + dy * dy)).matrix3Inverse();
}
