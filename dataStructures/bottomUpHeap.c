#include <stdio.h>
#define max 50

void bottomUpMaxHeap(int h[max], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        int key = h[i];
        int p = i;
        int c = 2 * p + 1;

        while (c < n) {
            if (c + 1 < n && h[c + 1] > h[c]) {
                c = c + 1;
            }
            if (key < h[c]) {
                h[p] = h[c];
                p = c;
                c = 2 * p + 1;
            } else {
                break;
            }
        }
        h[p] = key;
    }
}

int main() {
    int h[max], n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &h[i]);
    }

    bottomUpMaxHeap(h, n);

    printf("Bottom-Up Max Heap:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", h[i]);
    }

    return 0;
}
