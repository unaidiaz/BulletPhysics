#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"
#include "Application.h"
#include "ModulePlayer.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Black;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}


	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());
	chassis.color = Red;
	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	Cube chassis2(4, 2, 0.5);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis2.transform);
	btQuaternion q2 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset2(0, 2.5, -4);
	offset2 = offset2.rotate(q2.getAxis(), q2.getAngle());
	chassis2.color = Red;
	chassis2.transform.M[12] += offset2.getX();
	chassis2.transform.M[13] += offset2.getY();
	chassis2.transform.M[14] += offset2.getZ();

	Cube chassis3(3, 0.8, 0.2);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis3.transform);
	btQuaternion q3 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset3(0, 2, -4.2);
	offset3 = offset3.rotate(q3.getAxis(), q3.getAngle());
	chassis3.color = Cyan;
	chassis3.transform.M[12] += offset3.getX();
	chassis3.transform.M[13] += offset3.getY();
	chassis3.transform.M[14] += offset3.getZ();

	Cube chassis4(0.5, 2, 4);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis4.transform);
	btQuaternion q4 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset4(1.75, 2.5, -2);
	offset4 = offset4.rotate(q4.getAxis(), q4.getAngle());
	chassis4.color = Red;
	chassis4.transform.M[12] += offset4.getX();
	chassis4.transform.M[13] += offset4.getY();
	chassis4.transform.M[14] += offset4.getZ();

	Cube chassis5(0.5, 2, 4);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis5.transform);
	btQuaternion q5 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset5(-1.75, 2.5, -2);
	offset5 = offset5.rotate(q5.getAxis(), q5.getAngle());
	chassis5.color = Red;
	chassis5.transform.M[12] += offset5.getX();
	chassis5.transform.M[13] += offset5.getY();
	chassis5.transform.M[14] += offset5.getZ();

	Cube chassis6(4, 4, 2);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis6.transform);
	btQuaternion q6 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset6(0, 4, 1);
	offset6 = offset6.rotate(q6.getAxis(), q6.getAngle());
	chassis6.color = Red;
	chassis6.transform.M[12] += offset6.getX();
	chassis6.transform.M[13] += offset6.getY();
	chassis6.transform.M[14] += offset6.getZ();

	Cube chassis7(4, 2.5, 2);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis7.transform);
	btQuaternion q7 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset7(0, 3, 3);
	offset7 = offset7.rotate(q7.getAxis(), q7.getAngle());
	chassis7.color = Red;
	chassis7.transform.M[12] += offset7.getX();
	chassis7.transform.M[13] += offset7.getY();
	chassis7.transform.M[14] += offset7.getZ();

	Cube chassis8(3.5, 3.5, 1.5);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis8.transform);
	btQuaternion q8 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset8(0, 3.6, 1.3);
	offset8 = offset8.rotate(q8.getAxis(), q8.getAngle());
	chassis8.color = Cyan;
	chassis8.transform.M[12] += offset8.getX();
	chassis8.transform.M[13] += offset8.getY();
	chassis8.transform.M[14] += offset8.getZ();

	Cube chassis9(4.05, 1.5, 1.5);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis9.transform);
	btQuaternion q9 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset9(0, 5, 1);
	offset9 = offset9.rotate(q9.getAxis(), q9.getAngle());
	chassis9.color = Cyan;
	chassis9.transform.M[12] += offset9.getX();
	chassis9.transform.M[13] += offset9.getY();
	chassis9.transform.M[14] += offset9.getZ();

	Cube chassis10(0.7, 0.7, 0.7);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis10.transform);
	btQuaternion q10 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset10(1.5, 3, 4);
	offset10 = offset10.rotate(q10.getAxis(), q10.getAngle());
	chassis10.color = Yellow;
	chassis10.transform.M[12] += offset10.getX();
	chassis10.transform.M[13] += offset10.getY();
	chassis10.transform.M[14] += offset10.getZ();

	Cube chassis11(0.7, 0.7, 0.7);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis11.transform);
	btQuaternion q11 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset11(-1.5, 3, 4);
	offset11 = offset11.rotate(q11.getAxis(), q11.getAngle());
	chassis11.color = Yellow;
	chassis11.transform.M[12] += offset11.getX();
	chassis11.transform.M[13] += offset11.getY();
	chassis11.transform.M[14] += offset11.getZ();

	Cube chassis12(0.7, 5, 0.7);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis12.transform);
	btQuaternion q12 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset12(1.6, 4.5, 0);
	offset12 = offset12.rotate(q12.getAxis(), q12.getAngle());
	chassis12.color = Black;
	chassis12.transform.M[12] += offset12.getX();
	chassis12.transform.M[13] += offset12.getY();
	chassis12.transform.M[14] += offset12.getZ();

	Cube chassis13(0.7, 5, 0.7);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis13.transform);
	btQuaternion q13 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset13(-1.6, 4.5, 0);
	offset13 = offset13.rotate(q13.getAxis(), q13.getAngle());
	chassis13.color = Black;
	chassis13.transform.M[12] += offset13.getX();
	chassis13.transform.M[13] += offset13.getY();
	chassis13.transform.M[14] += offset13.getZ();

	chassis.Render();
	chassis2.Render();
	chassis3.Render();
	chassis4.Render();
	chassis5.Render();
	chassis6.Render();
	chassis7.Render();
	chassis8.Render();
	chassis9.Render();
	chassis10.Render();
	chassis11.Render();
	chassis12.Render();
	chassis13.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}