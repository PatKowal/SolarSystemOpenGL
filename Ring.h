#pragma once
#include "TexturedObject.h"

class Ring :
    public TexturedObject
{
private:
    float innerRadius;
    float outerRadius;

public:
    Ring(float innerRadius, float outerRadius, const std::string& texPath);
    void draw() override;
};

