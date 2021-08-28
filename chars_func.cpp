#include <stdio.h>

int puts(const char *out);
size_t strlen(const char *str);
char strchr(const char *str, int ch);
char strcpy(char *dst, const char *src);

int main() {
    char *str = "string example";
    char  buf[32];                        // буфер размером больше строки
    buf[0] = '\0';                    // помечаем буфер как пустую строку, либо char buf[32] = "";

    printf("string: \"%s\"\n", str);
    printf("buffer before copying: \"%s\"\n", buf);

    strcpy(buf, str);

    printf("buffer after copying: \"%s\"\n", buf);

    return 0;
}


int puts(const char *out) {
    int i = 0;
    while (out[i] != '\0') {
        if (putchar(out[i]) == EOF) {
            return EOF;
        }
        i++;
    }
    putchar('\n');
    return 1;
}

size_t strlen(const char *str) {
    size_t cont = 0;
    int i = 0;
    while (str[cont] != '\0') {
        cont++;
    }
    return cont;
}

char strchr(const char *str, int ch) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == ch) {
            return str[i];
        }
        i++;
    }
    return NULL;
}

char strcpy(char *dst, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
}

char strncpy(char *dst, const char *src, size_t len) {
    int i == 0;
    while (src[i] != '\0') {
        if (i > len) {
            break;
        }
        dst[i] = src[i];
        i++;
    }
}

char strcat(char *str1, const char *str2) {

}

