#include <stdio.h>
#include <stdlib.h>     /* For system() */
#include <stdbool.h>    /* For bool, true, and false */
#include <ctype.h>      /* For tolower() */
#include "fileHandler.h"
#include "game.h"
#include "terminal.h"
#include "carMovement.h"

/* Define macro for clearing screen based on OS */
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

/* Function to clear terminal screen */
void clearScreen()
{
    system(CLEAR_SCREEN);
}

int main(int argc, char *argv[])
{
    FILE *file;
    Map *map;
    Car car;
    Player player;
    char userInput;
    bool gameRunning = true;

    /* Check for correct number of arguments */
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    /* Attempt to open the specified file */
    file = openFile(argv[1]);

    if (file)
    {
        printf("File '%s' opened successfully!\n", argv[1]);

        /* Load map data */
        map = loadMapFromFile(file, &player, &car);  /* Pass car as a parameter here */
        fclose(file);
    }
    else
    {
        printf("Error opening file '%s'.\n", argv[1]);
        return 1;
    }

    disableBuffer();

    /* Main game loop */
    while(gameRunning)
    {
        clearScreen();  /* Clear the terminal screen */

        printMap(map, &car);  /* Print the game map */

        /* Read and lower-case the user input */
        userInput = tolower(getchar());

        /* Check for player movement */
        if(userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd')
        {
            /* Handle player and car movements */
            playerMovement(map->grid, map->player, userInput, map->rows, map->cols);
            carMovement(map->grid, &car, map->rows, map->cols);
        }
        else if(userInput == 'q')
        {
            /* Terminate the game */
            gameRunning = false;
        }
    }

    enableBuffer();  /* Enable terminal buffer before exiting */

    freeMap(map);  /* Free allocated map memory */

    return 0;
}
