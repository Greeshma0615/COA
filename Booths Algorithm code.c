#include <stdio.h>
#include <conio.h>

#define SIZE 8   // number of bits (increase if needed)

// Function to convert decimal to binary (two's complement for negatives)
void decToBin(int num, int bin[], int n) {
    int i;
    if (num >= 0) {
        for (i = n - 1; i >= 0; i--) {
            bin[i] = num % 2;
            num /= 2;
        }
    } else {
        num = (1 << n) + num; // two's complement form
        for (i = n - 1; i >= 0; i--) {
            bin[i] = num % 2;
            num /= 2;
        }
    }
}

// Add two binary numbers
void addBin(int a[], int b[], int res[], int n) {
    int carry = 0, i;
    for (i = n - 1; i >= 0; i--) {
        int sum = a[i] + b[i] + carry;
        res[i] = sum % 2;
        carry = sum / 2;
    }
}

// Two's complement (negation)
void twosComplement(int a[], int res[], int n) {
    int i, one[SIZE] = {0}, temp[SIZE];
    for (i = 0; i < n; i++)
        temp[i] = (a[i] == 0) ? 1 : 0;  // one's complement
    one[n - 1] = 1;
    addBin(temp, one, res, n);          // add 1
}

// Arithmetic right shift on A, Q, Q-1
void arithmeticShiftRight(int A[], int Q[], int *Qm1, int n) {
    int i, tempA = A[n - 1];  // sign bit
    *Qm1 = Q[n - 1];

    for (i = n - 1; i > 0; i--)
        Q[i] = Q[i - 1];
    Q[0] = A[n - 1];

    for (i = n - 1; i > 0; i--)
        A[i] = A[i - 1];
    A[0] = tempA;
}

// Print binary array
void printArray(int a[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d", a[i]);
}

void main() {
    int m, q;
    int n = SIZE;   // bit size
    int A[SIZE] = {0}, M[SIZE], Q[SIZE], negM[SIZE];
    int Qm1 = 0;
    int i;

    clrscr();
    printf("Enter Multiplicand (M): ");
    scanf("%d", &m);
    printf("Enter Multiplier (Q): ");
    scanf("%d", &q);

    // Convert numbers to binary
    decToBin(m, M, n);
    decToBin(q, Q, n);
    twosComplement(M, negM, n);

    printf("\nInitial Values:\nA = ");
    printArray(A, n);
    printf("  Q = ");
    printArray(Q, n);
    printf("  Q-1 = %d", Qm1);

    // Booth’s Algorithm
    for (i = 0; i < n; i++) {
        if (Q[n - 1] == 1 && Qm1 == 0) {
            addBin(A, negM, A, n); // A = A - M
            printf("\n\nStep %d: A = A - M", i + 1);
        } else if (Q[n - 1] == 0 && Qm1 == 1) {
            addBin(A, M, A, n);    // A = A + M
            printf("\n\nStep %d: A = A + M", i + 1);
        }

        arithmeticShiftRight(A, Q, &Qm1, n);
        printf("\nAfter Shift %d: A = ", i + 1);
        printArray(A, n);
        printf("  Q = ");
        printArray(Q, n);
        printf("  Q-1 = %d", Qm1);
    }

    printf("\n\nFinal Result (Binary) = ");
    printArray(A, n);
    printArray(Q, n);

    printf("\nResult (Decimal) = %d", m * q);

    getch();
}
