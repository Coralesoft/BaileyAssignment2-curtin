#include <stdlib.h>
#include "fileHandler.h"

FILE* openFile(const char *filename) 
{
    /* Attempt to open the file for reading */
    FILE *file = fopen(filename, "r");
    
    /* Error check */
    if (file == NULL) 
    {
        fprintf(stderr, "Error: Unable to open file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }
    
    return file; 
}
