#include <string.h>

// f(ile)2s(tring).c

char *reader(FILE *f, int *lengthOut) {
    char *buffer;
    long length;

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = malloc(length);

        if (buffer)
            fread(buffer, length, 1, f);

        fclose(f);
        
        if (lengthOut)
            *lengthOut = length;

        return buffer;
    }
   
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));

    return NULL;
}
