#include "HUD.h"

HUD::HUD()
{
    planetNames = {
        "Merkury", "Wenus", "Ziemia", "Mars",
        "Jowisz", "Saturn", "Uran", "Neptun"
    };
}

void HUD::draw(int trackedPlanetIndex, float scale, bool isPaused)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (trackedPlanetIndex != -1)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2i(20, h - 30);
        std::string label = "Sledzona planeta: " + planetNames[trackedPlanetIndex];
        for (char c : label)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

        glColor3f(0.7f, 0.7f, 0.7f);
        glRasterPos2i(20, h - 55);
        std::string hint = "[0] Przestan sledzic  [Strzalki] Obrot";
        for (char c : hint)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    else {
        glColor3f(0.2f, 0.8f, 1.0f);
        glRasterPos2i(20, h - 30);
        std::string label = "Uklad Sloneczny";
        for (char c : label)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

        glColor3f(0.7f, 0.7f, 0.7f);
        glRasterPos2i(20, h - 55);
        std::string hint = "[1-8] Wybor planety  [Strzałki] Obrot sceny  [Z/X] Zoom  [O] Widok orbit [P] Pauza";
        for (char c : hint) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }

    std::string speedText = "Predkosc: " + std::to_string(scale).substr(0, 4) + "x";
    if (isPaused) {
        speedText += " [PAUZA]";
        glColor3f(1.0f, 0.3f, 0.3f);
    }
    else {
        glColor3f(0.3f, 1.0f, 0.3f);
    }

    glRasterPos2i(w - 180, h - 30);
    for (char c : speedText) {
        glutBitmapCharacter((void*)GLUT_BITMAP_HELVETICA_12, c);
    }

    glColor3f(1.0f, 1.0f, 1.0f);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}
