#include <stdio.h>
#include <stdlib.h>

int main() {
    int num;

    printf("Bir sayı giriniz: ");
    scanf("%d", &num);

    if (num != 0) {
        printf("Girilen sayı %d, program exit komutu ile mantıksal olarak sonlandırılıyor...\n", num);
        exit(0);
    }

    printf("Girilen sayı 0, program normal şekilde sonlandırılıyor...\n");

    return 0;
}
