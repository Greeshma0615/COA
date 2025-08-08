#include <stdio.h>
#include <conio.h>
#include <string.h>

// Function to find 1's complement
void onesComplement(char bin[], char ones[]) {
    int i;
    for (i = 0; bin[i] != '\0'; i++) {
        if (bin[i] == '0')
            ones[i] = '1';
        else if (bin[i] == '1')
            ones[i] = '0';
        else {
            printf("Invalid binary digit: %c\n", bin[i]);
            ones[0] = '\0';  // Mark error
            return;
        }
    }
    ones[i] = '\0';
}

// Function to find 2's complement by adding 1 to 1's complement
void twosComplement(char ones[], char twos[]) {
    int len = strlen(ones);
    int carry = 1;
    int i;

    for (i = len - 1; i >= 0; i--) {
        if (ones[i] == '1' && carry == 1) {
            twos[i] = '0';
        } else if (ones[i] == '0' && carry == 1) {
            twos[i] = '1';
            carry = 0;
        } else {
            twos[i] = ones[i];
        }
    }
    twos[len] = '\0';
}

int main() {
    char binary[20], ones[20], twos[20];

    clrscr();  // Turbo C screen clear

    printf("Enter a binary number: ");
    scanf("%s", binary);

    onesComplement(binary, ones);

    // Error check
    if (ones[0] == '\0') {
        printf("Invalid binary number.\n");
        getch();
        return 1;
    }

    twosComplement(ones, twos);

    printf("\nOriginal Binary   : %s", binary);
    printf("\n1's Complement    : %s", ones);
    printf("\n2's Complement    : %s", twos);

    getch();  // Wait for key press
    return 0;
}