#include <stdio.h>

int main() {
    int a;

    scanf("%d", &a);
    printf("%d", a);

    if ( a > 0 ) {
        printf("%d é > que 0\n");
    }
    else {
        a--;
    }

    for(int i = 0; i < a; i++) {
        a++;
    }

    while(1) {
        a++;
    }

    return 0;
}