#pragma comment (lib, "winmm.lib")
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>		// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <algorithm>
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"			// Needed to access member functions and variables from OpenGLApplication
#include "GameActivity.h"
#include "Collision.h"
#include <iostream>
#include <vector>
#include <mmsystem.h>

#define MAP_SIZEX 10
#define MAP_SIZEY 10
#define VIEW_SIZE 80.0
#define CAMERA_MOVEMENT_SPEED 10.0
#define PLAYER_MOVEMENT_SPEED 10.0
#define JUMP_HEIGHT 2.5
#define SHIELD_OSCILATION_SPEED 1.5
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)
#define SHIELD_GROWTH_RATE 1.0
#define TIME_TO_WAIT_AFTER_DEATH 10.00
#define CARRY_ON_JUMP 5.0

char map[20][20] = {
	{ 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5 },
};

GameActivity::GameActivity(OpenGLApplication *app): Activity(app)	
{
	currentGameTime = 0.0;
	score = 0.0;
	camX = camY = camRot = 0.0;
	int skinID = 0;
	mapWidth = 20;
	mapHeight = 20;
	OrbsPickedUp = 0;
	numberOfScoreOrbs = 3;
	rotateCamera = false;
	
	for (int i = 0; i < 3; i++) {
		EnemyType1* e = new EnemyType1();
		enemyList.push_back(e);
	}

	for (int i = 0; i < 3; i++) {
		EnemyType2* e = new EnemyType2();
		enemyList.push_back(e);
	}

	for (int i = 0; i < 3; i++) {
		EnemyType3* e = new EnemyType3();
		enemyList.push_back(e);
	}
	
	for (int i = 0; i < 1; i++) {
		JumpPad* p = new JumpPad();
		p->initialise();
		jumpPadList.push_back(p);
	}
	
	for (int i = 0; i < 1; i++) {
		BlackHole* b = new BlackHole();
		b->initialise();
		blackHoleList.push_back(b);
	}
	
	for (int i = 0; i < 1; i++) {
		ShieldPickUp* s = new ShieldPickUp();
		s->initialise();
		shieldPickUpList.push_back(s);
	}
	
	for (int i = 0; i < numberOfScoreOrbs; i++) {
		ScoreOrb* s = new ScoreOrb();
		s->initialise();
		scoreOrbList.push_back(s);
	}
	
	for each (Enemy* e in enemyList) {
		e->initialise();
	}
	mainHUD = HUD(VIEW_SIZE*0.5*aspect, -VIEW_SIZE*0.5);
}

