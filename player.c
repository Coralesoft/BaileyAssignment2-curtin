#include "game.h"

/* Initialize player with starting coordinates and cell content */
void initializePlayer(Player *player, int startX, int startY, char startCell)
{
    /* Set the player's x and y coordinates and the type of cell they're on */
    player->x = startX;
    player->y = startY;
    player->originalCell = startCell;
}

/* Update player's position on the map */
void updatePosition(char **map, Player *player, int newRow, int newCol)
{
    /* Restore the cell content where the player was previously */
    map[player->y][player->x] = player->originalCell;

    /* Store the content of the cell the player is moving to */
    player->originalCell = map[newRow][newCol];

    /* Update the player's x and y coordinates */
    player->y = newRow;
    player->x = newCol;

    /* Place the player symbol at the new position */
    map[player->y][player->x] = PLAYER;
}

/* Handle player movements based on user input */
void playerMovement(char **map, Player *player, char input, int map_row, int map_col)
{
    /* Variable to store the content of the cell the player is moving to */
    int nextCell;

    /* Variables to hold the coordinates for the player's next move */
    int newRow = player->y;
    int newCol = player->x;

    /* Switch case to handle different movement commands */
    switch (input)
    {
        /* Handle 'w' for moving up */
        case 'w':
            newRow = player->y - 1;
            /* Check if moving up is within the map boundary */
            if (newRow >= 0)
            {
                nextCell = map[newRow][newCol];
                /* Check if the cell is one that the player can move to */
                if (nextCell == EMPTY || nextCell == ROAD || nextCell == GOAL)
                {
                    updatePosition(map, player, newRow, newCol);
                }
            }
            break;

        /* Handle 's' for moving down */
        case 's':
            newRow = player->y + 1;
            /* Check if moving down is within the map boundary */
            if (newRow < map_row)
            {
                nextCell = map[newRow][newCol];
                /* Check if the cell is one that the player can move to */
                if (nextCell == EMPTY || nextCell == ROAD || nextCell == GOAL)
                {
                    updatePosition(map, player, newRow, newCol);
                }
            }
            break;

        /* Handle 'a' for moving left */
        case 'a':
            newCol = player->x - 1;
            /* Check if moving left is within the map boundary */
            if (newCol >= 0)
            {
                nextCell = map[newRow][newCol];
                /* Check if the cell is one that the player can move to */
                if (nextCell == EMPTY || nextCell == ROAD || nextCell == GOAL)
                {
                    updatePosition(map, player, newRow, newCol);
                }
            }
            break;

        /* Handle 'd' for moving right */
        case 'd':
            newCol = player->x + 1;
            /* Check if moving right is within the map boundary */
            if (newCol < map_col)
            {
                nextCell = map[newRow][newCol];
                /* Check if the cell is one that the player can move to */
                if (nextCell == EMPTY || nextCell == ROAD || nextCell == GOAL)
                {
                    updatePosition(map, player, newRow, newCol);
                }
            }
            break;

        /* Default case to handle any other character input */
        default:
            /* Handle invalid input, if needed */
            break;
    }
}

/* Set player position on the map grid */
void setPlayerOnMap(Player* player, Map* map)
{
    /* Set the player's symbol at their current x, y coordinates on the map */
    map->grid[player->y][player->x] = PLAYER;
}
