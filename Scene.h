#pragma once
#include "Sun.h"
#include <vector>
#include "Planet.h"
#include "Camera.h"
#include "HUD.h"

class Scene
{
private:
	Sun* sun;
	std::vector<Planet*> planets;
	float time;
	bool paused;

	bool light0Enabled;
	bool light1Enabled;
	float timeScale;
	bool orbitsVisible;

	int  trackedPlanetIndex;

	HUD hud;
	Camera camera;
public:
	Scene();
	~Scene();

	void init();
	void setupObjects();
	void update(float time);
	void setupLighting();
	void render();

	void handleKeyboard(unsigned char key, int x, int y);
	void handleSpecialKey(int key, int x, int y);
	void handleMenu(int option);
};

