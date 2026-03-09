#include <stdio.h>
#include <math.h>

#define sinf(x) (float)sin((double)(x))
#define cosf(x) (float)cos((double)(x))

void nullMatrix(float m[3][3])
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m[i][j] = 0.0;
        }
    }
}

void printMatrix(const float m[3][3])
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%4.4f ", m[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(float a[3][3], float b[3][3], float c[3][3])
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void ScalarMultiplyMatrix(float a[3][3], float s, float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] * s;
        }
    }
}

void diagonalMatrix(float m[3][3])
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) {
                m[i][j] = 1.0;
            } else {
                m[i][j] = 0.0;
            }
        }
    }
}

void multiplyMatrices(float a[3][3], float b[3][3], float c[3][3])
{
    nullMatrix(c);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transformPoint(const float m[3][3], const float p[3], float r[3])
{
    for (int i = 0; i < 3; ++i) {
        r[i] = 0.0;
        for (int j = 0; j < 3; ++j) {
            r[i] += m[i][j] * p[j];
        }
    }
}

void scale(float m[3][3], float s, float r[3][3])
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            r[i][j] = m[i][j] * s;
        }
    }
}

void shift(float i[3][3], float tx, float ty, float r[3][3]) {
    float T[3][3];
    diagonalMatrix(T);
    T[0][2] = tx; 
    T[1][2] = ty; 
    
    multiplyMatrices(T, i, r);
}

void rotate(const float i[3][3], float a, float r[3][3]) {
    float radians = a * (M_PI / 180.0);
    float c = cosf(radians);
    float s = sinf(radians);
    
    float R[3][3] = {
        {c, -s, 0},
        {s,  c, 0},
        {0,  0, 1}
    };
    
    multiplyMatrices(R, i, r);
}

void copyMatrix(float s[3][3], float d[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            d[i][j] = s[i][j];
        }
    }
}

int main(int argc, char* argv[])
{
    float T1[3][3], T2[3][3], R[3][3];
    float tmp[3][3], M[3][3];

    diagonalMatrix(T1);
    shift(T1, 0.0f, 3.0f, tmp);
    copyMatrix(tmp, T1);
    
    diagonalMatrix(R);
    R[1][1] = -1.0f;

    diagonalMatrix(T2);
    shift(T2, 0.0f, -3.0f, tmp);
    copyMatrix(tmp, T2);

    multiplyMatrices(R, T1, tmp);
    multiplyMatrices(T2, tmp, M);   
    printMatrix(M);
    
	return 0;
}