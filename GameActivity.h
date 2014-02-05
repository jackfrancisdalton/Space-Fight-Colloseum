//
// The structure of the Graphics 1 OpenGL template is explained in README.txt
//

// Ensure that this file can only be included once
#pragma once

#include "Activity.h"



// GAME ACTIVITY
// Renders a grid with a smiley face character.
// WASD keys move the smiley face
// ARROW keys move the camera/viewpoint


class GameActivity : public Activity
{
private:
	// GAME activity variables go here

	// Camera position
	double camX, camY;

	// Player position
	GLuint playerTextureID, shieldTextureID, shieldHitTextureID, spikeBallTextureID, healthIconTextureID;
	double playerX, playerY, rotateZ, attackZ, acceleration;
	double powerORBRotate, powerORBTranslateY, powerORBSize;
	double jumpStage;
	double maxSpeed;
	double shieldTime, shieldScale;
	bool shieldOn, powerORBOn, boostOn;
	bool jump, falling;

public:
	GameActivity(OpenGLApplication *app);

	/*
	*
	* GAME activity methods
	* You should put your game code in the implementations of these methods
	* See GameActivity.cpp
	*
	*/
	virtual void initialise();											// Called on application start up
	virtual void shutdown();											// Called on application shut down

	virtual void onSwitchIn();											// Activity switch in; called when the activity changes and this one switches in
	virtual void onReshape(int width, int height);						// called when the window is resized
	virtual void update(double deltaT, double prevDeltaT);				// Update the application; if the current frame is frame number F, then the previous frame is F-1 and the one before that is F-2
																		// deltaT is the time elapsed from frame F-1 to frame F, prevDeltaT is the time elapsed from F-2 to F-1
	virtual void render();												// Render function


	virtual void onMouseDown(int button, int mouseX, int mouseY);		// Called when mouse button pressed
	virtual void onMouseUp(int button, int mouseX, int mouseY);			// Called when mouse button released
	virtual void onMouseMove(int mouseX, int mouseY);					// Called when mouse moved
	virtual void onKeyDown(int key);									// Called when key pressed
	virtual void onKeyUp(int key);										// Called when key released


	void chooseWizardCharacter();
	void chooseWarriorCharacter();


	// Drawing a grid in the background; useful for debugging
	void renderDebugGrid(float left, float bottom, float width, float height, int hSegments, int vSegments);
};