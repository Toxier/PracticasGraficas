#ifndef __Escena
#define __Escena

#include <gl\GLU.h>
#include <gl\GL.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "Model.h"
#include "Water.h"
#include "Billboard.h"
#include "Fog.h"
#include "Camera.h"
#include "Enemy.h"
#include "Pickup.h"

#define BILLSIZE 50

//BIENVENIDO AL ARCHIVO MAS IMPORTANTE DE TU PROYECTO

class Scene : public Camera
{
public:
	bool Drawtru=false,ST=false,Disco=false,HB=false,Tm=false;
	bool Picked[5] = {false};
	HWND hWnd = 0;
	int CR = 0,Seed;
	short int skyIndex, lightIndex;
	float skyRotation, Updown=0.0f, scale = 0.1f, scale2 =1;
	float JS=0;
	SkyDome* skyDome = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//sky.jpg");
		SkyDome * skyShield = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//skyShield.png");
		Fog* Fogi;
	Terrain *terrain;
	Water *lago;
	GLfloat AmbMat[4] = { 255, 255, 120, 1 }, FColor[4] = {255,255,255,1};
	float Cx = 0, Cz = 0, Cm = 0, cm = 0, CB = 0;
int Animate=1;
int counter = 0;
	EDXFramework::Model  *PC,*Home,*Gun,*Gun2,*Gun3,*GunH,*Medkit,*AmmoPack,*Truck,*Mecha,*Fences,*Tree,*Scrap;
	EDXFramework::Model *Spider,*Spider2,*Cow,*Pig,*Chiken,*Cat;
	Billboard *billBoard[BILLSIZE];
	Enemy Enemi;
	Pickup *AmmoP,*Pick1,*Pick2,*Pick3,*Pick4,*Pick5;
	

	Scene(HWND hWnd)
	{

		Seed = rand() % 4 + 1;
		this->hWnd = hWnd;
		skyIndex = lightIndex, skyRotation = 0;
		
		GLfloat AmbPos[] = { 0, 400, 400, 1 };

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, AmbPos);

		
	
		
	
         lago= new Water(hWnd, L"Imagenes//wata.bmp", L"Imagenes//water.bmp", 1000, 1000);
		terrain = new Terrain(hWnd, L"Imagenes//terreno.bmp", L"Imagenes//test1.jpg", L"Imagenes//Tierra.jpg", 500, 500);
		Home = new EDXFramework::Model("Modelos//BarnNew//Home.obj", "Modelos//BarnNew//Barn2.bmp", 1);
		Truck = new EDXFramework::Model("Modelos//Mapstuff//Truck.obj", "Modelos//Mapstuff//Truck.bmp", 1);
		Tree = new EDXFramework::Model("Modelos//Mapstuff//Tree.obj", "Modelos//Mapstuff//Tree.bmp", 1);
		Mecha = new EDXFramework::Model("Modelos//Mapstuff//Mecha.obj", "Modelos//Mapstuff//Mecha.bmp", 1);
		Fences = new EDXFramework::Model("Modelos//Mapstuff//Fences.obj", "Modelos//Mapstuff//Fences.bmp", 1);
		Cow = new EDXFramework::Model("Modelos//Cow//Cow.obj", "Modelos//Cow//Cow.bmp", 1);
		Cat = new EDXFramework::Model("Modelos//Cow//Cat.obj", "Modelos//Cow//Cat.bmp", 1);
		Pig = new EDXFramework::Model("Modelos//Cow//Pig.obj", "Modelos//Cow//Pig.bmp", 1);
		Chiken = new EDXFramework::Model("Modelos//Cow//Chiken.obj", "Modelos//Cow//Chiken.bmp", 1);
		Spider2 = new EDXFramework::Model("Modelos//Spider//Spider2.obj", "Modelos//Spider//Spider2.bmp", 1);
		Spider = new EDXFramework::Model("Modelos//Spider//Spider.obj", "Modelos//Spider//Spider.bmp", 1);
		Gun = new EDXFramework::Model("Modelos//Gun//Gun.obj", "Modelos//Gun//Gun.bmp", 1);
		Gun2 = new EDXFramework::Model("Modelos//Gun//Shotgun.obj", "Modelos//Gun//Shotgun.bmp", 1);
		Gun3 = new EDXFramework::Model("Modelos//Gun//Rifle.obj", "Modelos//Gun//Rifle.bmp", 1);
		GunH = new EDXFramework::Model("Modelos//Gun//Gun2.obj", "Modelos//Gun//Gun.bmp", 1);
		Medkit = new EDXFramework::Model("Modelos//PickUps//Medkit.obj", "Modelos//PickUps//Medkit.bmp", 1);
		AmmoPack = new EDXFramework::Model("Modelos//PickUps//Ammopack.obj", "Modelos//PickUps//Ammopack.bmp", 1);
		Scrap = new EDXFramework::Model("Modelos//PickUps//Scrap.obj", "Modelos//PickUps//Scrap.bmp", 1);

