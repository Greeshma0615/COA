#include <stdio.h>
#include <conio.h>

void decimalToBinary(int num) {
    int binary[32];  // Array to store binary digits
    int i = 0;

    if (num == 0) {
        printf("0");
        return;
    }

    while (num > 0) {
        binary[i] = num % 2;
        num = num / 2;
        i++;
    }

    // Print binary digits in reverse order
    for (i = i - 1; i >= 0; i--) {
        printf("%d", binary[i]);
    }
}

int main() {
    int decimalNumber;

    clrscr();  // Clear screen

    printf("Enter a decimal number: ");
    scanf("%d", &decimalNumber);

    printf("Binary equivalent: ");
    decimalToBinary(decimalNumber);

    printf("\n");
    getch();  // Wait for a key press
    return 0;
}