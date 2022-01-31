#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "lib/mine.h"
#include "lib/drawning.h"


GLint width = 600;
GLint height = 600;
game *new_game;
void DrawGameField()
{
    glLoadIdentity();
    glScalef(2.0 / GAME_FIELD_SIZE, 2.0 / GAME_FIELD_SIZE, 0);
    glTranslatef(-GAME_FIELD_SIZE / 2, -GAME_FIELD_SIZE / 2, 0);

    for(int i = 0; i < GAME_FIELD_SIZE; i++)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        for(int j = 0; j < GAME_FIELD_SIZE; j++)
        {
            glPushMatrix();
            glTranslatef(j, 0, 0);
            int element = new_game->field[i][j].state;
            switch(element)
            {
                case EMPTY_CLOSED:
                    DrawEmptyCell();
                    break;
                case EMPTY_OPENED:
                    DrawEmptyOpenedCell();
                    break;
                case MINE_CLOSED:
                    DrawEmptyCell();
                    break;
                case MINE_OPENED:
                    DrawOpenedMine();
                    break;
            }

            if(new_game->field[i][j].flag)
                DrawFlag();
            glPopMatrix();
        }
        glPopMatrix();
    }
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
    glOrtho(0, w, 0, h, -1.0, -1.0);

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
