#include <stdio.h>

int main() {
    int a = 10;
    float b = 20.5;
    char c = 'x';

    if (a > 5) {
        a = a + 1;
        printf("a is greater than 5\n");
    } else {
        a = a - 1;
        printf("a is less than or equal to 5\n");
    }

    while (a < 10) {
        a = a * 2;
        printf("a is now %d\n", a);
    }

    for (int i = 0; i < 10; i++) {
        printf("Iteration %d\n", i);
    }

    return 0;
}
