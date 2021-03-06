#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "Enemy.h"
#include <random>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)

Enemy::Enemy(){}

double Enemy::getEnemyRot() {
	return rot;
}

double Enemy::getEnemyX() {
	return posX;
}

double Enemy::getEnemyY() {
	return posY;
}

void Enemy::setSpeed(double s) {
	speed = s;
}

polygon Enemy::getPolygonN()
{
	return enemyPolyN;
}

int Enemy::getId()
{
	return id;
}

double Enemy::getDefaultSpeed()
{
	return defaultSpeed;
}

bool Enemy::getDeadState()
{
	return deadState;
}

void Enemy::setDeadState()
{
	deadState = true;
}

double Enemy::getSpeed()
{
	return speed;
}

void Enemy::shutdown()
{
	glDeleteTextures(1, &enemyTextureId);
}

void Enemy::onSwitchIn()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}


void Enemy::BlackHoleCollisionOn()
{
	blackHoleCollsion = true;
}

void Enemy::BlackHoleCollisionOff()
{
	blackHoleCollsion = false;
}