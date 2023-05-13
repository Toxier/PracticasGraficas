#pragma once
#include "glew.h"
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Model.h"
#include "Terrain.h"

class Pickup{
public:
	Pickup();
	Pickup(float x, float y, float z, float hbs, float kind);
	~Pickup();


	bool hitbox(float px,float pz) {
	
		
		if ((px<(X + Hbs) && px>(X - Hbs)) && (pz <(Z + Hbs) && pz >(Z - Hbs))) {

			
			return true;

		}
		

	
		return false;
	}
	

	void draw(EDXFramework::Model* pickup) {

		R < 360 ? R+= 0.1f : R= 0;
		if (Updown >= 20.0f) {
			scale = -0.1f;
		}
		else
		{
			if (Updown <= 0.0f)
			{
				scale = 0.1f;
			}
		}

		Updown = Updown + scale;
		
		glPushMatrix();
		glTranslatef(X, Y + Updown / 12, Z);
		glScalef(10, 10, 10);
		glRotatef(R * 16, 0, 1, 0);
		pickup->Draw();
		glPopMatrix();
	

	
	};


private:
	float X, Y, Z, Hbs, Kind,R, Updown = 0.0f, scale = 0.1f;
	EDXFramework::Model *PickUp;
};

Pickup::Pickup()
{




}


Pickup::Pickup( float x, float y,float z,float hbs,float kind)
{

	X = x;
	Y = y;
	Z = z;
 	Hbs = hbs;
	Kind = kind;
	
	

}

Pickup::~Pickup()
{
}