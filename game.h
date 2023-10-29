#ifndef GAME_H
#define GAME_H

#include <stdio.h>

/* Define constants to represent different elements on the map */
#define EMPTY 0
#define ROAD 1
#define CAR 2
#define PLAYER 3
#define GOAL 4

/* Define constants for display characters corresponding to each map element */
#define EMPTY_SYMBOL ' '
#define ROAD_SYMBOL '.'
#define CAR_SYMBOL '>'
#define PLAYER_SYMBOL 'P'
#define GOAL_SYMBOL 'G'

/* Player structure definition */
typedef struct
{
    int x;              /* x-coordinate of the player */
    int y;              /* y-coordinate of the player */
    char originalCell;  /* original content of the cell the player is on */
} Player;

/* Map structure definition */
typedef struct
{
    int rows;           /* Number of rows in the map */
    int cols;           /* Number of columns in the map */
    char **grid;        /* 2D array representing the map grid */
    Player *player;     /* Pointer to the player structure */
} Map;

/* Car structure definition */
typedef struct
{
    int x;              /* x-coordinate of the car */
    int y;              /* y-coordinate of the car */
    char currentDir;    /* Current direction of the car */
} Car;

/* Function prototypes for Player related operations */
void initializePlayer(Player *player, int startX, int startY, char startCell);
void updatePosition(char **map, Player *player, int newRow, int newCol);
void playerMovement(char **map, Player *player, char input, int map_row, int map_col);
void setPlayerOnMap(Player* player, Map* map);

/* Function prototypes for Map related operations */
Map *loadMapFromFile(FILE *file, Player *player, Car *car);
void printMap(const Map* map, const Car* car);
void freeMap(Map* map);

#endif  /* End of the header guard */
