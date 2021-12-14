//十六进制转二进制小工具
#include <stdio.h>

int tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 'a' - 'A';
    } else {
        return c;
    }
}

long htoi(char s[]) {
    int i;
    long n = 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
    } else {
        i = 0;
    }
    for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'); ++i) {
        if (tolower(s[i]) > '9') {
            n = 16 * n + (10 + tolower(s[i]) - 'a');
        } else {
            n = 16 * n + (tolower(s[i]) - '0');
        }
    }
    return n;
}

int main(int argc, char **argv) {
    long value = htoi("0xb400006fe0493bd0");
    printf("string=0xb400006fe0493bd0, value=%ld\n", value);
    return 0;
}
