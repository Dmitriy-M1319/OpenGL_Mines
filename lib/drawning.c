#include <GL/gl.h>
#include "drawning.h"

void DrawEmptyCell()
{
    glBegin(GL_POLYGON);
        glColor3f(0, 0.7f, 0); glVertex2f(0.0, 0.0);
        glColor3f(0, 0.8f, 0); glVertex2f(0.0, 1.0);
        glColor3f(0, 0.7f, 0); glVertex2f(1.0, 1.0);
        glColor3f(0, 0.6f, 0); glVertex2f(1.0, 0.0);
    glEnd();
}
void DrawEmptyOpenedCell()
{
    glBegin(GL_POLYGON);
        glColor3f(0.7, 0.7, 0.7); glVertex2f(0, 0);
        glColor3f(0.8, 0.8, 0.8); glVertex2f(0, 1);
        glColor3f(0.7, 0.7, 0.7); glVertex2f(1, 1);
        glColor3f(0.6, 0.6, 0.6); glVertex2f(1, 0);
    glEnd();
}

void DrawOpenedMine()
{
    glBegin(GL_POLYGON);
        glColor3f(0.7, 0, 0); glVertex2f(0, 0);
        glColor3f(0.8, 0, 0); glVertex2f(0, 1);
        glColor3f(0.7, 0, 0); glVertex2f(1, 1);
        glColor3f(0.6, 0, 0); glVertex2f(1, 0);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(0, 0, 0); glVertex2f(0.2, 0.2);
        glColor3f(0, 0, 0); glVertex2f(0.2, 0.8);
        glColor3f(0, 0, 0); glVertex2f(0.8, 0.8);
        glColor3f(0, 0, 0); glVertex2f(0.8, 0.2);
    glEnd();
}

void DrawFlag()
{
    glBegin(GL_POLYGON);
        glColor3f(0.7, 0.7, 0.7); glVertex2f(0, 0);
        glColor3f(0.8, 0.8, 0.8); glVertex2f(0, 1.0);
        glColor3f(0.7, 0.7, 0.7); glVertex2f(1.0, 1.0);
        glColor3f(0.6, 0.6, 0.6); glVertex2f(1.0, 0);
    glEnd();

    glColor3f(0, 1, 1);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2, 0.6);
        glVertex2f(0.6, 0.8);
        glVertex2f(0.6, 0.6);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(0.6, 0.8);
        glVertex2f(0.6, 0);
    glEnd();
}

void DrawFigure(int value)
{
    if(value == 0) return;
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        if(value != 2) {
            glVertex2f(0.8, 0.5); glVertex2f(0.8, 0.2);
        }
        if(value != 5 &&  value != 6) {
            glVertex2f(0.8, 0.8); glVertex2f(0.8, 0.5);
        }
        if (value != 1 && value != 4) {
            glVertex2f(0.2, 0.8); glVertex2f(0.8, 0.8);
        }
        if (value != 1 && value != 7) {
            glVertex2f(0.2, 0.5); glVertex2f(0.8, 0.5);
        }
        if (value != 1 && value != 7 && value != 4) {
            glVertex2f(0.2, 0.2); glVertex2f(0.8, 0.2);
        }
        if (value != 1 && value != 2 && value != 3) {
            glVertex2f(0.2, 0.8); glVertex2f(0.2, 0.5);
        }
        if (value == 2 || value == 6 || value == 8 || value == 9) {
            glVertex2f(0.2, 0.5); glVertex2f(0.2, 0.2);
        }
    glEnd();
}
