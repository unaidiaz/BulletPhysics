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
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

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
	ramp[0].SetPos(280, 0, 314);
	ramp[0].SetRotation(20.0f, { 0,0,1 });
	ramp[0].size.x = 25;
	ramp[0].size.y = 2;
	ramp[0].size.z = 40;
	ramp[0].axis = true;
	ramp[0].color = White;
	App->physics->AddBody(ramp[0], 0);

	ramp[1].SetPos(295, 10, 316);
	ramp[1].SetRotation(40.0f, { 0,0,1 });
	ramp[1].size.x = 25;
	ramp[1].size.y = 2;
	ramp[1].size.z = 40;
	ramp[1].axis = true;
	ramp[1].color = Black;
	App->physics->AddBody(ramp[1], 0);

	ramp[2].SetPos(308, 25, 318);
	ramp[2].SetRotation(60.0f, { 0,0,1 });
	ramp[2].size.x = 25;
	ramp[2].size.y = 2;
	ramp[2].size.z = 40;
	ramp[2].axis = true;
	ramp[2].color = White;
	App->physics->AddBody(ramp[2], 0);

	ramp[3].SetPos(314, 40, 320);
	ramp[3].SetRotation(80.0f, { 0,0,1 });
	ramp[3].size.x = 25;
	ramp[3].size.y = 2;
	ramp[3].size.z = 40;
	ramp[3].axis = true;
	ramp[3].color = Black;
	App->physics->AddBody(ramp[3], 0);

	ramp[4].SetPos(314, 55, 322);
	ramp[4].SetRotation(100.0f, { 0,0,1 });
	ramp[4].size.x = 25;
	ramp[4].size.y = 2;
	ramp[4].size.z = 40;
	ramp[4].axis = true;
	ramp[4].color = White;
	App->physics->AddBody(ramp[4], 0);

	ramp[5].SetPos(308, 70, 324);
	ramp[5].SetRotation(120.0f, { 0,0,1 });
	ramp[5].size.x = 25;
	ramp[5].size.y = 2;
	ramp[5].size.z = 40;
	ramp[5].axis = true;
	ramp[5].color = Black;
	App->physics->AddBody(ramp[5], 0);

	ramp[6].SetPos(295, 85, 326);
	ramp[6].SetRotation(140.0f, { 0,0,1 });
	ramp[6].size.x = 25;
	ramp[6].size.y = 2;
	ramp[6].size.z = 40;
	ramp[6].axis = true;
	ramp[6].color = White;
	App->physics->AddBody(ramp[6], 0);

	ramp[7].SetPos(280, 95, 328);
	ramp[7].SetRotation(160.0f, { 0,0,1 });
	ramp[7].size.x = 25;
	ramp[7].size.y = 2;
	ramp[7].size.z = 40;
	ramp[7].axis = true;
	ramp[7].color = Black;
	App->physics->AddBody(ramp[7], 0);

	ramp[8].SetPos(263, 98, 330);
	ramp[8].SetRotation(180.0f, { 0,0,1 });
	ramp[8].size.x = 25;
	ramp[8].size.y = 2;
	ramp[8].size.z = 40;
	ramp[8].axis = true;
	ramp[8].color = White;
	App->physics->AddBody(ramp[8], 0);

	ramp[9].SetPos(245, 0, 346);
	ramp[9].SetRotation(-20.0f, { 0,0,1 });
	ramp[9].size.x = 25;
	ramp[9].size.y = 2;
	ramp[9].size.z = 40;
	ramp[9].axis = true;
	ramp[9].color = White;
	App->physics->AddBody(ramp[9], 0);

	ramp[10].SetPos(230, 10, 344);
	ramp[10].SetRotation(-40.0f, { 0,0,1 });
	ramp[10].size.x = 25;
	ramp[10].size.y = 2;
	ramp[10].size.z = 40;
	ramp[10].axis = true;
	ramp[10].color = Black;
	App->physics->AddBody(ramp[10], 0);

	ramp[11].SetPos(218, 25, 342);
	ramp[11].SetRotation(-60.0f, { 0,0,1 });
	ramp[11].size.x = 25;
	ramp[11].size.y = 2;
	ramp[11].size.z = 40;
	ramp[11].axis = true;
	ramp[11].color = White;
	App->physics->AddBody(ramp[11], 0);

	ramp[12].SetPos(212, 40, 340);
	ramp[12].SetRotation(-80.0f, { 0,0,1 });
	ramp[12].size.x = 25;
	ramp[12].size.y = 2;
	ramp[12].size.z = 40;
	ramp[12].axis = true;
	ramp[12].color = Black;
	App->physics->AddBody(ramp[12], 0);

	ramp[13].SetPos(212, 55, 338);
	ramp[13].SetRotation(-100.0f, { 0,0,1 });
	ramp[13].size.x = 25;
	ramp[13].size.y = 2;
	ramp[13].size.z = 40;
	ramp[13].axis = true;
	ramp[13].color = White;
	App->physics->AddBody(ramp[13], 0);

	ramp[14].SetPos(218, 70, 336);
	ramp[14].SetRotation(-120.0f, { 0,0,1 });
	ramp[14].size.x = 25;
	ramp[14].size.y = 2;
	ramp[14].size.z = 40;
	ramp[14].axis = true;
	ramp[14].color = Black;
	App->physics->AddBody(ramp[14], 0);

	ramp[15].SetPos(230, 85, 334);
	ramp[15].SetRotation(-140.0f, { 0,0,1 });
	ramp[15].size.x = 25;
	ramp[15].size.y = 2;
	ramp[15].size.z = 40;
	ramp[15].axis = true;
	ramp[15].color = White;
	App->physics->AddBody(ramp[15], 0);

	ramp[16].SetPos(245, 95, 332);
	ramp[16].SetRotation(-160.0f, { 0,0,1 });
	ramp[16].size.x = 25;
	ramp[16].size.y = 2;
	ramp[16].size.z = 40;
	ramp[16].axis = true;
	ramp[16].color = Black;
	App->physics->AddBody(ramp[16], 0);

	ramp[34].SetPos(300, 0, 500);
	ramp[34].SetRotation(-5.0f, { 0,0,1 });
	ramp[34].size.x = 25;
	ramp[34].size.y = 2;
	ramp[34].size.z = 40;
	ramp[34].axis = true;
	ramp[34].color = Red;
	App->physics->AddBody(ramp[34], 0);


	




	ramp[17].SetPos(256, 0, 450);
	ramp[17].SetRotation(20.0f, { 1,0,0 });
	ramp[17].size.x = 250;
	ramp[17].size.y = 2;
	ramp[17].size.z = 20;
	ramp[17].axis = true;
	ramp[17].color = White;
	App->physics->AddBody(ramp[17], 0);

	ramp[18].SetPos(256, 4, 442);
	ramp[18].SetRotation(40.0f, { 1,0,0 });
	ramp[18].size.x = 250;
	ramp[18].size.y = 2;
	ramp[18].size.z = 20;
	ramp[18].axis = true;
	ramp[18].color = Black;
	App->physics->AddBody(ramp[18], 0);

	ramp[19].SetPos(256, 10, 436);
	ramp[19].SetRotation(60.0f, { 1,0,0 });
	ramp[19].size.x = 250;
	ramp[19].size.y = 2;
	ramp[19].size.z = 20;
	ramp[19].axis = true;
	ramp[19].color = White;
	App->physics->AddBody(ramp[19], 0);

	ramp[20].SetPos(256, 20, 431);
	ramp[20].SetRotation(80.0f, { 1,0,0 });
	ramp[20].size.x = 250;
	ramp[20].size.y = 2;
	ramp[20].size.z = 20;
	ramp[20].axis = true;
	ramp[20].color = Black;
	App->physics->AddBody(ramp[20], 0);

	ramp[21].SetPos(256, 35, 431);
	ramp[21].SetRotation(100.0f, { 1,0,0 });
	ramp[21].size.x = 250;
	ramp[21].size.y = 2;
	ramp[21].size.z = 20;
	ramp[21].axis = true;
	ramp[21].color = White;
	App->physics->AddBody(ramp[21], 0);

	ramp[22].SetPos(256, 45, 436);
	ramp[22].SetRotation(120.0f, { 1,0,0 });
	ramp[22].size.x = 250;
	ramp[22].size.y = 2;
	ramp[22].size.z = 20;
	ramp[22].axis = true;
	ramp[22].color = Black;
	App->physics->AddBody(ramp[22], 0);

	ramp[23].SetPos(256, 51, 442);
	ramp[23].SetRotation(140.0f, { 1,0,0 });
	ramp[23].size.x = 250;
	ramp[23].size.y = 2;
	ramp[23].size.z = 20;
	ramp[23].axis = true;
	ramp[23].color = White;
	App->physics->AddBody(ramp[23], 0);

	ramp[24].SetPos(256, 54, 448);
	ramp[24].SetRotation(160.0f, { 1,0,0 });
	ramp[24].size.x = 250;
	ramp[24].size.y = 2;
	ramp[24].size.z = 20;
	ramp[24].axis = true;
	ramp[24].color = Black;
	App->physics->AddBody(ramp[24], 0);

	ramp[25].SetPos(256, 56, 456);
	ramp[25].SetRotation(180.0f, { 1,0,0 });
	ramp[25].size.x = 250;
	ramp[25].size.y = 2;
	ramp[25].size.z = 20;
	ramp[25].axis = true;
	ramp[25].color = White;
	App->physics->AddBody(ramp[25], 0);

	ramp[26].SetPos(256, 0, 468);
	ramp[26].SetRotation(-20.0f, { 1,0,0 });
	ramp[26].size.x = 250;
	ramp[26].size.y = 2;
	ramp[26].size.z = 20;
	ramp[26].axis = true;
	ramp[26].color = White;
	App->physics->AddBody(ramp[26], 0);

	ramp[27].SetPos(256, 4, 474);
	ramp[27].SetRotation(-40.0f, { 1,0,0 });
	ramp[27].size.x = 250;
	ramp[27].size.y = 2;
	ramp[27].size.z = 20;
	ramp[27].axis = true;
	ramp[27].color = Black;
	App->physics->AddBody(ramp[27], 0);

	ramp[28].SetPos(256, 10, 480);
	ramp[28].SetRotation(-60.0f, { 1,0,0 });
	ramp[28].size.x = 250;
	ramp[28].size.y = 2;
	ramp[28].size.z = 20;
	ramp[28].axis = true;
	ramp[28].color = White;
	App->physics->AddBody(ramp[28], 0);

	ramp[29].SetPos(256, 20, 485);
	ramp[29].SetRotation(-80.0f, { 1,0,0 });
	ramp[29].size.x = 250;
	ramp[29].size.y = 2;
	ramp[29].size.z = 20;
	ramp[29].axis = true;
	ramp[29].color = Black;
	App->physics->AddBody(ramp[29], 0);

	ramp[30].SetPos(256, 35, 485);
	ramp[30].SetRotation(-100.0f, { 1,0,0 });
	ramp[30].size.x = 250;
	ramp[30].size.y = 2;
	ramp[30].size.z = 20;
	ramp[30].axis = true;
	ramp[30].color = White;
	App->physics->AddBody(ramp[30], 0);

	ramp[31].SetPos(256, 45, 480);
	ramp[31].SetRotation(-120.0f, { 1,0,0 });
	ramp[31].size.x = 250;
	ramp[31].size.y = 2;
	ramp[31].size.z = 20;
	ramp[31].axis = true;
	ramp[31].color = Black;
	App->physics->AddBody(ramp[31], 0);

	ramp[32].SetPos(256, 51, 474);
	ramp[32].SetRotation(-140.0f, { 1,0,0 });
	ramp[32].size.x = 250;
	ramp[32].size.y = 2;
	ramp[32].size.z = 20;
	ramp[32].axis = true;
	ramp[32].color = White;
	App->physics->AddBody(ramp[32], 0);

	ramp[33].SetPos(256, 54, 468);
	ramp[33].SetRotation(-160.0f, { 1,0,0 });
	ramp[33].size.x = 250;
	ramp[33].size.y = 2;
	ramp[33].size.z = 20;
	ramp[33].axis = true;
	ramp[33].color = Black;
	App->physics->AddBody(ramp[33], 0);

	//Limits-------------------
	limits[0].SetPos(256, 0, 56);
	limits[0].size.x = 47;
	limits[0].size.y = 40;
	limits[0].size.z = 111;
	limits[0].axis = true;
	limits[0].color = Lila;
	App->physics->AddBody(limits[0], 0);

	limits[1].SetPos(396, 0, 135);
	limits[1].size.x = 47;
	limits[1].size.y = 40;
	limits[1].size.z = 79;
	limits[1].axis = true;
	limits[1].color = Lila;
	App->physics->AddBody(limits[1], 0);

	limits[2].SetPos(109, 0, 187);
	limits[2].size.x = 43;
	limits[2].size.y = 40;
	limits[2].size.z = 195;
	limits[2].axis = true;
	limits[2].color = Lila;
	App->physics->AddBody(limits[2], 0);

	limits[3].SetPos(103, 0, 327);
	limits[3].size.x = 31;
	limits[3].size.y = 40;
	limits[3].size.z = 91;
	limits[3].axis = true;
	limits[3].color = Lila;
	App->physics->AddBody(limits[3], 0);

	limits[4].SetPos(123, 0, 397);
	limits[4].size.x = 71;
	limits[4].size.y = 40;
	limits[4].size.z = 51;
	limits[4].axis = true;
	limits[4].color = Lila;
	App->physics->AddBody(limits[4], 0);

	limits[5].SetPos(256, 0, 376);
	limits[5].size.x = 195;
	limits[5].size.y = 40;
	limits[5].size.z = 9;
	limits[5].axis = true;
	limits[5].color = Lila;
	App->physics->AddBody(limits[5], 0);

	limits[6].SetPos(385, 0, 389);
	limits[6].size.x = 63;
	limits[6].size.y = 40;
	limits[6].size.z = 35;
	limits[6].axis = true;
	limits[6].color = Lila;
	App->physics->AddBody(limits[6], 0);

	limits[7].SetPos(462, 0, 260);
	limits[7].size.x = 100;
	limits[7].size.y = 40;
	limits[7].size.z = 23;
	limits[7].axis = true;
	limits[7].color = Lila;
	App->physics->AddBody(limits[7], 0);

	limits[8].SetPos(369, 0, 267);
	limits[8].size.x = 87;
	limits[8].size.y = 40;
	limits[8].size.z = 9;
	limits[8].axis = true;
	limits[8].color = Lila;
	App->physics->AddBody(limits[8], 0);

	limits[9].SetPos(328, 0, 280);
	limits[9].size.x = 5;
	limits[9].size.y = 40;
	limits[9].size.z = 17;
	limits[9].axis = true;
	limits[9].color = Lila;
	App->physics->AddBody(limits[9], 0);

	limits[14].SetPos(285, 0, 286);
	limits[14].size.x = 81;
	limits[14].size.y = 40;
	limits[14].size.z = 5;
	limits[14].axis = true;
	limits[14].color = Lila;
	App->physics->AddBody(limits[14], 0);

	limits[15].SetPos(182, 0, 202);
	limits[15].size.x = 105;
	limits[15].size.y = 40;
	limits[15].size.z = 21;
	limits[15].axis = true;
	limits[15].color = Lila;
	App->physics->AddBody(limits[15], 0);

	limits[16].SetPos(289, 0, 196);
	limits[16].size.x = 109;
	limits[16].size.y = 40;
	limits[16].size.z = 9;
	limits[16].axis = true;
	limits[16].color = Lila;
	App->physics->AddBody(limits[16], 0);

	limits[17].SetPos(353, 0, 180);
	limits[17].size.x = 39;
	limits[17].size.y = 40;
	limits[17].size.z = 24;
	limits[17].axis = true;
	limits[17].color = Lila;
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

	limits[35].SetPos(11, 0, 213);
	limits[35].size.x = 1;
	limits[35].size.y = 15;
	limits[35].size.z = 1;
	limits[35].axis = true;
	limits[35].color = White;
	App->physics->AddBody(limits[35], 0);

	limits[36].SetPos(67, 0, 213);
	limits[36].size.x = 1;
	limits[36].size.y = 15;
	limits[36].size.z = 1;
	limits[36].axis = true;
	limits[36].color = White;
	App->physics->AddBody(limits[36], 0);

	limits[37].SetPos(11, 8, 213);
	limits[37].size.x = 4;
	limits[37].size.y = 4;
	limits[37].size.z = 4;
	limits[37].axis = true;
	limits[37].color = Red;
	App->physics->AddBody(limits[37], 0);

	limits[38].SetPos(67, 8, 213);
	limits[38].size.x = 4;
	limits[38].size.y = 4;
	limits[38].size.z = 4;
	limits[38].axis = true;
	limits[38].color = Red;
	App->physics->AddBody(limits[38], 0);

	limits[39].SetPos(255, 0, 122);
	limits[39].size.x = 1;
	limits[39].size.y = 15;
	limits[39].size.z = 1;
	limits[39].axis = true;
	limits[39].color = White;
	App->physics->AddBody(limits[39], 0);

	limits[40].SetPos(255, 0, 178);
	limits[40].size.x = 1;
	limits[40].size.y = 15;
	limits[40].size.z = 1;
	limits[40].axis = true;
	limits[40].color = White;
	App->physics->AddBody(limits[40], 0);

	limits[41].SetPos(255, 8, 122);
	limits[41].size.x = 4;
	limits[41].size.y = 4;
	limits[41].size.z = 4;
	limits[41].axis = true;
	limits[41].color = Red;
	App->physics->AddBody(limits[41], 0);

	limits[42].SetPos(255, 8, 178);
	limits[42].size.x = 4;
	limits[42].size.y = 4;
	limits[42].size.z = 4;
	limits[42].axis = true;
	limits[42].color = Red;
	App->physics->AddBody(limits[42], 0);

	//Sensor------------------------------

	sensor[0].SetPos(39, 0, 213);
	sensor[0].size.x = 40;
	sensor[0].size.y = 15;
	sensor[0].size.z = 1;
	sensor[0].axis = false;
	sensor[0].wire = true;
	sensor[0].color.Set(225, 225, 0);
	physSensor = App->physics->AddBody(sensor[0], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	sensor[1].SetPos(255, 0, 150);
	sensor[1].size.x = 1;
	sensor[1].size.y = 15;
	sensor[1].size.z = 30;
	sensor[1].axis = false;
	sensor[1].wire = false;
	sensor[1].color.Set(225, 225, 0);
	physSensor = App->physics->AddBody(sensor[1], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(3);

	sensor[2].SetPos(290, 0, 326);
	sensor[2].size.x = 1;
	sensor[2].size.y = 15;
	sensor[2].size.z = 15;
	sensor[2].axis = false;
	sensor[2].wire = true;
	sensor[2].color.Set(225, 225, 0);
	physSensor = App->physics->AddBody(sensor[2], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(4);

	sensor[3].SetPos(380, 0, 468);
	sensor[3].size.x = 1;
	sensor[3].size.y = 15;
	sensor[3].size.z = 15;
	sensor[3].axis = false;
	sensor[3].wire = true;
	sensor[3].color.Set(225, 225, 0);
	physSensor = App->physics->AddBody(sensor[3], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(5);

	sensor[4].SetPos(300, 0, 420);
	sensor[4].size.x = 1;
	sensor[4].size.y = 15;
	sensor[4].size.z = 15;
	sensor[4].axis = false;
	sensor[4].wire = true;
	sensor[4].color.Set(225, 225, 0);
	physSensor = App->physics->AddBody(sensor[4], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(6);

	sensor[5].SetPos(39, 2, 350);
	sensor[5].size.x = 10;
	sensor[5].size.y = 1;
	sensor[5].size.z = 15;
	sensor[5].axis = false;
	sensor[5].wire = false;
	sensor[5].color.Set(0, 225, 0);
	physSensor = App->physics->AddBody(sensor[5], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(7);

	sensor[6].SetPos(380, 2, 220);
	sensor[6].size.x = 15;
	sensor[6].size.y = 1;
	sensor[6].size.z = 10;
	sensor[6].axis = false;
	sensor[6].wire = false;
	sensor[6].color.Set(0, 225, 0);
	physSensor = App->physics->AddBody(sensor[6], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(7);

	sensor[7].SetPos(230, 2, 435);
	sensor[7].size.x = 15;
	sensor[7].size.y = 1;
	sensor[7].size.z = 10;
	sensor[7].axis = false;
	sensor[7].wire = false;
	sensor[7].color.Set(0, 225, 0);
	physSensor = App->physics->AddBody(sensor[7], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(7);

	flag[0].SetPos(30, 17, 214);
	flag[0].size.x = 2;
	flag[0].size.y = 2;
	flag[0].size.z = 2;
	flag[0].axis = true;
	flag[0].color = Black;
	App->physics->AddBody(flag[0], 0);

	flag[1].SetPos(40, 17, 214);
	flag[1].size.x = 2;
	flag[1].size.y = 2;
	flag[1].size.z = 2;
	flag[1].axis = true;
	flag[1].color = Black;
	App->physics->AddBody(flag[1], 0);

	flag[2].SetPos(50, 17, 214);
	flag[2].size.x = 2;
	flag[2].size.y = 2;
	flag[2].size.z = 2;
	flag[2].axis = true;
	flag[2].color = Black;
	App->physics->AddBody(flag[2], 0);

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

	flag[0].Render();
	flag[1].Render();
	flag[2].Render();

	secondsSinceInit = INITIAL_TIME - timer;

	if (secondsSinceInit == 2)
	{
		flag[0].color = Red;
	}
	else if (secondsSinceInit == 3)
	{
		flag[1].color = Red;
	}
	else if (secondsSinceInit == 4)
	{
		flag[2].color = Red;
	}
	else if (secondsSinceInit == 5)
	{
		for (int i = 0; i < 3; i++)
		{
			flag[i].color = Green;
		}
	}
	
	for (int i = 0; i < 40; i++)
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

	if (frames % 60 == 0 && timer > 0 && App->camera->finish == false)
	{
		if (App->player->turboTimer > 0)
		{
			App->player->turboTimer--;
		}
		App->player->turboSoundActive = true;
		timer--;
	}

	frames++;

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}