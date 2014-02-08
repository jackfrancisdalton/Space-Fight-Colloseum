//
// The structure of the Graphics 1 OpenGL template is explained in README.txt
//

/*
GameActivity implementation


The comments in the file Activity.cpp give a little more info about each method

This activity is where the main game logic goes.
Most of your game code will go here
*/


#include <windows.h>		// Header File For Windows
#include <gl\gl.h>		// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <algorithm>
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"			// Needed to access member functions and variables from OpenGLApplication
#include "GameActivity.h"
#include "PlayerType1.h"

#define VIEW_SIZE 30.0					// The height of the view in WORLD SPACE


#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define DEG_2_RAD(x) (x * M_PI / 180.0)



GameActivity::GameActivity(OpenGLApplication *app): Activity(app)	
{
	camX = camY = 0.0;
	playerX = playerY = 0.0;
	rotateZ = 0.0;
	attackZ = 0.0;
	acceleration = 0.0;
	jump = false;
	falling = false;
	jumpStage = 1.0;
	powerORBRotate = 0.0;
	powerORBTranslateY = 2.0;
	powerORBOn = false;
	powerORBSize = 0.0;
	shieldScale = 0.0;
	shieldTime = 0.0;
	shieldOn = false;
	boostOn = false;
	maxSpeed = 5;
	playerX_spriteSheet_offset = 0.0;
	playerY_spriteSheet_offset = 0.0;
	player = new PlayerType1();
}

void GameActivity::initialise()
{	
		player.initialise();
		playerSpirteSheetTextureID = SOIL_load_OGL_texture("sprite_sheet.png",		
		SOIL_LOAD_AUTO,							
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);					

		healthIconTextureID = SOIL_load_OGL_texture("health_icon.png",		
		SOIL_LOAD_AUTO,							 
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void GameActivity::shutdown()
{
	glDeleteTextures(1, &playerTextureID);
}

void GameActivity::onSwitchIn()
{
	glClearColor(0.0,0.0,0.0,0.0);						//sets the clear colour to black
}

void GameActivity::onReshape(int width, int height)
{
	// If you need to do anything when the screen is resized, do it here

	// EXAMPLE CODE
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	double aspect = app->getAspectRatio();
	// The height of the visible area is defined by VIEW_SIZE. Split it half each way around the origin, hence the *0.5
	// Take the aspect ratio into consideration when computing the width of the visible area
	gluOrtho2D(-VIEW_SIZE*0.5*aspect, VIEW_SIZE*0.5*aspect,  -VIEW_SIZE*0.5, VIEW_SIZE*0.5);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void GameActivity::update(double deltaT, double prevDeltaT)
{
	player.update(deltaT,prevDeltaT,inputState);
}

void GameActivity::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//*******************************HUD ORB1
	glPushMatrix();
	glTranslated(12.0, -13.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(1, 1);
		glVertex2f(1, 1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
	glEnd();
	
	glDisable (GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//*******************************HUD ORB2
	glPushMatrix();
	glTranslated(14.0, -13.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(1, 1);
		glVertex2f(1, 1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
	glEnd();
	
	glDisable (GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//*******************************HUD ORB3
	glPushMatrix();
	
	glTranslated(16.0, -13.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(1, 1);
		glVertex2f(1, 1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
	glEnd();
	
	glDisable (GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glRotated(-rotateZ,0.0, 0.0, 1);
	glTranslated(-playerX, -playerY, 0.0);
	renderDebugGrid(-100.0, -100.0, 400.0, 400.0, 30, 30);

	//***********************************************************STATIONARY ORB
	glPushMatrix();
	glTranslated(0.0, 3.0, 0.9);
	glBindTexture(GL_TEXTURE_2D, shieldTextureID);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(1, 1);
		glVertex2f(1, 1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
	glEnd();
	
	glDisable (GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//********************************************************BACKGROUND
	glBindTexture(GL_TEXTURE_2D, playerTextureID);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(1, 1);
		glVertex2f(1, 1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
	glEnd();

	glDisable (GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	//***********************************************************PLAYER
	glPushMatrix();
	player.render;
	glPopMatrix();
	glFlush();
}

void GameActivity::onMouseDown(int button, int mouseX, int mouseY)
{
	// This method will be invoked when a mouse button is pressed
	// button: 0=LEFT, 1=MIDDLE, 2=RIGHT
	// mouseX and mouseY: position
}

void GameActivity::onMouseUp(int button, int mouseX, int mouseY)
{
	// This method will be invoked when a mouse button is released
	// button: 0=LEFT, 1=MIDDLE, 2=RIGHT
	// mouseX and mouseY: position
}

void GameActivity::onMouseMove(int mouseX, int mouseY)
{
	// This method will be invoked when the mouse is moved
	// mouseX and mouseY: position
}

void GameActivity::onKeyDown(int key)
{
	if (key == VK_F1)
	{
		// F1; switch to end screen activity
		app->setCurrentActivity(app->endScreen);
	}
	if(key == VK_RETURN) {

		app->setCurrentActivity(app->pauseScreen);
	}
}

void GameActivity::onKeyUp(int key)									
{
}

void GameActivity::chooseWizardCharacter()
{
}

void GameActivity::chooseWarriorCharacter()
{
}

void GameActivity::renderDebugGrid(float left, float bottom, float width, float height, int hSegments, int vSegments)
{
	// Render a grey grid using lines
	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_LINES);

	// Vertical lines
	float dx = width / hSegments;
	float x = left;
	for (int i = 0; i <= hSegments; i++)
	{
		glVertex2f(x, bottom);
		glVertex2f(x, bottom + height);

		x += dx;
	}
	
	// Horizontal lines
	float dy = height / vSegments;
	float y = bottom;
	for (int i = 0; i <= hSegments; i++)
	{
		glVertex2f(left, y);
		glVertex2f(left + width, y);

		y += dy;
	}

	glEnd();
}

