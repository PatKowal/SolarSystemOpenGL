#include "Sun.h"

Sun::Sun(float size, const std::string& texPath) 
{
	this->size = size;
	this->rotationAngle = 0.0f;
	this->rotationSpeed = 10.0f;

	loadTexture(texPath);
}

void Sun::update(float time) 
{
	rotationAngle += rotationSpeed * time;
	if (rotationAngle > 360.0f) rotationAngle -= 360.0f;
}

void Sun::draw()
{
	glPushMatrix();
	
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->getTextureID());

    glDisable(GL_LIGHTING);

    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, size, 64, 64);
    gluDeleteQuadric(quad);

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
