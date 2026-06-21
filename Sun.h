#pragma once
#include "TexturedObject.h"
class Sun :
    public TexturedObject
{
private:
    float size;
    float rotationAngle;
    float rotationSpeed;

public:
    Sun(float size, const std::string& texPath);
    void update(float time);
    void draw() override;
};

