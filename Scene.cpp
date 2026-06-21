#include "Scene.h"

Scene::Scene()
	: sun(nullptr), time(0.0f), paused(false),
	light0Enabled(true), light1Enabled(true), timeScale(0.5f),
	orbitsVisible(true),trackedPlanetIndex(-1)
{}

Scene::~Scene()
{
	delete sun;
	for (auto* p : planets) {
		delete p;
	}
}

void Scene::init()
{
	glClearColor(0.0f, 0.0f, 0.05f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	setupObjects();
	setupLighting();
}

void Scene::setupObjects()
{
	sun = new Sun(4.0f, "textures/sun.bmp");

	Planet* mercury = new Planet(10.0f, 47.9f, 58.6f, 0.8f, 0.0f, 0.0f, 0.0f, "textures/mercury.bmp");
	Planet* venus = new Planet(16.0f, 35.0f, -24.0f, 1.2f, 40.0f, 0.0f, 177.4f, "textures/venus.bmp");
	Planet* earth = new Planet(23.0f, 29.8f, 36.0f, 1.3f, 80.0f, 0.0f, 23.4f, "textures/earth.bmp");
	Planet* mars = new Planet(31.0f, 24.1f, 35.0f, 0.9f, 130.0f, 0.0f, 25.2f, "textures/mars.bmp");
	Planet* jupiter = new Planet(46.0f, 13.1f, 360.0f, 3.5f, 200.0f, 0.0f, 3.1f, "textures/jupiter.bmp");
	Planet* saturn = new Planet(62.0f, 9.7f, 330.0f, 3.0f, 260.0f, 0.0f, 26.7f, "textures/saturn.bmp");
	Planet* uranus = new Planet(77.0f, 6.8f, 154.0f, 2.0f, 310.0f, 0.0f, 97.8f, "textures/uranus.bmp");
	Planet* neptune = new Planet(90.0f, 5.4f, 149.0f, 1.9f, 350.0f, 0.0f, 28.3f, "textures/neptune.bmp");

	Planet* moon = new Planet(3.2f, 120.0f, 27.0f, 0.4f, 0.0f, 0.0f, 6.7f, "textures/moon.bmp");
	Planet* phobos = new Planet(2.0f, 300.0f, 10.0f, 0.2f, 0.0f, 0.0f, 0.0f, "textures/phobos.bmp");
	Planet* deimos = new Planet(3.0f, 200.0f, 10.0f, 0.15f, 90.0f, 0.0f, 0.0f, "textures/deimos.bmp");

	earth->addMoon(moon);
	mars->addMoon(phobos);
	mars->addMoon(deimos);

	saturn->setRing(new Ring(3.8f, 7.0f, "textures/saturn_ring.bmp"));

	planets.push_back(mercury);
	planets.push_back(venus);
	planets.push_back(earth);
	planets.push_back(mars);
	planets.push_back(jupiter);
	planets.push_back(saturn);
	planets.push_back(uranus);
	planets.push_back(neptune);
}

void Scene::update(float time)
{
	if (paused) return;

	float newTime = time * timeScale;
	time += newTime;

	sun->update(newTime);
	for (auto* p : planets) p->update(newTime);
}

void Scene::setupLighting()
{
	// GL_LIGHT0 - Slonce
	GLfloat light0Pos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light0Diffuse[] = { 1.0f, 0.95f, 0.8f, 1.0f };
	GLfloat light0Specular[] = { 1.0f, 1.0f,  1.0f, 1.0f };
	GLfloat light0Ambient[] = { 0.1f, 0.1f,  0.1f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
	glEnable(GL_LIGHT0);

	// GL_LIGHT1
	GLfloat light1Pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat light1Diffuse[] = { 0.15f, 0.15f, 0.25f, 1.0f };
	GLfloat light1Ambient[] = { 0.05f, 0.05f, 0.1f,  1.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
	glEnable(GL_LIGHT1);
}

void Scene::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Planet* trackedPlanet = (trackedPlanetIndex != -1) ? planets[trackedPlanetIndex] : nullptr;
	camera.applyView(trackedPlanetIndex, trackedPlanet);

	GLfloat light0Pos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

	sun->draw();
	for (auto* p : planets) p->draw();

	hud.draw(trackedPlanetIndex, timeScale, paused);

	glutSwapBuffers();
}

void Scene::handleKeyboard(unsigned char key, int x, int y)
{
	// Wybór planety [1-8], powrót [0]
	if (key >= '1' && key <= '8')
	{
		int index = key - '1';
		if (index < (int)planets.size())
		{
			trackedPlanetIndex = index;

			float distance = planets[index]->getSize() * 4.0f;
			camera.setTrackDistance(distance);
		}
		glutPostRedisplay();
		return;
	}

	if (key == '0')
	{
		trackedPlanetIndex = -1;
		glutPostRedisplay();
		return;
	}

	switch (key) {
	case 'o':
		orbitsVisible = !orbitsVisible;
		for (auto* p : planets)
			p->setShowOrbit(orbitsVisible);
		break;
	case 'p':
		paused = !paused;
		break;

	case '+':
		timeScale = std::min(timeScale + 0.25f, 16.0f);
		break;

	case '-':
		timeScale = std::max(timeScale - 0.25f, 0.25f);
		break;

	case 'r': case 'R':
		camera.reset();
		timeScale = 0.5f;
		break;

	case 'z':
		if (trackedPlanetIndex == -1) camera.setZoom(std::min(camera.getZoom() + 3.0f, -10.0f));
		break;

	case 'x':
		if (trackedPlanetIndex == -1) camera.setZoom(camera.getZoom() - 3.0f);
		break;

	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void Scene::handleSpecialKey(int key, int x, int y)
{
	const float step = 3.0f;
	if (trackedPlanetIndex != -1) {
		camera.handleTrackingRotation(key, step);
	}
	else {
		camera.handleGlobalRotation(key, step);
	}
	glutPostRedisplay();
}

enum MenuOption {
	MENU_VIEW_TOP = 1,
	MENU_VIEW_SIDE,
	MENU_VIEW_ISO,
	MENU_LIGHT0_TOGGLE,
	MENU_LIGHT1_TOGGLE,
	MENU_SPEED_HALF,
	MENU_SPEED_NORMAL,
	MENU_SPEED_DOUBLE,
	MENU_EXIT
};

void Scene::handleMenu(int option)
{
	switch (option)
	{
	case MENU_VIEW_TOP:
		camera.setViewTop();
		trackedPlanetIndex = -1;
		break;

	case MENU_VIEW_SIDE:
		camera.setViewSide();
		trackedPlanetIndex = -1;
		break;

	case MENU_VIEW_ISO:
		camera.setViewIso();
		trackedPlanetIndex = -1;
		break;

	case MENU_LIGHT0_TOGGLE:
		light0Enabled = !light0Enabled;
		light0Enabled ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);
		break;

	case MENU_LIGHT1_TOGGLE:
		light1Enabled = !light1Enabled;
		light1Enabled ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);
		break;
	}
	glutPostRedisplay();
}
