#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	metaFx = App->audio->LoadFx("Assets/meta.wav");
	checkpointFx = App->audio->LoadFx("Assets/checkpoint.wav");
	startFx = App->audio->LoadFx("Assets/start.wav");
	turboFx = App->audio->LoadFx("Assets/turbo.wav");
	restartButtonFx = App->audio->LoadFx("Assets/press_u.wav");
	canMove = false;
	playMusic = true;
	turboSoundActive = true;

	App->audio->PlayFx(startFx);
	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(3, 0.5, 12);
	car.chassis2_size.Set(5.5, 1.7, 7);
	car.chassis3_size.Set(7, 0.3, 1.2);
	car.chassis4_size.Set(3, 0.5, 14);
	car.chassis5_size.Set(2.3, 2, 5);
	car.chassis6_size.Set(0.2, 1, 1);
	car.chassis7_size.Set(0.2, 1, 1);
	car.chassis8_size.Set(5, 0.2, 1.3);
	car.chassis9_size.Set(2, 0.7, 8);
	car.chassis10_size.Set(4, 1.3, 5);
	car.chassis11_size.Set(2.3, 2.5, 3);

	car.chassis_offset.Set(0, 1.8, 0);
	car.chassis2_offset.Set(0, 2.4, -3);
	car.chassis3_offset.Set(0, 1.8, 7.5);
	car.chassis4_offset.Set(0, 1.8, 1.5);
	car.chassis5_offset.Set(0, 3, -3);
	car.chassis6_offset.Set(1.6, 3.5, -6.2);
	car.chassis7_offset.Set(-1.6, 3.5, -6.2);
	car.chassis8_offset.Set(0, 4, -6.4);
	car.chassis9_offset.Set(0, 2.2, 3);
	car.chassis10_offset.Set(0, 2.2, 0);
	car.chassis11_offset.Set(0, 3, -4);

	car.mass = 130.0f;
	car.suspensionStiffness = 26.10f;
	car.suspensionCompression = 1.42f;
	car.suspensionDamping = 2.35f;
	car.maxSuspensionTravelCm = 510.0f;
	car.frictionSlip = 100.5;
	car.maxSuspensionForce = 1000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 3.0f;
	float wheel_radius = 1.2f;
	float wheel_width = 1.5f;
	float suspensionRestLength = 1.5f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x * 0.5f;
	float half_length = car.chassis_size.z * 0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width + 0.9f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = true;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width - 0.9f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = true;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width + 0.9f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = false;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width - 0.9f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = false;
	car.wheels[3].steering = false;
	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(45, 0, 235);
	vehicle->collision_listeners.add(this);
	vehicle->SetId(1);
	btQuaternion q;
	q.setEuler(btScalar(180 * DEGTORAD), btScalar(0), btScalar(0));
	vehicle->SetRotation(q);

	turboTimer = 0;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if (INITIAL_TIME - App->scene_intro->timer == 5)
	{
		canMove = true;
		if (playMusic) App->audio->PlayMusic("Assets/music.ogg", 0.0f);
		playMusic = false;
	}

	if (App->camera->finish == false)
	{

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && canMove == true)
		{
			if (slow == true)
			{
				vehicle->body->setLinearVelocity(vehicle->body->getLinearVelocity() / 1.03f);
			}
			acceleration = MAX_ACCELERATION * 5;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && canMove == true)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && canMove == true)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && canMove == true)
		{
			if (vehicle->GetKmh() > 0)
			{
				brake = BRAKE_POWER / 2;
			}
			else
			{
				if (slow == true)
				{
					vehicle->body->setLinearVelocity(vehicle->body->getLinearVelocity() / 1.03f);
				}
				acceleration = -MAX_ACCELERATION * 5;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) 
		{
			brake = BRAKE_POWER;
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{

			if ((jump_cooldown.Read() * 0.001) >= JUMP_COOLDOWN)
			{
				vehicle->Push(0.0f, JUMP_IMPULSE * 3, 0.0f);
				jump_cooldown.Start();

			}
		}

		if (turboTimer > 0)
		{
			acceleration = MAX_ACCELERATION * 9;
		}

		if (App->scene_intro->lap == 1)
		{
			App->scene_intro->wall1.color.Set(0, 255, 255);
			App->scene_intro->wall2.color.Set(0, 255, 255);
			App->scene_intro->wall3.color.Set(0, 255, 255);
			App->scene_intro->wall4.color.Set(0, 255, 255);
			App->scene_intro->limits[0].color = Lila;
			App->scene_intro->limits[1].color = Lila;
			App->scene_intro->limits[2].color = Lila;
			App->scene_intro->limits[3].color = Lila;
			App->scene_intro->limits[4].color = Lila;
			App->scene_intro->limits[5].color = Lila;
			App->scene_intro->limits[7].color = Lila;
			App->scene_intro->limits[8].color = Lila;
			App->scene_intro->limits[9].color = Lila;
			App->scene_intro->limits[55].color = Lila;
			App->scene_intro->limits[14].color = Lila;
			App->scene_intro->limits[15].color = Lila;
			App->scene_intro->limits[16].color = Lila;
			App->scene_intro->limits[17].color = Lila;
			App->scene_intro->limits[60].color = Lila;
		}

		if (App->scene_intro->lap == 2)
		{
			App->scene_intro->wall1.color.Set(0, 0, 255);
			App->scene_intro->wall2.color.Set(0, 0, 255);
			App->scene_intro->wall3.color.Set(0, 0, 255);
			App->scene_intro->wall4.color.Set(0, 0, 255);
			App->scene_intro->limits[0].color = Pink;
			App->scene_intro->limits[1].color = Pink;
			App->scene_intro->limits[2].color = Pink;
			App->scene_intro->limits[3].color = Pink;
			App->scene_intro->limits[4].color = Pink;
			App->scene_intro->limits[5].color = Pink;
			App->scene_intro->limits[7].color = Pink;
			App->scene_intro->limits[8].color = Pink;
			App->scene_intro->limits[9].color = Pink;
			App->scene_intro->limits[55].color = Pink;
			App->scene_intro->limits[14].color = Pink;
			App->scene_intro->limits[15].color = Pink;
			App->scene_intro->limits[16].color = Pink;
			App->scene_intro->limits[17].color = Pink;
			App->scene_intro->limits[60].color = Pink;

		}

		if (App->scene_intro->lap == 3)
		{
			App->scene_intro->wall1.color = Black;
			App->scene_intro->wall2.color = Black;
			App->scene_intro->wall3.color = Black;
			App->scene_intro->wall4.color = Black;
			App->scene_intro->limits[0].color = Cyan;
			App->scene_intro->limits[1].color = Cyan;
			App->scene_intro->limits[2].color = Cyan;
			App->scene_intro->limits[3].color = Cyan;
			App->scene_intro->limits[4].color = Cyan;
			App->scene_intro->limits[5].color = Cyan;
			App->scene_intro->limits[7].color = Cyan;
			App->scene_intro->limits[8].color = Cyan;
			App->scene_intro->limits[9].color = Cyan;
			App->scene_intro->limits[55].color = Cyan;
			App->scene_intro->limits[14].color = Cyan;
			App->scene_intro->limits[15].color = Cyan;
			App->scene_intro->limits[16].color = Cyan;
			App->scene_intro->limits[17].color = Cyan;
			App->scene_intro->limits[60].color = Cyan;
		}

		if (App->scene_intro->lap == 4)
		{
			App->camera->finish = true;
			App->audio->PlayMusic("Assets/win.ogg", 0.0f);
			App->audio->PlayFx(restartButtonFx);
		}
		if (App->scene_intro->timer <= 0)
		{
			App->camera->finish = true;
			App->audio->PlayMusic("Assets/lose.ogg", 0.0f);
			App->audio->PlayFx(restartButtonFx);
		}

		btVector3 airControl;
		airControl = vehicle->vehicle->getChassisWorldTransform().getOrigin();
		if (airControl.getY() > 5)
		{
			Euler angles = vehicle->GetEulerAngles(vehicle->vehicle->getChassisWorldTransform().getRotation());

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				angles.yaw -= (DEGTORAD * 2);
				btQuaternion q;
				q.setEulerZYX(btScalar(angles.yaw), btScalar(angles.pitch), btScalar(angles.roll));
				vehicle->SetRotation(q);
			}
			else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			{
				angles.yaw += (DEGTORAD * 2);
				btQuaternion q;
				q.setEulerZYX(btScalar(angles.yaw), btScalar(angles.pitch), btScalar(angles.roll));
				vehicle->SetRotation(q);
			}

			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			{
				angles.roll += (DEGTORAD * 1);
				btQuaternion q;
				q.setEulerZYX(btScalar(angles.yaw), btScalar(angles.pitch), btScalar(angles.roll));
				vehicle->SetRotation(q);
			}
			else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			{
				angles.roll -= (DEGTORAD * 1);
				btQuaternion q;
				q.setEulerZYX(btScalar(angles.yaw), btScalar(angles.pitch), btScalar(angles.roll));
				vehicle->SetRotation(q);
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN) restart();
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) checkpointReapear(App->scene_intro->passedCheckpoints);


	if ((App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE) || App->camera->finish == true)
	{
		btVector3 vel = vehicle->body->getLinearVelocity();
		float friction = 0.99f;
		vehicle->body->setLinearVelocity(btVector3(vel.getX() * friction, vel.getY(), vel.getZ() * friction));
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h --- Lap %d --- Time Left %d", vehicle->GetKmh(), App->scene_intro->lap, App->scene_intro->timer);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2->id == 2 && App->scene_intro->sensor[0].wire == false)
	{
		if (App->scene_intro->passedCheckpoints == 3)
		{
			App->scene_intro->lap++;
			App->scene_intro->sensor[0].wire = true;
			App->audio->PlayFx(metaFx);
			App->scene_intro->timer += 7;
			App->scene_intro->passedCheckpoints = 0;
			App->scene_intro->sensor[1].wire = false;
			App->scene_intro->limits[37].color = Green;
			App->scene_intro->limits[38].color = Green;
			App->scene_intro->limits[41].color = Red;
			App->scene_intro->limits[42].color = Red;
			App->scene_intro->limits[45].color = Red;
			App->scene_intro->limits[46].color = Red;
			App->scene_intro->limits[53].color = Red;
			App->scene_intro->limits[54].color = Red;
			App->scene_intro->limits[49].color = Red;
			App->scene_intro->limits[50].color = Red;
		}
	}
	else if (body2->id == 3 && App->scene_intro->sensor[1].wire == false)
	{
		App->audio->PlayFx(checkpointFx);
		App->scene_intro->passedCheckpoints++;
		App->scene_intro->sensor[1].wire = true;
		App->scene_intro->timer += 7;
		App->scene_intro->sensor[2].wire = false;
		App->scene_intro->limits[41].color = Green;
		App->scene_intro->limits[42].color = Green;
		App->scene_intro->limits[37].color = Red;
		App->scene_intro->limits[38].color = Red;
	}
	else if (body2->id == 4 && App->scene_intro->sensor[2].wire == false)
	{
		App->audio->PlayFx(checkpointFx);
		App->scene_intro->passedCheckpoints++;
		App->scene_intro->sensor[2].wire = true;
		App->scene_intro->timer += 7;
		App->scene_intro->sensor[3].wire = false;
		App->scene_intro->sensor[4].wire = false;
		App->scene_intro->limits[45].color = Green;
		App->scene_intro->limits[46].color = Green;
	}
	else if (body2->id == 5 && App->scene_intro->sensor[3].wire == false)
	{
		App->audio->PlayFx(checkpointFx);
		App->scene_intro->passedCheckpoints++;
		App->scene_intro->sensor[3].wire = true;
		App->scene_intro->timer += 7;
		App->scene_intro->sensor[4].wire = true;
		App->scene_intro->sensor[0].wire = false;
		App->scene_intro->limits[53].color = Green;
		App->scene_intro->limits[54].color = Green;

	}
	else if (body2->id == 6 && App->scene_intro->sensor[4].wire == false)
	{
		App->audio->PlayFx(checkpointFx);
		App->scene_intro->passedCheckpoints++;
		App->scene_intro->sensor[4].wire = true;
		App->scene_intro->timer += 7;
		App->scene_intro->sensor[3].wire = true;
		App->scene_intro->sensor[0].wire = false;
		App->scene_intro->limits[49].color = Green;
		App->scene_intro->limits[50].color = Green;
	}
	else if (body2->id == 7)
	{
		if (turboSoundActive)
		{
			App->audio->PlayFx(turboFx);
			turboSoundActive = false;
		}
		turboTimer = 2;
	}
	else if (body2->id == 8)
	{
		slow = true;
	}
}

void ModulePlayer::restart()
{
	App->audio->PlayMusic("Assets/silence.ogg");
	turn = 0;
	acceleration = 0;
	vehicle->SetPos(40, 0, 230);
	btQuaternion q;
	q.setEuler(btScalar(180 * DEGTORAD), btScalar(0), btScalar(0));
	vehicle->SetRotation(q);
	App->scene_intro->lap = 1;
	App->scene_intro->passedCheckpoints = 0;
	App->scene_intro->timer = INITIAL_TIME;
	App->scene_intro->sensor[0].wire = true;
	App->scene_intro->sensor[1].wire = false;
	App->scene_intro->sensor[2].wire = true;
	App->scene_intro->sensor[3].wire = true;
	App->scene_intro->sensor[4].wire = true;
	vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
	canMove = false;
	App->scene_intro->flag[0].color = Black;
	App->scene_intro->flag[1].color = Black;
	App->scene_intro->flag[2].color = Black;
	App->camera->finish = false;
	playMusic = true;
	App->audio->PlayFx(startFx);
}

void ModulePlayer::checkpointReapear(int checkpointPassed)
{
	btQuaternion q;

	switch (checkpointPassed)
	{
	case 0:
		turn = 0;
		acceleration = 0;
		vehicle->SetPos(39, 0, 213);
		q.setEuler(btScalar(180 * DEGTORAD), btScalar(0), btScalar(0));
		vehicle->SetRotation(q);
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		break;
	case 1:
		turn = 0;
		acceleration = 0;
		vehicle->SetPos(235, 0, 150);
		q.setEuler(btScalar(90 * DEGTORAD), btScalar(0), btScalar(0));
		vehicle->SetRotation(q);
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		break;
	case 2:
		turn = 0;
		acceleration = 0;
		vehicle->SetPos(335, 0, 338);
		q.setEuler(btScalar(90 * DEGTORAD), btScalar(0), btScalar(0));
		vehicle->SetRotation(q);
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		break;
	case 3:
		turn = 0;
		acceleration = 0;
		vehicle->SetPos(475, 0, 442);
		q.setEuler(btScalar(270 * DEGTORAD), btScalar(0), btScalar(0));
		vehicle->SetRotation(q);
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		break;
	}
}