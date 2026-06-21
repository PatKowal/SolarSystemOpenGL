#include "Ring.h"

Ring::Ring(float innerRadius, float outerRadius, const std::string& texPath)
	: innerRadius(innerRadius), outerRadius(outerRadius)
{
	loadTexture(texPath);
}

void Ring::draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->getTextureID());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);

    GLfloat matAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matSpecular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat matShininess = 10.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    const int segments = 128;
    const float PI2 = 2.0f * 3.14159265f;

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments; i++)
    {
        float angle = (float)i / segments * PI2;
        float cosA = cosf(angle);
        float sinA = sinf(angle);
        float v = (float)i / segments;

        glNormal3f(0.0f, 0.0f, 1.0f);

        glTexCoord2f(0.0f, v);
        glVertex3f(innerRadius * cosA, innerRadius * sinA, 0.0f);

        glTexCoord2f(1.0f, v);
        glVertex3f(outerRadius * cosA, outerRadius * sinA, 0.0f);
    }
    glEnd();

    glPopMatrix();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}
