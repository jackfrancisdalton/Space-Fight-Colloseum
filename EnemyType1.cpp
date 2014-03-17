#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "EnemyType1.h"
#include <random>
#include <ctime>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)

EnemyType1::EnemyType1() : Enemy()
{
	textureX = textureY = 0.25;
	refreshWait = 1000;
	refreshIndex = 1;
	frameCounter = 0.0;
	speed = defaultSpeed = 6;
	enemyPoly = polygon(4);
	enemyPolyN = polygon(4);
	blackHoleCollsion = false;
	deadState = false;
}
/* use for testing enemies
EnemyType1::EnemyType1(int idVal) : Enemy()
{
	id = idVal;
	textureX = textureY = 0.25;
	refreshWait = 1000;
	refreshIndex = 1;
	frameCounter = 0.0;
	speed = 10;
	enemyPoly = polygon(4);
	enemyPolyN = polygon(4);
}
*/
void EnemyType1::initialise()
{
	enemyTextureId = SOIL_load_OGL_texture("square-enemy.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	//srand(time(NULL));
	posX = -75;
	posY = (rand() % 10 - 5) * 10;
	rot = 0.0;

	enemyPolyN.vert[0].x = enemyPoly.vert[0].x = -enemySize;
	enemyPolyN.vert[0].y = enemyPoly.vert[0].y = -enemySize;
	enemyPolyN.vert[1].x = enemyPoly.vert[1].x = enemySize;
	enemyPolyN.vert[1].y = enemyPoly.vert[1].y = -enemySize;
	enemyPolyN.vert[2].x = enemyPoly.vert[2].x = enemySize;
	enemyPolyN.vert[2].y = enemyPoly.vert[2].y = enemySize;
	enemyPolyN.vert[3].x = enemyPoly.vert[3].x = -enemySize;
	enemyPolyN.vert[3].y = enemyPoly.vert[3].y = enemySize;
}

void EnemyType1::update(double deltaT, double prevDeltaT, double playerX, double playerY)
{
	double rotRads = atan2(posY - playerY, posX - playerX); //trig function for angle of zombie
	rot = rotRads * (180.0 / M_PI); // convert to deg

	double playerDirSin = sin(rotRads); //calculates direction for y
	double playerDirCos = cos(rotRads); //calculates direction for x

	posX -= playerDirCos * speed * deltaT;
	posY -= playerDirSin * speed * deltaT;

	setTraMat(mb1, posX, posY, 0.0);
	setRotMat(mb2, M_PI*rot / 180.0, 2);
	MultMat(mb1, mb2, mb);
	for (int i = 0; i < 4; ++i){
		MultMatPre2DPoint(mb, &enemyPoly.vert[i], &enemyPolyN.vert[i]);
	}
}

void EnemyType1::render()
{
	glPushMatrix();
	glTranslated(posX, posY, 0.0);
	glRotated(rot, 0.0, 0.0, 1.0);
	
	glBindTexture(GL_TEXTURE_2D, enemyTextureId);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(-enemySize, -enemySize);
		glTexCoord2f(0.0, 1.0); glVertex2f(enemySize, -enemySize);
		glTexCoord2f(1.0, 1.0); glVertex2f(enemySize, enemySize);
		glTexCoord2f(1.0, 0.0); glVertex2f(-enemySize, enemySize);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

