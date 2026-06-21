#include <GL/glut.h>
#include "Scene.h"

static Scene scene;

static int lastTime = 0;

void display()
{
    scene.render();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 0.1, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle()
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    if (deltaTime > 0.1f) deltaTime = 0.1f;

    scene.update(deltaTime);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    scene.handleKeyboard(key, x, y);
}

void specialKey(int key, int x, int y)
{
    scene.handleSpecialKey(key, x, y);
}

void menu(int option)
{
    scene.handleMenu(option);
}

void buildMenu()
{
    // Widok
    int viewMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Widok z gory", 1);
    glutAddMenuEntry("Widok z boku", 2);
    glutAddMenuEntry("Widok izometryczny", 3);

    // Oświetlenie
    int lightMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Przelacz GL_LIGHT0 (Slonce)", 4);
    glutAddMenuEntry("Przelacz GL_LIGHT1 (Ambient)", 5);

    // Menu główne
    glutCreateMenu(menu);
    glutAddSubMenu("Widok", viewMenu);
    glutAddSubMenu("Oswietlenie", lightMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Uklad Sloneczny");

    scene.init();
    lastTime = glutGet(GLUT_ELAPSED_TIME);

    buildMenu();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);

    glutMainLoop();
    return 0;
}