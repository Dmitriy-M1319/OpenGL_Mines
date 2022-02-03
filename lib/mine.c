#include <stdlib.h>
#include "mine.h"


void setNeighbours(game *gameptr, int x, int y)
{
    for(int dy = -1; dy < 2; dy++)
    {
        for(int dx = -1; dx < 2; dx++)
        {
                if((x + dx >= 0) && (x + dx < GAME_FIELD_SIZE) && (y + dy >= 0) && (y + dy < GAME_FIELD_SIZE))
                {
                    int element = gameptr->neighbourCounts[x + dx][y + dy];
                    element++;
                    gameptr->neighbourCounts[x + dx][y + dy]  = element;
                }
        }
    }
}
void initializeRandomGame(game *gameptr)
{
    int count = gameptr->mines_count;
    while(count != 0)
    {
        int row = rand() % GAME_FIELD_SIZE;
        int col = rand() % GAME_FIELD_SIZE;
        if(!gameptr->field[row][col].state)
        {
            gameptr->field[row][col].state = MINE_CLOSED;
            setNeighbours(gameptr, row, col);
            count--;
        }
        
    }
#ifdef DEBUG
#include <stdio.h>
    for(int i = 0; i < GAME_FIELD_SIZE; i++) 
    {
        for(int j = 0; j < GAME_FIELD_SIZE; j++)
        {
            if(gameptr->field[j][i].state == MINE_CLOSED) {
                printf("8 ");
            } else {
                printf("%d ", gameptr->neighbourCounts[j][i]);
            }
        }
        printf("\n");
    }
#endif
}

void OpenCell(game *gameptr, int x, int y)
{
    if((x < 0) || (x >= GAME_FIELD_SIZE) || (y < 0) || (y >= GAME_FIELD_SIZE)) return;
    if(gameptr->field[x][y].state == EMPTY_OPENED) return;
    
    gameptr->field[x][y].state = EMPTY_OPENED;
    if(!gameptr->neighbourCounts[x][y])
    {
        for(int dy = -1; dy < 2; dy++)
        {
            for(int dx = -1; dx < 2; dx++)
            {
                OpenCell(gameptr, x + dx, y + dy);
            }
        }
    }
}

int push_cell(game *gameptr, int x, int y)
{
    int result = 0;
    cell *c = &gameptr->field[x][y];
    if(c->flag) return 0;
    switch(c->state)
    {
        case EMPTY_CLOSED:
            OpenCell(gameptr, x, y); 
            break;
        case MINE_CLOSED:
            c->state = MINE_OPENED;
            result = 1;
            break;
    }
    return result;
}

void push_flag(game *gameptr, int x, int y)
{
    cell *c = &gameptr->field[x][y];
    if(c->flag)
    {
        if(gameptr->flags_count == MINES_COUNT) return;
        c->flag = 0;
        gameptr->flags_count++;
    }
    else
    {
        if(gameptr->flags_count == 0) return;
        c->flag = 1;
        gameptr->flags_count--;
    }
}

void end_game(game *gameptr)
{
    for(int i = 0; i < GAME_FIELD_SIZE; i++)
    {
        for(int j = 0; j < GAME_FIELD_SIZE; j++)
        {
            if(gameptr->field[i][j].state == MINE_CLOSED)
            {
                gameptr->field[i][j].state = MINE_OPENED;
            }
        }

    }
}
