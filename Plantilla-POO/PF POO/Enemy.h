#pragma once
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Model.h"
#include "Terrain.h"
#include "Pickup.h"








class Enemy {

public:
	Enemy();
	~Enemy();



	EDXFramework::Model *Modelo,*Pick1,*Pick2;
	Pickup* Drop;
	GLdouble Mx = -130, My =6, Mz=1,MA=0,MM=0,SM=0;
	GLdouble Px = 0, Pz = 0,Cx=0,Cz=0,PM=0;
	GLdouble Dx = 1, Dz = 0,D2x = 1, D2z = 0;
	
	int counter=0,PU=0,P3=0;


	void die() {
		PU = rand() % 20+1;
		Drop = new Pickup(Mx, My, Mz, 8, 1);
		Mx = -130;
		Mz = 1;
		
		if (PU%2==0)
		{
			if (PU>10)
			{
				Drop->draw(Pick1);
				P3 = 1;
			}
			else {
			
				Drop->draw(Pick2);
				P3 = 2;
			}
			}
		
	
	}


	void Shoot() {
		MM = Dx / Dz;
		PM = D2x / D2z;
		SM = MM - PM;
		SM *= SM;
		if (SM < 0.2)
		{
			die();
		}

	}

	bool hitbox(float px, float pz) {


		if ((px<(Mx + 8) && px>(Mx - 8)) && (pz <(Mz + 8) && pz >(Mz - 8))) {

			counter++;
			return true;
			

		}



		return false;
	}


	void UpdatePlayer(GLdouble px ,GLdouble pz, GLdouble cx, GLdouble cz){
		Px = px;
		Pz = pz;
		Cx = cx;
		Cz = cz;
		Dx = Mx - Px;
		Dz = Mz - Pz;
		D2x = Cx - Px;
		D2z = Cz - Pz;
		if(PU!=0) {
		
			if (P3 = 1) {
				Drop->draw(Pick1);
			}
			if (P3 == 2)
			{
				Drop->draw(Pick2);

			}



			if (Drop->hitbox(px, pz)) {
				if (P3 = 1) { counter--; }
				if (P3 == 2)
				{

				}
				Drop = new Pickup(251, 0, 0, 8, 1);
			
			}

		
		}
	
		
		
	
	
	}
	int getCounter() {
	
		return counter;
	
	}
	
	void draw2(EDXFramework::Model *Model) {
		glPushMatrix();
		glTranslatef(Mx, My+3, Mz);
		glScalef(15, 15, 15);
		glRotatef(MA-90, 0, 1, 0);
		Model->Draw();
		glPopMatrix();




	}
	void move(Terrain* Terreno) {

		double M =  Dx/ Dz;

		MA = atan(M)* 180 / 3.14;
		My = (Terreno->Superficie(Mx, Mz) * 4 +3);
		
		if (Dx < -0.2 || Dx > 0.2) {
		
			if (Dx < 0)
			{
				Mx += 0.4;
			}
			else
			{
				Mx -= 0.4;
			}
		
		
		}
		if (Dz < -0.2 || Dz > 0.2) {
			if (Dz < 0)
			{
				Mz += 0.4;
			}
			else
			{
				Mz -= 0.4;
			}
		}
	}

	






};
Enemy::Enemy()
{

	Pick1 = new EDXFramework::Model("Modelos//PickUps//Medkit.obj", "Modelos//PickUps//Medkit.bmp", 1);
	Pick2 = new EDXFramework::Model("Modelos//PickUps//Ammopack.obj", "Modelos//PickUps//Ammopack.bmp", 1);

}

Enemy::~Enemy()
{
}