		switch (Seed)
		{
		case 1:
			Pick1=new Pickup(115, 56, -220,8,1);
			Pick2 = new Pickup(105, 56, -48, 8, 1);
			Pick3 = new Pickup(135, 56, -202, 8, 1);
			Pick4 = new Pickup(68, 56, -172, 8, 1);
			Pick5 = new Pickup(100, 56, -233, 8, 1);

			break;
		case 2:
			Pick1 = new Pickup(100, 56, -233, 8, 1);
			Pick2 = new Pickup(75, 56, -186, 8, 1);
			Pick3 = new Pickup(135, 56, -202, 8, 1);
			Pick4 = new Pickup(229, 56, -144, 8, 1);
			Pick5 = new Pickup(-127, 32, 133, 8, 1);
			break;
		case 3:
			Pick1 = new Pickup(115, 56, -220, 8, 1);
			Pick2 = new Pickup(229, 56, -144, 8, 1);
			Pick3 = new Pickup(224, 56, 223, 8, 1);
			Pick4 = new Pickup(-130, 0, 1, 8, 1);
			Pick5 = new Pickup(68, 56, -172, 8, 1);
			break;
		case 4:
			Pick1 = new Pickup(-127, 32, 133, 8, 1);
			Pick2 = new Pickup(100, 56, -233, 8, 1);
			Pick3 = new Pickup(105, 56, -48, 8, 1);
			Pick4 = new Pickup(135, 56, -202, 8, 1);
			Pick5 = new Pickup(75, 56, -186, 8, 1);
			break;
		default:
			break;
		}






		AmmoP = new Pickup(129, 63.0f, -222,5,1);
		Billboards(billBoard, hWnd);

		

