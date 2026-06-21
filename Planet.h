#pragma once
#include "TexturedObject.h"
#include "Ring.h"
#include <vector>
#include <cmath>
class Planet :
    public TexturedObject
{
private:
    float orbitRadius;
    float orbitSpeed;
    float rotationSpeed;
    float size;
    float orbitAngle;
    float rotationAngle;
    float tilt;

    std::vector<Planet*> moons;
    Ring* ring;

    bool showOrbit = true;

public:
    Planet(float orbitRadius, float orbitSpeed, float rotationSpeed, float size, float orbitAngle, float rotationAngle, float tilt, const std::string& texPath);
    ~Planet();

    void draw() override;
    void update(float time);
    void drawOrbit();

    void addMoon(Planet* moon);
    void setRing(Ring* ring);

    void setOrbitSpeed(float speed);
    void setOrbitRadius(float radius);

    void setShowOrbit(bool value) { showOrbit = value; }
    bool getShowOrbit() const { return showOrbit; }

    float getWorldX() const { return orbitRadius * cosf(orbitAngle * M_PI / 180.0f); }
    float getWorldZ() const { return -orbitRadius * sinf(orbitAngle * M_PI / 180.0f); }
    float getSize() const { return size; }
    float getRotationAngle() const { return rotationAngle; }
    float getRotationSpeed() const { return rotationSpeed; }
    float getOrbitAngle() const { return orbitAngle; }
};

