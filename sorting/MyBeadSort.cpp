#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BEAD(i, j) beads[i * max + j] //i means layer num(how many numbers), j means post num(maximum numbers)
void beadSort(int *a, int len) {
    //find the maximum element
    int max = a[0];
    for (int i = 1; i < len; i ++) {
        if (a[i] > max) {
            max = a[i];
        }
    }

    unsigned char * beads = (unsigned char *)malloc(max * len * sizeof(unsigned char));
    memset(beads, 0, max * len * sizeof(unsigned char));
    //mark the beads
    for (int i = 0; i < len; i ++) {
        for (int j = 0; j < a[i]; j ++) {
            BEAD(i, j) = 1;
        }
    }

    //count the sum of beads
    for (int j = 0; j < max; j ++) {
        int sum = 0;
        for (int i = 0; i < len; i ++) {
            sum += BEAD(i, j);
            BEAD(i, j) = 0;
        }
        //move the beads
        for(int i = len - sum; i < len; i ++) {
            BEAD(i, j) = 1;
        }
    }

    for (int i = 0; i < len; i ++) {
        int j = 0;
        while(BEAD(i, j)) {
            j ++;
        }
        a[i] = j;
    }
    free(beads);
    beads = 0;
}

int main() {
    int a [] = {1, 5, 1, 6, 9, 22, 1};
    int len = sizeof(a) / sizeof(a[0]);
    printf("len:%d\n", len);

    beadSort(a, len);
    for(int i = 0; i < len; i ++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
