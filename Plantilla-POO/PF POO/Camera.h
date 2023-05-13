#ifndef __Camera
#define __Camera
#define TO_RAD(DEG) (DEG * 3.1416 / 180)
#define TO_DEG(RAD) (RAD / 3.1416 * 180.0)
#define ANGLE_INC 3.5
#define POSITION_INC 1


#include "VectorRR.h"
#include <math.h>

class Camera : public VectorRR
{
public:
	VectorRR posc, dirc;
	GLdouble px, py, pz, dx, dy, dz, ux, uy, uz,HV,Ppx,Ppz;
	int JV;
	bool JA=false;
	float angle = 0, dir = 0, MG = 0, MGu = 0, loop = 0;
	float viewVectorMag = 0, magX = 0, magZ = 0;

	bool ableToMove;

	Camera()
	{
	}

	void cameraInitialize()
	{
		px = 0, py = 25, pz = 0, dx = 25, dy = 25, dz = 25;
		ux = 0, uy = 1, uz = 0,JV=0;
		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
		viewVectorMag = sqrt(pow(dx - px, 2) + pow(dz - pz, 2));
		ableToMove = true;
	}

	void cameraUpdate()
	{
		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
	}

	void move(char movDir)
	{
		dir = 0;

		magX = dx - px;
		magZ = dz - pz;

		switch (movDir)
		{
		case 'f':
			dir = TO_DEG(atan2(magZ, magX));
			break;
		case 'b':
			dir = TO_DEG(atan2(magZ, magX)) - 180;
			break;
		case 'l':
			dir = TO_DEG(atan2(magZ, magX)) - 90;
			break;
		case 'r':
			dir = TO_DEG(atan2(magZ, magX)) + 90;
			break;
		}
		if (ableToMove)
		{

			Ppz = pz;
			Ppx = px;
			pz += POSITION_INC * sin(TO_RAD(dir));
			dz += POSITION_INC * sin(TO_RAD(dir));
			px += POSITION_INC * cos(TO_RAD(dir));
			dx += POSITION_INC * cos(TO_RAD(dir));
		}
	}

	void turnRight()
	{
		MG--;
		angle = angle + ANGLE_INC;
		dx = sin(TO_RAD(angle)) * viewVectorMag + px;
		dz = -cos(TO_RAD(angle)) * viewVectorMag + pz;
	}

	void turnLeft()
	{
		MG++;
		angle = angle - ANGLE_INC;
		dx = sin(TO_RAD(angle)) * viewVectorMag + px;
		dz = -cos(TO_RAD(angle)) * viewVectorMag + pz;
	}

	void turnUp()
	{
		if (HV < 15 ) {
			MGu++;
			HV += 1;
		}
	}

	void turnDown()
	{
		if (HV > -30 ){
			MGu--;
			HV -= 1;
		}
	}
	
};
#endif