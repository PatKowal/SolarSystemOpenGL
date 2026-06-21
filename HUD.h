#pragma once
#include <GL/glut.h>
#include  <string>
#include  <vector>

class HUD
{
private:
	std::vector<std::string> planetNames;

public:
	HUD();
	
	void draw(int trackedPlanetIndex, float scale, bool isPaused);
};

