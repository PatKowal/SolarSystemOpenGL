#include "Planet.h"

Planet::Planet(float orbitRadius, float orbitSpeed, float rotationSpeed, float size, float orbitAngle, float rotationAngle, float tilt, const std::string& texPath)
	: orbitRadius(orbitRadius), orbitSpeed(orbitSpeed), rotationSpeed(rotationSpeed), size(size), orbitAngle(orbitAngle), rotationAngle(rotationAngle), tilt(tilt), ring(nullptr)
{
	loadTexture(texPath);
}

Planet::~Planet()
{
    delete ring;
    for (auto* moon : moons) {
        delete moon;
    }
}

void Planet::draw()
{
    glPushMatrix();

    if (showOrbit)
        drawOrbit();

    glRotatef(orbitAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(orbitRadius, 0.0f, 0.0f);

    glRotatef(tilt, 0.0f, 0.0f, 1.0f);

    if (ring != nullptr)
    {
        glPushMatrix();
        ring->draw();
        glPopMatrix();
    }

    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->getTextureID());

    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, size, 48, 48);
    gluDeleteQuadric(quad);

    glDisable(GL_TEXTURE_2D);

    for (auto* moon : moons) {
        moon->draw();
    }

    glPopMatrix();
}

void Planet::update(float time)
{
    orbitAngle += orbitSpeed * time;
    rotationAngle += rotationSpeed * time;

    for (auto* moon : moons) {
        moon->update(time);
    }
}

void Planet::drawOrbit()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glColor4f(1.0f, 1.0f, 1.0f, 0.15f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int segments = 128;
    const float PI2 = 2.0f * 3.14159265f;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        float angle = (float)i / segments * PI2;
        glVertex3f(orbitRadius * cosf(angle), 0.0f, orbitRadius * sinf(angle));
    }
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void Planet::addMoon(Planet* moon)
{
    moons.push_back(moon);
}

void Planet::setRing(Ring* ring)
{
    delete this->ring;
    this->ring = ring;
}

void Planet::setOrbitSpeed(float speed)
{
    orbitSpeed = speed;
}

void Planet::setOrbitRadius(float radius)
{
    orbitRadius = radius;
}




