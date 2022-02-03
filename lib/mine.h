#ifndef MINE_H
#define MINE_H

#define GAME_FIELD_SIZE 10
#define MINES_COUNT 10
enum cell_state {
    EMPTY_CLOSED = 0,
    EMPTY_OPENED = 1,
    MINE_CLOSED = 2,
    MINE_OPENED = 3
};

typedef struct {
    /* Состояние клетки поля */
    enum cell_state state;
    /* Находится под флагом или нет */
    int flag;
    /*Хранилище последнего состояния до помечения флагом */
    enum cell_state old_state;
} cell;

typedef struct {
    cell field[GAME_FIELD_SIZE][GAME_FIELD_SIZE];
    int neighbourCounts[GAME_FIELD_SIZE][GAME_FIELD_SIZE];
    int mines_count;
    int flags_count;
    int is_end_game;
} game;

void setNeigbours(game *gameptr, int x, int y);
void initializeRandomGame(game *gameptr);
int push_cell(game *gameptr, int x, int y);
void push_flag(game *gameptr, int x, int y);
void end_game(game *gameptr);

#endif
