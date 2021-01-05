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

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(4, 0.5, 8);
	car.chassis2_size.Set(4, 2, 0.5);
	car.chassis3_size.Set(3, 0.8, 0.2);
	car.chassis4_size.Set(0.5, 2, 4);
	car.chassis5_size.Set(0.5, 2, 4);
	car.chassis6_size.Set(4, 4, 2);
	car.chassis7_size.Set(4, 2.5, 2);
	car.chassis8_size.Set(3.5, 3.5, 1.5);
	car.chassis9_size.Set(4.05, 1.5, 1.5);
	car.chassis10_size.Set(0.7, 0.7, 0.7);
	car.chassis11_size.Set(0.7, 0.7, 0.7);
	car.chassis12_size.Set(0.7, 5, 0.7);
	car.chassis13_size.Set(0.7, 5, 0.7);

	car.chassis_offset.Set(0, 1.8, 0);
	car.chassis2_offset.Set(0, 2.5, -4);
	car.chassis3_offset.Set(0, 2, -4.2);
	car.chassis4_offset.Set(1.75, 2.5, -2);
	car.chassis5_offset.Set(-1.75, 2.5, -2);
	car.chassis6_offset.Set(0, 4, 1);
	car.chassis7_offset.Set(0, 3, 3);
	car.chassis8_offset.Set(0, 3.6, 1.3);
	car.chassis9_offset.Set(0, 5, 1);
	car.chassis10_offset.Set(1.5, 3, 4);
	car.chassis11_offset.Set(-1.5, 3, 4);
	car.chassis12_offset.Set(1.6, 4.5, 0);
	car.chassis13_offset.Set(-1.6, 4.5, 0);

	car.mass = 1500.0f;
	car.suspensionStiffness = 4.0f;
	car.suspensionCompression = 0.5f;
	car.suspensionDamping = 0.3f;
	car.maxSuspensionTravelCm = 200.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 7000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 2.0f;
	float wheel_radius = 1.5f;
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
	car.wheels[0].connection.Set(half_width + 0.7f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width - 0.7f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width + 0.7f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width - 0.7f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(47, 0, 230);
	vehicle->collision_listeners.add(this);
	vehicle->SetId(1);

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
	VehicleInfo car;

	int select = 1;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		select++;
	}
	if (select == 3) {
		select = 1;
	}
	if (select == 2) {

		car.chassis_size.Set(4, 5, 8);
		car.chassis2_size.Set(4, 2, 0.5);
		car.chassis3_size.Set(3, 0.8, 0.2);
		car.chassis4_size.Set(0.5, 2, 4);
		car.chassis5_size.Set(0.5, 2, 4);
		car.chassis6_size.Set(4, 4, 2);
		car.chassis7_size.Set(4, 2.5, 2);
		car.chassis8_size.Set(3.5, 3.5, 1.5);
		car.chassis9_size.Set(4.05, 4, 1.5);
		car.chassis10_size.Set(0.7, 0.7, 0.7);
		car.chassis11_size.Set(0.7, 0.7, 0.7);
		car.chassis12_size.Set(0.7, 5, 0.7);
		car.chassis13_size.Set(0.7, 5, 0.7);

		car.chassis_offset.Set(0, 1.8, 0);
		car.chassis2_offset.Set(0, 2.5, -4);
		car.chassis3_offset.Set(0, 2, -4.2);
		car.chassis4_offset.Set(1.75, 2.5, -2);
		car.chassis5_offset.Set(-1.75, 2.5, -2);
		car.chassis6_offset.Set(0, 4, 1);
		car.chassis7_offset.Set(0, 3, 3);
		car.chassis8_offset.Set(0, 3.6, 1.3);
		car.chassis9_offset.Set(0, 5, 1);
		car.chassis10_offset.Set(1.5, 3, 4);
		car.chassis11_offset.Set(-1.5, 3, 4);
		car.chassis12_offset.Set(1.6, 4.5, 0);
		car.chassis13_offset.Set(-1.6, 4.5, 0);

		car.mass = 1500.0f;
		car.suspensionStiffness = 4.0f;
		car.suspensionCompression = 0.5f;
		car.suspensionDamping = 0.3f;
		car.maxSuspensionTravelCm = 200.0f;
		car.frictionSlip = 50.5;
		car.maxSuspensionForce = 7000.0f;
	}
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
		brake = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{

		if ((jump_cooldown.Read() * 0.001) >= JUMP_COOLDOWN)
		{
			vehicle->Push(0.0f, JUMP_IMPULSE, 0.0f);
			jump_cooldown.Start();
			
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE)
	{
		if (vehicle->GetKmh() > 0)
		{
			acceleration = vehicle->info.mass * -10 * 0.1f;
		}
		else if (vehicle->GetKmh() < 0)
		{
			acceleration = -vehicle->info.mass * -10 * 0.1f;
		}
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2->id == 2)
	{
		vehicle->SetPos(0, 100, 0);
	}
}