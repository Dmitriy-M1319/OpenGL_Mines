#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
#include "lib/mine.h"
#define MINES_COUNT 20

GLint width = 600;
GLint height = 600;

game *new_game;
void DrawEmptyCell(int dx, int dy, int dpixels);
void DrawEmptyOpenedCell(int dx, int dy, int dpixels);
void DrawOpenedMine(int dx, int dy, int dpixels);
void DrawFlag(int dx, int dy, int dpixels);



void DrawGameField()
{
    int dpixels = width / GAME_FIELD_SIZE;
    int dx = 0;
    int dy = 0;
    for(int i = 0; i < GAME_FIELD_SIZE; i++)
    {
        for(int j = 0; j < GAME_FIELD_SIZE; j++)
        {
            int element = new_game->field[i][j].state;

            switch(element)
            {
                case EMPTY_CLOSED:
                    DrawEmptyCell(dx, dy, dpixels);
                    break;
                case EMPTY_OPENED:
                    DrawEmptyOpenedCell(dx, dy, dpixels);
                    break;
                case MINE_CLOSED:
                    DrawEmptyCell(dx, dy, dpixels);
                    break;
                case MINE_OPENED:
                    DrawOpenedMine(dx, dy, dpixels);
                    break;
            }

            if(new_game->field[i][j].flag) DrawFlag(dx, dy, dpixels);
            
            dx += dpixels;

        }
        dx = 0;
        dy += dpixels;
    }
}
void DrawEmptyCell(int dx, int dy, int dpixels)
{
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
        glVertex2f(dx, dy);
        glVertex2f(dx, dy + dpixels);
        glVertex2f(dx + dpixels, dy + dpixels);
        glVertex2f(dx + dpixels, dy);
    glEnd();

    glColor3f(0, 0.5f, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(dx, dy);
        glVertex2f(dx, dy + dpixels);
        glVertex2f(dx + dpixels, dy + dpixels);
        glVertex2f(dx + dpixels, dy);
    glEnd();

}
void DrawEmptyOpenedCell(int dx, int dy, int dpixels)
{
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
        glVertex2f(dx, dy);
        glVertex2f(dx, dy + dpixels);
        glVertex2f(dx + dpixels, dy + dpixels);
        glVertex2f(dx + dpixels, dy);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(dx, dy);
        glVertex2f(dx, dy + dpixels);
        glVertex2f(dx + dpixels, dy + dpixels);
        glVertex2f(dx + dpixels, dy);
    glEnd();
}

void DrawOpenedMine(int dx, int dy, int dpixels)
{
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
        glVertex2f(dx, dy);
        glVertex2f(dx, dy + dpixels);
        glVertex2f(dx + dpixels, dy + dpixels);
        glVertex2f(dx + dpixels, dy);
    glEnd();

    int d = dpixels / 4;
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
        glVertex2f(dx + d, dy + d);
        glVertex2f(dx + d, dy + 3 * d);
        glVertex2f(dx + 3 * d, dy + 3 * d);
        glVertex2f(dx + 3 * d, dy + d);
    glEnd();
}

void DrawFlag(int dx, int dy, int dpixels)
{
    glColor3ub(190, 190, 190);
    glBegin(GL_QUADS);
        glVertex2f(dx, dy);
        glVertex2f(dx, dy + dpixels);
        glVertex2f(dx + dpixels, dy + dpixels);
        glVertex2f(dx + dpixels, dy);
    glEnd();

    int d = dpixels / 4;
    glColor3ub(0, 255, 255);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(dx + d, dy + 2 * d);
        glVertex2f(dx + 3 * d, dy + 3 * d);
        glVertex2f(dx + 3 * d, dy + 2 * d);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(dx + 3 * d, dy + 3 * d);
        glVertex2f(dx + 3 * d, dy);
    glEnd();

}
void Display(void)
{
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    DrawGameField();
    glFinish();
}

void Reshape(GLint w, GLint h)
{
    width = w;
    height = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Mouse(int button, int state, int x, int y)
{
    int dx, dy;
    int dpixels = width / GAME_FIELD_SIZE;
    int ostx = x % dpixels;
    if(ostx > 0)
    {
        dx = x / dpixels + 1;
    }
    else 
    {
        dx = x / dpixels + 1;
    }
    int osty = y % dpixels;
    if(osty > 0)
    {
        dy = (height - y) / dpixels + 1;
    }
    else 
    {
        dy = (height - y) / dpixels + 1;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int res = push_cell(new_game, dy - 1, dx - 1);
        if(res)
        {
            end_game(new_game);
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        push_flag(new_game, dy - 1, dx - 1);
    }
    glutPostRedisplay();
}

int main(int argc,char *argv[])
{
    srand(time(NULL));
    new_game = (game *)malloc(sizeof(game));
    new_game->mines_count = MINES_COUNT;
    new_game->flags_count = MINES_COUNT;
    initializeRandomGame(new_game);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Mines");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse);

    glutMainLoop();
    free(new_game);
    return 0;
}
