#include <stdio.h>

void printMatrix(double m[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%6.1f ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiplyMatrices(double a[3][3], double b[3][3], double result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {
    double M1[3][3] = {{1, 0, 3}, {0, 1, 0}, {0, 0, 1}};
    double M2[3][3] = {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    double M3[3][3] = {{1, 0, -3}, {0, 1, 0}, {0, 0, 1}};

    double helpy[3][3];
    double Mc[3][3];

    multiplyMatrices(M2, M1, helpy);
    multiplyMatrices(M3, helpy, Mc);

    printf("The Final Transformation Matrix:\n");
    printMatrix(Mc);

    return 0;
}