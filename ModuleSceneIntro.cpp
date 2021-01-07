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

	passedCheckpoints = 0;

	//Walls----------------------
	wall1.SetPos(0, 0, 256);
	wall1.size.x = 5;
	wall1.size.y = 512;
	wall1.size.z = 512;
	wall1.axis = false;
	wall1.color.Set(0, 255, 255);
	App->physics->AddBody(wall1, 0);

	wall2.SetPos(512, 0, 256);
	wall2.size.x = 5;
	wall2.size.y = 512;
	wall2.size.z = 512;
	wall2.axis = false;
	wall2.color.Set(0, 255, 255);
	App->physics->AddBody(wall2, 0);

	wall3.SetPos(256, 0, 0);
	wall3.size.x = 512;
	wall3.size.y = 512;
	wall3.size.z = 5;
	wall3.axis = false;
	wall3.color.Set(0, 255, 255);
	App->physics->AddBody(wall3, 0);

	wall4.SetPos(256, 0, 512);
	wall4.size.x = 512;
	wall4.size.y = 512;
	wall4.size.z = 5;
	wall4.axis = false;
	wall4.color.Set(0, 255, 255);
	App->physics->AddBody(wall4, 0);

	//Borders----------------------
	limits[10].SetPos(0, 0, 256);
	limits[10].size.x = 9;
	limits[10].size.y = 4;
	limits[10].size.z = 512;
	limits[10].axis = false;
	limits[10].color.Set(255, 0, 0);
	App->physics->AddBody(limits[10], 0);

	limits[11].SetPos(512, 0, 256);
	limits[11].size.x = 9;
	limits[11].size.y = 4;
	limits[11].size.z = 512;
	limits[11].axis = false;
	limits[11].color.Set(255, 0, 0);
	App->physics->AddBody(limits[11], 0);

	limits[12].SetPos(256, 0, 0);
	limits[12].size.x = 512;
	limits[12].size.y = 4;
	limits[12].size.z = 9;
	limits[12].axis = false;
	limits[12].color.Set(255, 0, 0);
	App->physics->AddBody(limits[12], 0);

	limits[13].SetPos(256, 0, 512);
	limits[13].size.x = 512;
	limits[13].size.y = 4;
	limits[13].size.z = 9;
	limits[13].axis = false;
	limits[13].color.Set(255, 0, 0);
	App->physics->AddBody(limits[13], 0);

	//Ramps-------------------
	ramp[0].SetPos(316, 0, 324);
	ramp[0].SetRotation(25.0f, { 0,0,1 });
	ramp[0].size.x = 30;
	ramp[0].size.y = 2;
	ramp[0].size.z = 40;
	ramp[0].axis = true;
	ramp[0].color.Set(255, 0, 0);
	App->physics->AddBody(ramp[0], 0);

	ramp[1].SetPos(334, 0, 470);
	ramp[1].SetRotation(-25.0f, { 0,0,1 });
	ramp[1].size.x = 30;
	ramp[1].size.y = 2;
	ramp[1].size.z = 40;
	ramp[1].axis = true;
	ramp[1].color.Set(255, 0, 0);
	App->physics->AddBody(ramp[1], 0);

	//Limits-------------------
	limits[0].SetPos(256, 0, 56);
	limits[0].size.x = 47;
	limits[0].size.y = 50;
	limits[0].size.z = 111;
	limits[0].axis = true;
	limits[0].color.Set(0, 0, 255);
	App->physics->AddBody(limits[0], 0);

	limits[1].SetPos(396, 0, 135);
	limits[1].size.x = 47;
	limits[1].size.y = 50;
	limits[1].size.z = 79;
	limits[1].axis = true;
	limits[1].color.Set(0, 0, 255);
	App->physics->AddBody(limits[1], 0);

	limits[2].SetPos(109, 0, 187);
	limits[2].size.x = 43;
	limits[2].size.y = 50;
	limits[2].size.z = 195;
	limits[2].axis = true;
	limits[2].color.Set(0, 0, 255);
	App->physics->AddBody(limits[2], 0);
	
	limits[3].SetPos(103, 0, 327);
	limits[3].size.x = 31;
	limits[3].size.y = 50;
	limits[3].size.z = 91;
	limits[3].axis = true;
	limits[3].color.Set(0, 0, 255);
	App->physics->AddBody(limits[3], 0);
	
	limits[4].SetPos(123, 0, 397);
	limits[4].size.x = 71;
	limits[4].size.y = 50;
	limits[4].size.z = 51;
	limits[4].axis = true;
	limits[4].color.Set(0, 0, 255);
	App->physics->AddBody(limits[4], 0);
	
	limits[5].SetPos(256, 0, 376);
	limits[5].size.x = 195;
	limits[5].size.y = 50;
	limits[5].size.z = 9;
	limits[5].axis = true;
	limits[5].color.Set(0, 0, 255);
	App->physics->AddBody(limits[5], 0);
	
	limits[6].SetPos(385, 0, 389);
	limits[6].size.x = 63;
	limits[6].size.y = 50;
	limits[6].size.z = 35;
	limits[6].axis = true;
	limits[6].color.Set(0, 0, 255);
	App->physics->AddBody(limits[6], 0);
	
	limits[7].SetPos(462, 0, 260);
	limits[7].size.x = 100;
	limits[7].size.y = 50;
	limits[7].size.z = 23;
	limits[7].axis = true;
	limits[7].color.Set(0, 0, 255);
	App->physics->AddBody(limits[7], 0);
	
	limits[8].SetPos(369, 0, 267);
	limits[8].size.x = 87;
	limits[8].size.y = 50;
	limits[8].size.z = 9;
	limits[8].axis = true;
	limits[8].color.Set(0, 0, 255);
	App->physics->AddBody(limits[8], 0);
	
	limits[9].SetPos(328, 0, 280);
	limits[9].size.x = 5;
	limits[9].size.y = 50;
	limits[9].size.z = 17;
	limits[9].axis = true;
	limits[9].color.Set(0, 0, 255);
	App->physics->AddBody(limits[9], 0);

	limits[14].SetPos(285, 0, 286);
	limits[14].size.x = 81;
	limits[14].size.y = 50;
	limits[14].size.z = 5;
	limits[14].axis = true;
	limits[14].color.Set(0, 0, 255);
	App->physics->AddBody(limits[14], 0);

	limits[15].SetPos(182, 0, 202);
	limits[15].size.x = 105;
	limits[15].size.y = 50;
	limits[15].size.z = 21;
	limits[15].axis = true;
	limits[15].color.Set(0, 0, 255);
	App->physics->AddBody(limits[15], 0);

	limits[16].SetPos(289, 0, 196);
	limits[16].size.x = 109;
	limits[16].size.y = 50;
	limits[16].size.z = 9;
	limits[16].axis = true;
	limits[16].color.Set(0, 0, 255);
	App->physics->AddBody(limits[16], 0);

	limits[17].SetPos(353, 0, 180);
	limits[17].size.x = 39;
	limits[17].size.y = 50;
	limits[17].size.z = 24;
	limits[17].axis = true;
	limits[17].color.Set(0, 0, 255);
	App->physics->AddBody(limits[17], 0);

	limits[18].SetPos(256, 0, 56);
	limits[18].size.x = 51;
	limits[18].size.y = 4;
	limits[18].size.z = 115;
	limits[18].axis = true;
	limits[18].color.Set(225, 0, 0);
	App->physics->AddBody(limits[18], 0);

	limits[19].SetPos(396, 0, 135);
	limits[19].size.x = 51;
	limits[19].size.y = 4;
	limits[19].size.z = 83;
	limits[19].axis = true;
	limits[19].color.Set(225, 0, 0);
	App->physics->AddBody(limits[19], 0);

	limits[20].SetPos(109, 0, 187);
	limits[20].size.x = 47;
	limits[20].size.y = 4;
	limits[20].size.z = 199;
	limits[20].axis = true;
	limits[20].color.Set(225, 0, 0);
	App->physics->AddBody(limits[20], 0);

	limits[21].SetPos(103, 0, 327);
	limits[21].size.x = 35;
	limits[21].size.y = 4;
	limits[21].size.z = 95;
	limits[21].axis = true;
	limits[21].color.Set(225, 0, 0);
	App->physics->AddBody(limits[21], 0);

	limits[22].SetPos(123, 0, 397);
	limits[22].size.x = 75;
	limits[22].size.y = 4;
	limits[22].size.z = 55;
	limits[22].axis = true;
	limits[22].color.Set(225, 0, 0);
	App->physics->AddBody(limits[22], 0);

	limits[23].SetPos(256, 0, 376);
	limits[23].size.x = 199;
	limits[23].size.y = 4;
	limits[23].size.z = 13;
	limits[23].axis = true;
	limits[23].color.Set(225, 0, 0);
	App->physics->AddBody(limits[23], 0);

	limits[24].SetPos(385, 0, 389);
	limits[24].size.x = 67;
	limits[24].size.y = 4;
	limits[24].size.z = 39;
	limits[24].axis = true;
	limits[24].color.Set(225, 0, 0);
	App->physics->AddBody(limits[24], 0);

	limits[25].SetPos(462, 0, 260);
	limits[25].size.x = 104;
	limits[25].size.y = 4;
	limits[25].size.z = 27;
	limits[25].axis = true;
	limits[25].color.Set(225, 0, 0);
	App->physics->AddBody(limits[25], 0);

	limits[26].SetPos(369, 0, 267);
	limits[26].size.x = 91;
	limits[26].size.y = 4;
	limits[26].size.z = 13;
	limits[26].axis = true;
	limits[26].color.Set(225, 0, 0);
	App->physics->AddBody(limits[26], 0);

	limits[27].SetPos(328, 0, 280);
	limits[27].size.x = 9;
	limits[27].size.y = 4;
	limits[27].size.z = 21;
	limits[27].axis = true;
	limits[27].color.Set(225, 0, 0);
	App->physics->AddBody(limits[27], 0);

	limits[28].SetPos(285, 0, 286);
	limits[28].size.x = 85;
	limits[28].size.y = 4;
	limits[28].size.z = 9;
	limits[28].axis = true;
	limits[28].color.Set(225, 0, 0);
	App->physics->AddBody(limits[28], 0);

	limits[29].SetPos(182, 0, 202);
	limits[29].size.x = 109;
	limits[29].size.y = 4;
	limits[29].size.z = 25;
	limits[29].axis = true;
	limits[29].color.Set(225, 0, 0);
	App->physics->AddBody(limits[29], 0);

	limits[30].SetPos(289, 0, 196);
	limits[30].size.x = 113;
	limits[30].size.y = 4;
	limits[30].size.z = 13;
	limits[30].axis = true;
	limits[30].color.Set(225, 0, 0);
	App->physics->AddBody(limits[30], 0);

	limits[31].SetPos(353, 0, 180);
	limits[31].size.x = 43;
	limits[31].size.y = 4;
	limits[31].size.z = 28;
	limits[31].axis = true;
	limits[31].color.Set(225, 0, 0);
	App->physics->AddBody(limits[31], 0);

	limits[32].SetPos(17, 0, 213);
	limits[32].size.x = 2;
	limits[32].size.y = 46;
	limits[32].size.z = 2;
	limits[32].axis = true;
	limits[32].color.Set(225, 225, 225);
	App->physics->AddBody(limits[32], 0);

	limits[33].SetPos(61, 0, 213);
	limits[33].size.x = 2;
	limits[33].size.y = 46;
	limits[33].size.z = 2;
	limits[33].axis = true;
	limits[33].color.Set(225, 225, 225);
	App->physics->AddBody(limits[33], 0);

	limits[34].SetPos(39, 20, 213);
	limits[34].size.x = 42;
	limits[34].size.y = 6;
	limits[34].size.z = 2;
	limits[34].axis = true;
	limits[34].color.Set(0, 0, 0);
	App->physics->AddBody(limits[34], 0);

	limits[35].SetPos(259, 0, 480);
	limits[35].size.x = 8;
	limits[35].size.y = 4;
	limits[35].size.z = 68;
	limits[35].axis = true;
	limits[35].color.Set(225, 0, 0);
	App->physics->AddBody(limits[35], 0);

	sensor[0].SetPos(39, 0, 213);
	sensor[0].size.x = 15;
	sensor[0].size.y = 15;
	sensor[0].size.z = 1;
	sensor[0].axis = true;
	sensor[0].color.Set(225, 0, 0);
	physSensor = App->physics->AddBody(sensor[0], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	sensor[1].SetPos(255, 0, 157);
	sensor[1].size.x = 1;
	sensor[1].size.y = 15;
	sensor[1].size.z = 15;
	sensor[1].axis = true;
	sensor[1].color.Set(225, 0, 0);
	physSensor = App->physics->AddBody(sensor[1], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(3);

	sensor[2].SetPos(290, 0, 326);
	sensor[2].size.x = 1;
	sensor[2].size.y = 15;
	sensor[2].size.z = 15;
	sensor[2].axis = true;
	sensor[2].color.Set(225, 0, 0);
	physSensor = App->physics->AddBody(sensor[2], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(4);

	sensor[3].SetPos(380, 0, 468);
	sensor[3].size.x = 1;
	sensor[3].size.y = 15;
	sensor[3].size.z = 15;
	sensor[3].axis = true;
	sensor[3].color.Set(225, 0, 0);
	physSensor = App->physics->AddBody(sensor[3], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(5);

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
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) 
	{
		passedCheckpoints = 4;
	}

	if (passedCheckpoints == 4)
	{
		for (int i = 0; i < 10; i++)
		{
			sensor[i].color.Set(225, 0, 0);
		}
	}


	ground->Render();

	wall1.Render();
	wall2.Render();
	wall3.Render();
	wall4.Render();

	for (int i = 0; i < 4; i++)
	{
		ramp[i].Render();
	}

	for (int i = 0; i < 40; i++)
	{
		limits[i].Render();
	}

	for (int i = 0; i < 10; i++)
	{
		sensor[i].Render();
	}

	if (passedCheckpoints == 4)
	{
		for (int i = 0; i < 10; i++)
		{
			sensor[i].color.Set(225, 0, 0);
		}
	}


	if (frames % 60 == 0)
	{
		timer--;
	}
	if (timer <= 0)
	{
		SDL_Quit();
	}
	frames++;

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}