void GameActivity::initialise()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	
	player = PlayerShip(chosenShipID);
	player.initialise();
	mainHUD.initialise();

	wallRightId = SOIL_load_OGL_texture("wall-right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	wallLeftId = SOIL_load_OGL_texture("wall-left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	wallBotId = SOIL_load_OGL_texture("wall-bot.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	wallTopId = SOIL_load_OGL_texture("wall-top.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	cornerWall = SOIL_load_OGL_texture("corner-wall.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	spaceTextureID = SOIL_load_OGL_texture("space-texture.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	levelStart = true;
	levelWon = false;
	levelLost = false;
}

void GameActivity::shutdown()
{
	glDeleteTextures(1, &healthIconTextureID);
}

void GameActivity::onSwitchIn()
{
	glClearColor(0.0,0.0,0.0,0.0);						//sets the clear colour to black
}

void GameActivity::onReshape(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	aspect = app->getAspectRatio();
	gluOrtho2D(-VIEW_SIZE*0.5*aspect, VIEW_SIZE*0.5*aspect,  -VIEW_SIZE*0.5, VIEW_SIZE*0.5);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	mainHUD.setPosition(VIEW_SIZE*0.5*aspect, -VIEW_SIZE*0.5);
}

void GameActivity::update(double deltaT, double prevDeltaT)
{

	if (levelStart == true)
	{
		mainHUD.setMainMessage("message start");
	}
	else if (levelLost == true)
	{
		mainHUD.setMainMessage("message Lost");
	}
	else if (levelWon == true)
	{
		mainHUD.setMainMessage("message Won");
	}
	else
	{
		mainHUD.setPosition(VIEW_SIZE*0.5*aspect, -VIEW_SIZE*0.5);
		currentGameTime += 1 * deltaT;
		player.update(deltaT, prevDeltaT, inputState);

		//IF OPTION 1 IS ACTIVE ELSE OPTION 2
		if (rotateCamera == false) 
		{
			camRot = 0;
		}
		else 
		{
			camRot = player.getPlayerRot();
		}
		
		camX = player.getPlayerX();
		camY = player.getPlayerY();

		for each (Enemy* e in enemyList)
		{
			e->update(deltaT, prevDeltaT, player.getPlayerX(), player.getPlayerY());
		}

		for each (BlackHole* b in blackHoleList)
		{
			b->update(deltaT, prevDeltaT);
		}

		for each (JumpPad* j in jumpPadList)
		{
			j->update(deltaT, prevDeltaT);
		}

		for each (ShieldPickUp* s in shieldPickUpList)
		{
			s->update(deltaT, prevDeltaT);
		}

		for each (ScoreOrb* s in scoreOrbList)
		{
			s->update(deltaT, prevDeltaT);
		}

		for (int i = 0; i < enemyList.size() - 1; i++)
		{
			for (int j = i + 1; j < enemyList.size(); j++)
			{
				if (!SAT2D(&enemyList.at(i)->getPolygonN(), &enemyList.at(j)->getPolygonN())){
					enemyList.at(i);
				}
			}
		}

		for each(JumpPad* p in jumpPadList)
		{
			if (!SAT2D(&player.getPolygonN(), &p->getPolygonN()))
			{
				player.setPlayerJumpOn();
			}
		}

		for each(BlackHole* b in blackHoleList)
		{
			if (!SAT2D(&player.getPolygonN(), &b->getPolygonN()) && player.checkShouldColide() == false)
			{
				player.setBlackHoleSlowOn();
			}
		}

		for (int i = 0; i < shieldPickUpList.size(); i++)
		{
			if (!SAT2D(&player.getPolygonN(), &shieldPickUpList.at(i)->getPolygonN()) && player.getJumpState() == false)
			{
				player.shieldToggleOn();
				shieldPickUpList.erase(shieldPickUpList.begin() + i);
			}
		}

		for (int i = 0; i < scoreOrbList.size(); i++)
		{
			if (!SAT2D(&player.getPolygonN(), &scoreOrbList.at(i)->getPolygonN()) && player.getJumpState() == false)
			{
				scoreOrbList.erase(scoreOrbList.begin() + i);
				OrbsPickedUp++;
				score++;
				
				if (OrbsPickedUp == numberOfScoreOrbs)
				{
					PlaySound("complete.wav", NULL, SND_ASYNC);
				}
				else 
				{
					PlaySound("off.wav", NULL, SND_ASYNC);
				}
			}
		}

		mainHUD.update(deltaT, prevDeltaT, inputState, score);

		for (int i = 0; i < enemyList.size(); i++)
		{
			int collideAllTest = 0;
			for each (BlackHole* b in blackHoleList)
			{

				if (!SAT2D(&enemyList.at(i)->getPolygonN(), &b->getPolygonN()))
				{
					if (enemyList.at(i)->getSpeed() > 4)
					{
						enemyList.at(i)->setSpeed(enemyList.at(i)->getSpeed() - 0.5);
					}
				}
				else {
					collideAllTest++;
				}
			}
			if (collideAllTest == blackHoleList.size()) {
				enemyList.at(i)->setSpeed(enemyList.at(i)->getDefaultSpeed());
			}
		}

		for (int i = 0; i < enemyList.size(); i++) {

			if ((!SAT2D(&player.getPolygonN(), &enemyList.at(i)->getPolygonN())) && player.checkShouldColide() == false)
			{
				if (player.getShieldState() == true) {
					enemyList.at(i)->setSpeed(0);
				}

				if (player.getShieldState() == false) {
					player.setDamageState();
					mainHUD.decreaseHealthTexture();
					if (score > 0)
					{
						score--;
					}
					enemyList.erase(enemyList.begin() + i);
				}
			}
		}

		if (player.getHealthCount() <= 0)
		{
			player.setDeadState(true);
		}

		if (player.getDeadState() == true)
		{
			levelLost = true;
		}

		if (OrbsPickedUp == numberOfScoreOrbs - 3)
		{
			mainHUD.setPopUpMessage("3 orb left!");
		}

		if (OrbsPickedUp == numberOfScoreOrbs - 2)
		{
			mainHUD.setPopUpMessage("2 orb left!");
		}

		if (OrbsPickedUp == numberOfScoreOrbs - 1)
		{
			mainHUD.setPopUpMessage("1 orb left!");
		}

		if (OrbsPickedUp == numberOfScoreOrbs)
		{
			//score = (score * 10) / currentGameTime;
			levelWon = true;
		}
	}
}

void GameActivity::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	glRotated(-camRot, 0.0, 0.0, 1);
	glTranslated(-camX, -camY, 0.0);
	//renderDebugGrid(-100.0, -120.0, 400.0, 400.0, 30, 30);

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			drawSquare(i, j, map[i][j]);
		}
	}

	for each (BlackHole* b in blackHoleList)
	{
		b->render();
	}

	for each (JumpPad* j in jumpPadList)
	{
		j->render();
	}

	for each (ShieldPickUp* s in shieldPickUpList)
	{
		s->render();
	}

	for each (ScoreOrb* s in scoreOrbList)
	{
		s->render();
	}

	for each (Enemy* e in enemyList)
	{
		e->render();
	}
	player.render();
	mainHUD.render();

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
		app->setCurrentActivity(app->endScreen);
	}
	else if (key == VK_RETURN) {

		app->setCurrentActivity(app->pauseScreen);
	}
	else if (key == VK_HOME) {
		levelStart = false;
		mainHUD.setMainMessage("");
	}
	else if (key == VK_SPACE) {
		player.boostToggleOn();
	}
	else if (key == VK_END) {
		rotateCamera = !rotateCamera;
	}
}

