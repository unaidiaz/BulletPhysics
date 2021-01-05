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

	App->audio->PlayMusic("Assets/music.ogg");
	//App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	//App->camera->LookAt(vec3(0, 0, 0));

	sensor.SetPos(20, 0, 0);
	sensor.size.x = 5;
	sensor.size.y = 5;
	sensor.size.z = 5;
	sensor.axis = false;
	sensor.color.Set(0, 0, 0);
	physSensor = App->physics->AddBody(sensor, 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	//WALLS----------------------
	wall1.SetPos(250, 0, 0);
	wall1.size.x = 5;
	wall1.size.y = 500;
	wall1.size.z = 500;
	wall1.axis = false;
	wall1.color.Set(0, 255, 0);
	App->physics->AddBody(wall1, 0);

	wall2.SetPos(-250, 0, 0);
	wall2.size.x = 5;
	wall2.size.y = 500;
	wall2.size.z = 500;
	wall2.axis = false;
	wall2.color.Set(0, 255, 0);
	App->physics->AddBody(wall2, 0);

	wall3.SetPos(0, 0, 250);
	wall3.size.x = 500;
	wall3.size.y = 500;
	wall3.size.z = 5;
	wall3.axis = false;
	wall3.color.Set(0, 255, 0);
	App->physics->AddBody(wall3, 0);

	wall4.SetPos(0, 0, -250);
	wall4.size.x = 500;
	wall4.size.y = 500;
	wall4.size.z = 5;
	wall4.axis = false;
	wall4.color.Set(0, 255, 0);
	App->physics->AddBody(wall4, 0);

	/*
	ramp.SetPos(-15, 1, 0);
	ramp.SetRotation(60.0f, { 1,0,0 });
	ramp.size.x = 20;
	ramp.size.y = 10;
	ramp.size.z = 2;
	ramp.axis = true;
	ramp.color.Set(0, 0, 255);
	App->physics->AddBody(ramp, 0);*/
	//-------------------------

	//Limits-------------------
	limits[0].SetPos(-272, 0, 6);
	limits[0].size.x = 693;
	limits[0].size.y = 80;
	limits[0].size.z = 90;
	limits[0].axis = true;
	limits[0].color.Set(0, 255, 255);
	App->physics->AddBody(limits[0], 0);

/*	limits[1].SetPos(-167, 0, -282);
	limits[1].size.x = 115;
	limits[1].size.y = 80;
	limits[1].size.z = 78;
	limits[1].axis = true;
	limits[1].color.Set(0, 255, 255);
	App->physics->AddBody(limits[1], 0);

	limits[2].SetPos(40, 0, -240);
	limits[2].size.x = 32;
	limits[2].size.y = 80;
	limits[2].size.z = 491;
	limits[2].axis = true;
	limits[2].color.Set(0, 255, 255);
	App->physics->AddBody(limits[2], 0);

	limits[3].SetPos(287, 0, -269);
	limits[3].size.x = 88;
	limits[3].size.y = 80;
	limits[3].size.z = 154;
	limits[3].axis = true;
	limits[3].color.Set(0, 255, 255);
	App->physics->AddBody(limits[3], 0);

	limits[4].SetPos(4, 0, 114);
	limits[4].size.x = 44;
	limits[4].size.y = 80;
	limits[4].size.z = 420;
	limits[4].axis = true;
	limits[4].color.Set(0, 255, 255);
	App->physics->AddBody(limits[4], 0);

	limits[5].SetPos(244, 0, 156);
	limits[5].size.x = 59;
	limits[5].size.y = 80;
	limits[5].size.z = 57;
	limits[5].axis = true;
	limits[5].color.Set(0, 255, 255);
	App->physics->AddBody(limits[5], 0);

	limits[6].SetPos(320, 0, 239);
	limits[6].size.x = 176;
	limits[6].size.y = 80;
	limits[6].size.z = 92;
	limits[6].axis = true;
	limits[6].color.Set(0, 255, 255);
	App->physics->AddBody(limits[6], 0);

	limits[7].SetPos(31, 0, 395);
	limits[7].size.x = 229;
	limits[7].size.y = 80;
	limits[7].size.z = 117;
	limits[7].axis = true;
	limits[7].color.Set(0, 255, 255);
	App->physics->AddBody(limits[7], 0);

	limits[8].SetPos(254, 0, -61);
	limits[8].size.x = 26;
	limits[8].size.y = 80;
	limits[8].size.z = 516;
	limits[8].axis = true;
	limits[8].color.Set(0, 255, 255);
	App->physics->AddBody(limits[8], 0);

	limits[9].SetPos(336, 0, -27);
	limits[9].size.x = 34;
	limits[9].size.y = 80;
	limits[9].size.z = 352;
	limits[9].axis = true;
	limits[9].color.Set(0, 255, 255);
	App->physics->AddBody(limits[9], 0);
	*/

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
	sensor.Render();

	ramp.Render();

	for (int i = 0; i < 1; i++)
	{
		limits[i].Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}