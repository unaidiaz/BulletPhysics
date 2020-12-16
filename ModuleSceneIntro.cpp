#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ground = new Plane(0, 1, 0, 0);
	ground->axis = false;
	ground->color.Set(255, 1, 0);
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	//App->camera->LookAt(vec3(0, 0, 0));

	//WALLS----------------------
	wall1.SetPos(250, 0, 0);
	wall1.size.x = 5;
	wall1.size.y = 1000;
	wall1.size.z = 1000;
	wall1.axis = false;
	wall1.color.Set(0, 255, 0);
	App->physics->AddBody(wall1, 0);

	wall2.SetPos(-250, 0, 0);
	wall2.size.x = 5;
	wall2.size.y = 1000;
	wall2.size.z = 1000;
	wall2.axis = false;
	wall2.color.Set(0, 255, 0);
	App->physics->AddBody(wall2, 0);

	wall3.SetPos(0, 0, 250);
	wall3.size.x = 1000;
	wall3.size.y = 1000;
	wall3.size.z = 5;
	wall3.axis = false;
	wall3.color.Set(0, 255, 0);
	App->physics->AddBody(wall3, 0);

	wall4.SetPos(0, 0, -250);
	wall4.size.x = 1000;
	wall4.size.y = 1000;
	wall4.size.z = 5;
	wall4.axis = false;
	wall4.color.Set(0, 255, 0);
	App->physics->AddBody(wall4, 0);

	ramp.SetPos(-15, 1, 0);
	ramp.SetRotation(60.0f, { 1,0,0 });
	ramp.size.x = 20;
	ramp.size.y = 10;
	ramp.size.z = 2;
	ramp.axis = true;
	ramp.color.Set(0, 0, 255);
	App->physics->AddBody(ramp, 0);
	//-------------------------

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	ground->Render();

	wall1.Render();
	wall2.Render();
	wall3.Render();
	wall4.Render();

	ramp.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}

