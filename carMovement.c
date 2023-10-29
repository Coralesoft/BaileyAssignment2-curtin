#include <stdio.h>
#include <stdlib.h>
#include "carMovement.h"
#include "game.h"

/* Function to check if the car can move in a given direction */
int canMove(char **map, int x, int y, char dir, int rows, int cols) {
    switch (dir) {
        case '>':
            /* Check if car can move right */
            return (x < cols - 1 && map[y][x + 1] == ROAD);
        case '^':
            /* Check if car can move up */
            return (y > 0 && map[y - 1][x] == ROAD);
        case 'v':
            /* Check if car can move down */
            return (y < rows - 1 && map[y + 1][x] == ROAD);
        case '<':
            /* Check if car can move left */
            return (x > 0 && map[y][x - 1] == ROAD);
        default:
            /* Return 0 for unknown directions */
            return 0;
    }
}

void carMovement(char **map, Car *car, int rows, int cols)
{
    /* Array of alternative directions */
    char alternativeDirs[] = {'^', '>','v', '<'};
    int i;
    int x = car->x;
    int y = car->y;
    char currentDir = car->currentDir;

    /* Check if car can move in its current direction */
    if (canMove(map, x, y, currentDir, rows, cols)) {
        map[y][x] = ROAD;  /* Clear the current position */

        /* Update car position based on its current direction */
        switch (currentDir) {
            case '>':
                map[y][x + 1] = '>';
                car->x = x + 1;
                break;
            case '^':
                map[y - 1][x] = '^';
                car->y = y - 1;
                break;
            case 'v':
                map[y + 1][x] = 'v';
                car->y = y + 1;
                break;
            case '<':
                map[y][x - 1] = '<';
                car->x = x - 1;
                break;
            default:
                /* Handle other conditions */
                break;
        }
    } else {
        /* If car cannot move in its current direction, try alternative directions */
        for (i = 0; i < sizeof(alternativeDirs) / sizeof(char); ++i) {
            if (canMove(map, car->x, car->y, alternativeDirs[i], rows, cols)) {
                /* Update the car's current direction */
                car->currentDir = alternativeDirs[i];

                map[car->y][car->x] = ROAD;  /* Clear the current position before moving */

                /* Move car in the new direction */
                switch (alternativeDirs[i]) {
                    case '>':
                        map[car->y][car->x + 1] = '>';
                        car->x = car->x + 1;
                        break;
                    case '^':
                        map[car->y - 1][car->x] = '^';
                        car->y = car->y - 1;
                        break;
                    case 'v':
                        map[car->y + 1][car->x] = 'v';
                        car->y = car->y + 1;
                        break;
                    case '<':
                        map[car->y][car->x - 1] = '<';
                        car->x = car->x - 1;
                        break;
                    default:
                        /* Handle other conditions */
                        break;
                }

                return; /* Exit the function after making a move */
            }
        }
    }
}
