#include <stdio.h>
#include <string.h>
#include <conio.h>

/* Function to convert decimal to binary */
void decimalToBinary(int decimal, char binary[]) {
    int i = 0, len, j;
    char temp;
    if (decimal == 0) {
        strcpy(binary, "0");
        return;
    }

    while (decimal > 0) {
        binary[i++] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binary[i] = '\0';

    /* Reverse the binary string to get correct order */
    len = strlen(binary);
    for (j = 0; j < len / 2; j++) {
        temp = binary[j];
        binary[j] = binary[len - j - 1];
        binary[len - j - 1] = temp;
    }
}

/* Function to find 1's complement */
void onesComplement(char bin[], char ones[]) {
    int i;
    for (i = 0; bin[i] != '\0'; i++) {
        if (bin[i] == '0')
            ones[i] = '1';
        else if (bin[i] == '1')
            ones[i] = '0';
        else {
            printf("Invalid binary digit: %c\n", bin[i]);
            ones[0] = '\0';  /* Mark error */
            return;
        }
    }
    ones[i] = '\0';
}

/* Function to find 2's complement by adding 1 to 1's complement */
void twosComplement(char ones[], char twos[]) {
    int len, carry = 1, i;
    len = strlen(ones);

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

void main() {
    int decimal;
    char binary[50], ones[50], twos[50];

    clrscr();

    printf("Enter a decimal number: ");
    scanf("%d", &decimal);

    if (decimal < 0) {
        printf("Only positive decimal numbers are supported in this version.\n");
        getch();
        return;
    }

    /* Convert to binary */
    decimalToBinary(decimal, binary);

    /* 1's complement */
    onesComplement(binary, ones);

    if (ones[0] == '\0') {
        printf("Invalid binary number.\n");
        getch();
        return;
    }

    /* 2's complement */
    twosComplement(ones, twos);

    printf("\nDecimal Input      : %d", decimal);
    printf("\nBinary Equivalent  : %s", binary);
    printf("\n1's Complement     : %s", ones);
    printf("\n2's Complement     : %s\n", twos);

    getch();
}
