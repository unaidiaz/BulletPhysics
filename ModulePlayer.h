#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 5000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define JUMP_COOLDOWN 3.0f
#define JUMP_IMPULSE 7000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2) override;

public:
	Timer jump_cooldown;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	bool helper = true;
	bool helper2 = false;
	bool helper3 = false;
	bool helper4 = false;

	int checkpointFx;
	int metaFx;
};