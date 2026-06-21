#pragma once
#include <GL/glut.h>
#include "Planet.h"
#include <cmath>

class Camera
{
private:
	float angleX;
	float angleY;
	float zoom;

	float trackAngleX;
	float trackAngleY;
	float trackDistance;
public:
	Camera();

	void applyView(int trackedPlanetIndex, Planet* trackedPlanet);

	void handleGlobalRotation(int key, float step);
	void handleTrackingRotation(int key, float step);
	void reset();

	float getZoom() const { return zoom; }
	void setZoom(float zoom) { this->zoom = zoom; }
	void setTrackDistance(float distance) { trackDistance = distance; }

	void setViewTop();
	void setViewSide();
	void setViewIso();
};

