#include <stdio.h>
#include <stdlib.h>
#include "game.h"

/* Function to load the map from a file */
Map* loadMapFromFile(FILE* file, Player *player, Car *car) /* Added Car *car*/
{
    /* Initialize variables and allocate memory for the map */
    Map* map = malloc(sizeof(Map));
    int i, j;
    char cellChar;

    /* Check if memory allocation was successful */
    if (!map)
    {
        fprintf(stderr, "Failed to allocate memory for the map.\n");
        exit(EXIT_FAILURE);
    }

    /* Allocate memory for player within map */
    map->player = malloc(sizeof(Player));

    /* Check if memory allocation for player was successful */
    if (!map->player)
    {
        fprintf(stderr, "Failed to allocate memory for the player within map.\n");
        free(map);
        exit(EXIT_FAILURE);
    }

    /* Read the number of rows and columns from the file */
    fscanf(file, "%d %d", &(map->rows), &(map->cols));
    printf("Read map dimensions: %d x %d\n", map->rows, map->cols);

    /* Allocate memory for the rows in the map grid */
    map->grid = malloc(map->rows * sizeof(int*));

    /* Check if memory allocation for rows was successful */
    if (!map->grid)
    {
        fprintf(stderr, "Failed to allocate memory for the map grid rows.\n");
        free(map);
        exit(EXIT_FAILURE);
    }

    /* Loop to allocate memory and populate the map grid */
    for (i = 0; i < map->rows; i++)
    {
        /* Allocate memory for each row */
        map->grid[i] = malloc(map->cols * sizeof(int));

        /* Check if memory allocation for a row was successful */
        if (!map->grid[i])
        {
            fprintf(stderr, "Failed to allocate memory for row %d of the map grid.\n", i);
            for (j = 0; j < i; j++)
            {
                free(map->grid[j]);
            }
            free(map->grid);
            free(map);
            exit(EXIT_FAILURE);
        }

        /* Populate the map grid by reading from the file */
        for (j = 0; j < map->cols; j++)
        {
            fscanf(file, " %c", &cellChar);
            switch (cellChar)
            {
            case '0':
                map->grid[i][j] = EMPTY;
                break;
            case '1':
                map->grid[i][j] = ROAD;
                break;
            case '2':
                /* Initialize car position and direction */
                map->grid[i][j] = CAR;
                car->x = j;
                car->y = i;
                car->currentDir = '>';
                break;
            case '3':
                /* Initialize player position and set it on map */
                map->grid[i][j] = PLAYER;
                initializePlayer(map->player, j, i, EMPTY);
                setPlayerOnMap(map->player, map);
                break;
            case '4':
                map->grid[i][j] = GOAL;
                break;
            default:
                map->grid[i][j] = EMPTY;
                break;
            }
        }
    }

    return map;
}

/* Function to free the memory allocated for the map */
void freeMap(Map* map)
{
    int i;

    /* Loop to free each row */
    for (i = 0; i < map->rows; i++)
    {
        free(map->grid[i]);
    }

    /* Free the grid and map */
    free(map->grid);
    free(map);
}

/* Function to print the map on the console */
void printMap(const Map* map, const Car* car)
{
    int i, j;

    /* Print top border */
    for (j = 0; j < map->cols + 2; j++)
    {
        printf("*");
    }
    printf("\n");

    /* Loop to print map content */
    for (i = 0; i < map->rows; i++)
    {
        printf("*");
        for (j = 0; j < map->cols; j++)
        {
            /* Display car's current position with its direction */
            if (i == car->y && j == car->x) {
                printf("%c", car->currentDir);
            } else {
                switch(map->grid[i][j])
                {
                case EMPTY:
                    printf("%c", EMPTY_SYMBOL);
                    break;
                case ROAD:
                    printf("%c", ROAD_SYMBOL);
                    break;
                case CAR:
                    break; /* Car handled above */
                case PLAYER:
                    printf("%c", PLAYER_SYMBOL);
                    break;
                case GOAL:
                    printf("%c", GOAL_SYMBOL);
                    break;
                default:
                    printf("?"); /* For debugging unknown symbols */
                    break;
                }
            }
        }
        printf("*\n");
    }

    /* Print bottom border */
    for (j = 0; j < map->cols + 2; j++)
    {
        printf("*");
    }
    printf("\n");

    /* Display controls */
    printf("\npress w to move up\n");
    printf("press s to move down\n");
    printf("press a to move left\n");
    printf("press d to move right\n");
}
