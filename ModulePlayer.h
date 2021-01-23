#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 400.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 350.0f
#define JUMP_COOLDOWN 3.0f
#define JUMP_IMPULSE 700.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2) override;

	void restart();
	void checkpointReapear(int checkpointPassed);

public:
	Timer jump_cooldown;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	uint turboTimer;
	bool canMove;
	bool playMusic;
	bool slow;

	int checkpointFx;
	int metaFx;
	int startFx;
	int turboFx;
	int restartButtonFx;
	bool turboSoundActive;
};