		cameraInitialize();
	}

	void Hitbox(int x,int x1, int z, int z1) {
	
		if ((px<x1 && px>x)&& (pz <z && pz > z1)) {
		
			ableToMove = false;
			px = Ppx;
			pz = Ppz;

		}
		else { ableToMove = true; }
	
		
	
	}


	void Billboards(Billboard *bills[], HWND hWnd)
	{

		int aux1 = 106;
		int aux2 = 103;
		
			bills[1] = new Billboard(hWnd, L"Imagenes//grass.png", 100, 100, aux1, 62, aux2);
		
		
	}
	

	void render(HDC hDC)
	{


//		billBoard[2] = new Billboard(hWnd, L"Imagenes//grass.png", 10, 10, px, py, pz);


		skyRotation < 360 ? skyRotation +=0.1f : skyRotation = 0;
		//CowBackflip (Press Space to start)
 		if (JS <= 0 && loop >= 1)
		{	JA = false;
			CB = 0;}
		if (JA)
		{
			if (JS>=20)
			{scale2 = -0.4;
			loop = 1;}
			if (JS<=0)
			{scale2 = 0.4;}
			CB += 7.2;
			JS += scale2;
		}

		

		//CowMovePattern

		if (Cx <= 0 && Cz >= 30)
		{
			ST = true;
			cm = 0;
			Cm = -0.5f;
		}
		if (Cx<=0 && Cz<=0)
		{
			ST = true;
			Cm = 0;
			cm = +0.5f;

		}
		if (Cx >= 30 && Cz <= 0)
		{
			ST = true;
			cm = 0;
			Cm = +0.5f;
		}
		if (Cx >= 30 && Cz >= 30)
		{
			ST = true;
			Cm = 0;
		cm = -0.5f;
		}
		if (ST)
		{
			if (CR % 90==0 && CR!=0)
			{
				ST = false;
			}
			CR < 360 ? CR -= 2 : CR = 0;
		}
		if (!ST)
		{
			Cx += cm;
			Cz += Cm;
		}
		



		
		
		
	


		//ItemUpdown

		if (Updown >= 20.0f ) {
			scale = -0.1f;
		}
		else
		{
			if (Updown<= 0.0f)
			{
				scale =0.1f;
			}
		}

		Updown = Updown + scale;
		
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glLoadIdentity();
		GLfloat AmbInt[] = { 1, 1, 1, 1 };;
		if (Disco)
		{
			AmbInt[0] =  Ppz - pz;
			AmbInt[1] =  Ppx - px;
			AmbInt[2] = px - pz, 1 ;
		
		}
	
		
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
	
		py = (terrain->Superficie(px, pz) * 4 + 6) + JV;
		dy = (terrain->Superficie(px, pz) * 4 + 6) + HV+JV;
	
		cameraUpdate();
		
		Hitbox( 249, 250,250, -249);
		Hitbox(-250, -249, 250, -249);
		Hitbox( -249, 250, 250,249 );
		Hitbox(  -249, 250, -249, -250);
	

		


		
		//Skydome
		glPushMatrix();
			glTranslatef(0, 8, 0);
			glRotatef(skyRotation, 0, 1, 0);
			skyDome->Draw();
		glPopMatrix();
		if (Drawtru) {

			//Skydome
			glPushMatrix();
			glTranslatef(0, 8, 0);
			glRotatef(skyRotation, 0, 1, 0);
			skyShield->Draw();
			glPopMatrix();

		}
		//Terreno
		glPushMatrix();
			glScalef(1, 4, 1);
			terrain->Draw();
		glPopMatrix();

		glPushMatrix();
		glScalef(2, 1, 2);
		glTranslatef(0, 27, 0);
		lago->Draw();
		glPopMatrix();


		if (!Tm) {
			Enemi.move(terrain);
			
		}
		Enemi.UpdatePlayer(px, pz, dx, dz);
		Enemi.draw2(Spider);
		Enemi.hitbox(px,pz);
		if (Enemi.getCounter() > 3) {
		
			Tm = true;
		
		}
		
	
		
		
		
		
		
		if (!Picked[0]) {
		
			Picked[0] = Pick1->hitbox(px, pz);
			Pick1->draw(Gun2);
		
		}
		if (!Picked[1]) {

			Picked[1] = Pick2->hitbox(px, pz);
			Pick2->draw(Gun3);


		}
	
		if (!Picked[2]) {

			Picked[2] = Pick3->hitbox(px, pz);
			Pick3->draw(Scrap);
			counter++;

		}
		if (!Picked[3]) {

			Picked[3] = Pick4->hitbox(px, pz);
			Pick4->draw(Scrap);
			counter++;

		}
		if (!Picked[4]) {

			Picked[4] = Pick5->hitbox(px, pz);

			Pick5->draw(Scrap);
			counter++;


		}
		
		
	
		

		//Home
		glPushMatrix();
		glTranslatef(100, 52, -170);
		glRotatef(-90, 0, 1, 0);
		Home->Draw();
		glPopMatrix();
		Hitbox(84,89,-172,-229);
		Hitbox(84, 94, -172, -178);
		Hitbox(84, 123, -224, -229);
		Hitbox(117, 122, -214, -229);
		Hitbox(117, 142, -210, -216);
		Hitbox(136, 141, -196, -216);
		Hitbox(128, 141, -196, -202);
		Hitbox(117, 124, -196, -202);
		Hitbox(117, 120, -174, -202);
		Hitbox(111, 120, -172, -178);


		//Mecha
		glPushMatrix();
		glTranslatef(129, 57.0f, -222);
		glScalef(50, 50, 50);
		glRotatef(90, 0, 1, 0);
		Mecha->Draw();
		glPopMatrix();

		//Fences
		glPushMatrix();
		glTranslatef(192, 56.2f, -141);
		glScalef(4, 4, 4);
		Fences->Draw();
		glPopMatrix();

		//Tree
		glPushMatrix();
		glTranslatef(100, 56.5f, -50);
		glScalef(10, 10, 10);
		Tree->Draw();
		glPopMatrix();


		
		//Truck
		glPushMatrix();
		glTranslatef(75, 56.6f, -172 );
		glScalef(20, 20, 20);
		Truck->Draw();
		glPopMatrix();
		Hitbox(69, 80, -159, -185);


		//Spider
		glPushMatrix();
		glTranslatef(0, 36.6, -80);
		glScalef(15,15,15);
	
		Spider->Draw();
		glPopMatrix();

		//Spider2
		glPushMatrix();
		glTranslatef(0, 34, -100);
		glScalef(2, 2, 2);
		glRotatef(90, 0, 1, 0);
		Spider2->Draw();
		glPopMatrix();

		
	


		//Medkit
		glPushMatrix();
		glTranslatef(132, 57 + Updown / 24, -193);
		glScalef(20, 20, 20);
		glRotatef(skyRotation *16, 0, 1, 0);
		Medkit->Draw();
		glPopMatrix();
		//Ammo
		glPushMatrix();
		glTranslatef(135, 57 + Updown/24, -193);
		glScalef(20, 20, 20);
		glRotatef(skyRotation *16, 0, 1, 0);
		AmmoPack->Draw();
		glPopMatrix();

		if (AmmoP->hitbox(px, pz)) {
			AmmoP->draw(AmmoPack); 
			if (counter>3)
			{

				Disco = true;

			}
		
		
		}
		
	

		if (Drawtru) {

		

			//Shotgun
			glPushMatrix();
			glTranslatef(0, 35 + Updown/24, -117);
			glScalef(10, 10, 10);
	    	glRotatef(skyRotation * 16, 0, 1, 0);
	    	Gun2->Draw();
	    	glPopMatrix();

			//Rifle
			glPushMatrix();
			glTranslatef(0, 35+Updown / 24, -107);
			glScalef(10, 10, 10);
			glRotatef(skyRotation * 16, 0, 1, 0);
			Gun3->Draw();
			glPopMatrix();
			//Pistola
			glPushMatrix();
			glTranslatef(0, 35 + Updown / 24, -112);
			glScalef(10, 10, 10);
			glRotatef(skyRotation * 16, 0, 1, 0);
			Gun->Draw();
			glPopMatrix();

		
		
		}
		//Gunhand
		glPushMatrix();
		glTranslatef(px , py-0.5 , pz );
		glScalef(3, 3, 3);
		glRotatef(MG*3.5, 0, 1, 0);
		glRotatef(MGu/2 * 3.5, 1, 0, 0);
		GunH->Draw();
		glPopMatrix();

		//cow	
		glPushMatrix();
		glTranslatef(190 + Cx, (JS / 2) + 60.0f, -175 + Cz);
		glScalef(500, 500, 500);
		glRotatef(CR, 0, 1, 0);
		glRotatef(CB, 1, 0, 0);
		Cow->Draw();
		glPopMatrix();

	//Pollo
		glPushMatrix();
		glTranslatef(192 + Cx/2,  57.0f, -183 + Cz/2);
		glScalef(5, 5, 5);
		glRotatef(CR+180, 0, 1, 0);
		Chiken->Draw();
		glPopMatrix();
		//Cerdo
		glPushMatrix();
		glTranslatef(200 + Cx / 3,  57.0f, -177 + Cz);
		glScalef(5, 5, 5);
		glRotatef(CR+180, 0, 1, 0);
		Pig->Draw();
		glPopMatrix();
		//Cat
		glPushMatrix();
		glTranslatef(117 + Cx, + 57.0f, -114 + Cz);
		glScalef(1, 1, 1);
		glRotatef(CR+90, 0, 1, 0);
		
		Cat->Draw();
		glPopMatrix();


	


		glPushMatrix();
		
			billBoard[1]->Draw(px, py, pz);
			
		
			
		glPopMatrix();


		SwapBuffers(hDC);
		
	}




	~Scene()
	{
		//NO OLVIDES PONER AQUI TODOS TUS PUNTEROS
		delete skyDome;
		delete billBoard;
		delete skyShield;
		delete terrain;
		delete Home;
		delete Spider;
		delete Spider2;
		delete Truck;
		delete Gun;
		delete Gun2;
		delete Gun3;
		delete GunH;
		delete Cow;
		delete Pig;
		delete Chiken;
		delete AmmoPack;
		delete Medkit;
		delete Mecha;
		delete Fences;
		delete Tree;
		delete Cat;
		delete Scrap;
	
		delete Pick1;
		delete Pick2;
		delete Pick3;
		delete Pick4;
		delete Pick5;
		delete AmmoP;
		//*Cow, * Gun, * Gun2, * Gun3, * Medkit, * AmmoPack
	}
};
#endif
