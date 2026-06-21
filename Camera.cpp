#include "Camera.h"

Camera::Camera()
	: angleX(20.0f), angleY(0.0f), zoom(-60.0f), trackAngleX(20.0f), trackAngleY(0.0f), trackDistance(5.0f)
{}

void Camera::applyView(int trackedPlanetIndex, Planet* trackedPlanet)
{
    if (trackedPlanetIndex == -1 || trackedPlanet == nullptr)
    {
        glTranslatef(0.0f, 0.0f, zoom);
        glRotatef(angleX, 1.0f, 0.0f, 0.0f);
        glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    }
    else
    {
        float px = trackedPlanet->getWorldX();
        float pz = trackedPlanet->getWorldZ();

        float totalAngleY = (trackedPlanet->getOrbitAngle() + trackAngleY) * M_PI / 180.0f;
        float angleX = trackAngleX * M_PI / 180.0f;

        float camX = px + trackDistance * cosf(angleX) * cosf(totalAngleY);
        float camZ = pz + trackDistance * cosf(angleX) * (-sinf(totalAngleY));
        float camY = trackDistance * sinf(angleX);

        gluLookAt(
            camX, camY, camZ,
            px, 0.0f, pz,
            0.0f, 1.0f, 0.0f
        );
    }
}

void Camera::handleGlobalRotation(int key, float step)
{
    switch (key) {
    case GLUT_KEY_UP: angleX += step; break;
    case GLUT_KEY_DOWN: angleX -= step; break;
    case GLUT_KEY_RIGHT: angleY -= step; break;
    case GLUT_KEY_LEFT: angleY += step; break;
    }
}

void Camera::handleTrackingRotation(int key, float step)
{
    switch (key) {
    case GLUT_KEY_UP: trackAngleX += step; break;
    case GLUT_KEY_DOWN: trackAngleX -= step; break;
    case GLUT_KEY_LEFT: trackAngleY -= step; break;
    case GLUT_KEY_RIGHT: trackAngleY += step; break;
    }

    if (trackAngleX > 85.0f) trackAngleX = 85.0f;
    if (trackAngleX < -85.0f) trackAngleX = -85.0f;
}

void Camera::reset()
{
    angleX = 20.0f;
    angleY = 0.0f;
    zoom = -60.0f;
    trackAngleX = 20.0f;
    trackAngleY = 0.0f;
}

void Camera::setViewTop()
{
    angleX = 90.0f;
    angleY = 0.0f;
    zoom = -80.0f;
    trackAngleX = 20.0f;
    trackAngleY = 0.0f;
}

void Camera::setViewSide()
{
    angleX = 0.0f;
    angleY = 0.0f;
    zoom = -60.0f;
    trackAngleX = 20.0f;
    trackAngleY = 0.0f;
}

void Camera::setViewIso()
{
    angleX = 35.0f;
    angleY = 45.0f;
    zoom = -70.0f;
    trackAngleX = 20.0f;
    trackAngleY = 0.0f;
}


