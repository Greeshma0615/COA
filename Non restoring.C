#include <stdio.h>
#include <conio.h>

#define BITS 8  // Number of bits for dividend and divisor

// Function to convert decimal to binary array
void toBinary(int num, int arr[]) {
    int i;
    for (i = BITS - 1; i >= 0; i--) {
        arr[i] = num & 1;
        num >>= 1;
    }
}

// Function to display binary number
void displayBinary(int arr[], int len) {
    int i;
    for (i = 0; i < len; i++)
        printf("%d", arr[i]);
}

// Left shift A and Q registers
void leftShift(int A[], int Q[]) {
    int i;
    for (i = 0; i < BITS - 1; i++)
        A[i] = A[i + 1];
    A[BITS - 1] = Q[0];
    for (i = 0; i < BITS - 1; i++)
        Q[i] = Q[i + 1];
}

// Binary addition of two arrays (A = A + M)
void add(int A[], int M[]) {
    int i, carry = 0, sum;
    for (i = BITS - 1; i >= 0; i--) {
        sum = A[i] + M[i] + carry;
        A[i] = sum % 2;
        carry = sum / 2;
    }
}

// 2's complement of M (negM = -M)
void twosComplement(int M[], int negM[]) {
    int i, carry = 1;
    for (i = 0; i < BITS; i++)
        negM[i] = !M[i]; // 1's complement
    for (i = BITS - 1; i >= 0; i--) { // Add 1
        if (negM[i] == 0 && carry == 1) {
            negM[i] = 1;
            carry = 0;
            break;
        } else if (negM[i] == 1 && carry == 1) {
            negM[i] = 0;
        }
    }
}

int main() {
    int A[BITS], Q[BITS], M[BITS], negM[BITS];
    int dividend, divisor;
    int i, quotient = 0, remainder = 0;

    clrscr();

    printf("Enter Dividend (positive integer): ");
    scanf("%d", &dividend);
    printf("Enter Divisor (positive integer): ");
    scanf("%d", &divisor);

    if (divisor == 0) {
        printf("Error: Division by zero not allowed.");
        getch();
        return 0;
    }

    // Initialize registers with zero
    for (i = 0; i < BITS; i++) {
        A[i] = 0;
        Q[i] = 0;
        M[i] = 0;
        negM[i] = 0;
    }

    toBinary(dividend, Q);
    toBinary(divisor, M);
    twosComplement(M, negM);

    printf("\nInitial values:\nA: ");
    displayBinary(A, BITS);
    printf("\nQ: ");
    displayBinary(Q, BITS);
    printf("\nM: ");
    displayBinary(M, BITS);
    printf("\n");

    for (i = 0; i < BITS; i++) {
        leftShift(A, Q);
        add(A, negM);  // A = A - M

        if (A[0] == 1) {  // If A is negative
            add(A, M);    // Restore A = A + M
            Q[BITS - 1] = 0;
        } else {
            Q[BITS - 1] = 1;
        }
    }

    printf("\nFinal Quotient (Q): ");
    displayBinary(Q, BITS);
    printf("\nFinal Remainder (A): ");
    displayBinary(A, BITS);

    // Convert binary arrays back to decimal
    for (i = 0; i < BITS; i++) {
        quotient = (quotient << 1) | Q[i];
        remainder = (remainder << 1) | A[i];
    }

    printf("\n\nQuotient (Decimal): %d", quotient);
    printf("\nRemainder (Decimal): %d\n", remainder);

    getch();
    return 0;
}