void GameActivity::onKeyUp(int key)									
{
	if (key == VK_SPACE) {
		player.boostToggleOff();
	}
}

void GameActivity::renderDebugGrid(float left, float bottom, float width, float height, int hSegments, int vSegments)
{
	glColor3f(0.4f, 0.4f, 1.0f);
	glBegin(GL_LINES);

	float dx = width / hSegments;
	float x = left;
	for (int i = 0; i <= hSegments; i++)
	{
		glVertex2f(x, bottom);
		glVertex2f(x, bottom + height);
		x += dx;
	}
	
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

void GameActivity::matrixFiller(char *map, int w, int h)
{
	int i, j;

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			/*
			if (j == 0 || j == w) {
				map[i][j] = 1;
			}
			else if (i == 0 || j == h){
				map[i][j] = 2;
			}
			else {
				map[i][j] = 0;
			}
			*/
		}
	}
}


void GameActivity::drawSquare(double posX, double posY, GLuint mapId) {
	glPushMatrix();

	glTranslated(posX * 8 - (10 * 8), posY * 8 - (10 * 8), 0.0);
	
	if (mapId == 1){
		glBindTexture(GL_TEXTURE_2D,  wallLeftId);
	}
	else if (mapId == 2){
		glBindTexture(GL_TEXTURE_2D, wallTopId);
	}
	else if (mapId == 3){
		glBindTexture(GL_TEXTURE_2D, wallRightId);
	}
	else if (mapId == 4){
		glBindTexture(GL_TEXTURE_2D, wallBotId);
	}
	else if (mapId == 5){
		glBindTexture(GL_TEXTURE_2D, cornerWall);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, spaceTextureID);
	}
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0, 0);
		glVertex2f(-4, -4);

		glTexCoord2f(1.0, 0);
		glVertex2f(4, -4);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(-4, 4);

		glTexCoord2f(1.0, 0);
		glVertex2f(4, -4);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(4, 4);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(-4, 4);
	glEnd();

	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}