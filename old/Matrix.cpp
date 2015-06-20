// David Sami 2015

#include "Matrix.h"
#include <string.h>
#include <cmath>
#include <iostream>
#include <iomanip>

static double id[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
const Matrix4 Matrix4::Identity(id);

Matrix4 :: Matrix4() { 
    // Identity Matrix
    memset(m,0,sizeof(m)); 
}

Matrix4 :: Matrix4(double aM[4][4]) { 
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            m[i][j] = aM[i][j];
        }
    }
}

bool Matrix4 :: operator==(const Matrix4 &m2) const{
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if (m[i][j] != m2.m[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix4 :: operator!=(const Matrix4 &m2) const{
    return !(*this == m2);
}

Matrix4 Matrix4 :: operator*(const Matrix4 &aM) const{
    Matrix4 out;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            out.m[i][j] = 0;
            for(int k = 0; k < 4; k++){
                out.m[i][j] += m[i][k] * aM.m[k][j];
            }
        }
    }
    return out;
}

Matrix4 Matrix4 :: Transpose(){
    Matrix4 out;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            out.m[j][i] = m[i][j];
        }
    }
    return out;
}

#define ZERO_TOL (1e-13)
inline bool Matrix4::equalsZero(double num, double tol = ZERO_TOL){
    return (fabs(num) < tol);
}

#define TEST() 
/*std::cout \
        << "TEST" << std::endl \
        << pivotTable[0] << ", " << pivotTable[1] << ", " << pivotTable[2] << ", " << pivotTable[3] << ", " << std::endl \
        << "[" << std::setw(12) << a[0][0] << std::setw(12) << a[0][1] << std::setw(12) << a[0][2] << std::setw(12) << a[0][3] << std::setw(12) << a[0][4] << std::setw(12) << a[0][5] << std::setw(12) << a[0][6] << std::setw(12) << a[0][7] << "]" << std::endl\
        << "[" << std::setw(12) << a[1][0] << std::setw(12) << a[1][1] << std::setw(12) << a[1][2] << std::setw(12) << a[1][3] << std::setw(12) << a[1][4] << std::setw(12) << a[1][5] << std::setw(12) << a[1][6] << std::setw(12) << a[1][7] << "]" << std::endl\
        << "[" << std::setw(12) << a[2][0] << std::setw(12) << a[2][1] << std::setw(12) << a[2][2] << std::setw(12) << a[2][3] << std::setw(12) << a[2][4] << std::setw(12) << a[2][5] << std::setw(12) << a[2][6] << std::setw(12) << a[2][7] << "]" << std::endl\
        << "[" << std::setw(12) << a[3][0] << std::setw(12) << a[3][1] << std::setw(12) << a[3][2] << std::setw(12) << a[3][3] << std::setw(12) << a[3][4] << std::setw(12) << a[3][5] << std::setw(12) << a[3][6] << std::setw(12) << a[3][7] << "]" << std::endl << std::endl
        */

Matrix4 Matrix4 :: Inverse(){
    //Debug();
    // Gauss-Jordan Elimination
    // Set up A as [M I]
    // Apply Gaussian Elimination
    // Return B from a = [I B]

    // Initialize
    double a[4][8] = {0};
    a[0][4] = a[1][5] = a[2][6] = a[3][7] = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            a[i][j] = m[i][j];
        }
    }

    int pivotTable[4] = {0,1,2,3};
    // Row by row
    for (int x = 0; x < 4; x++) {
        int i = pivotTable[x];
    TEST();

        // If the leftmost position is zero, switch row out with another row
        if (a[i][x] == 0){
            bool foundSwitchRow = false;
            for (int y = x + 1; y < 4; y++){
                int j = pivotTable[y];
                if (!equalsZero(a[j][x])){
                    int temp = pivotTable[y];
                    pivotTable[y] = pivotTable[x];
                    pivotTable[x] = temp;
                    foundSwitchRow = true;
                    break;
                }
            }

            if(!foundSwitchRow){
                goto error;
            }
        }

        i = pivotTable[x];
    TEST();

        // Divide row by leftmost number
        if (a[i][x] != 1){
            double div = 1.f/a[i][x];
            for (int j = x; j < 8; j++){
                a[i][j] *= div;
                if (equalsZero(a[i][j])){
                    a[i][j] = 0;
                }
            }
        }
    TEST();

        // Set leftmost column to 0 under current row
        // by subtracting the current row * leftmost number
        for(int y = x + 1; y < 4; y++){
            int j = pivotTable[y];
            double mul = a[j][x];
            for(int k = x; k < 8; k++){
                a[j][k] -= mul * a[i][k];
                if (equalsZero(a[j][k])){
                    a[j][k] = 0;
                }
            }
        }
        TEST();
    }

    // Work up the Matrix
    for (int x = 3; x >= 0; x--){
        int i = pivotTable[x];
    TEST();
        for(int y = x - 1; y >= 0; y--){
            int j = pivotTable[y];
            double mul = a[j][x];
            for(int k = x; k < 8; k++){
                a[j][k] -= mul * a[i][k];
                if (equalsZero(a[j][k])){
                    a[j][k] = 0;
                }
            }
        }
    }
    TEST();

    double out[4][4];
    for (int x = 0; x < 4; x++){
        int i = pivotTable[x];
        for (int j = 0; j < 4; j++){
            out[x][j] = a[i][j+4];
        }
    }

    return Matrix4(out);
error:
    std::cout << "ERROR\n";
    return Matrix4();
}

double Matrix4::Determinant(){
    // Hard coded
    return 
        m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0]-
        m[0][3] * m[1][1] * m[2][2] * m[3][0]+m[0][1] * m[1][3] * m[2][2] * m[3][0]+
        m[0][2] * m[1][1] * m[2][3] * m[3][0]-m[0][1] * m[1][2] * m[2][3] * m[3][0]-
        m[0][3] * m[1][2] * m[2][0] * m[3][1]+m[0][2] * m[1][3] * m[2][0] * m[3][1]+
        m[0][3] * m[1][0] * m[2][2] * m[3][1]-m[0][0] * m[1][3] * m[2][2] * m[3][1]-
        m[0][2] * m[1][0] * m[2][3] * m[3][1]+m[0][0] * m[1][2] * m[2][3] * m[3][1]+
        m[0][3] * m[1][1] * m[2][0] * m[3][2]-m[0][1] * m[1][3] * m[2][0] * m[3][2]-
        m[0][3] * m[1][0] * m[2][1] * m[3][2]+m[0][0] * m[1][3] * m[2][1] * m[3][2]+
        m[0][1] * m[1][0] * m[2][3] * m[3][2]-m[0][0] * m[1][1] * m[2][3] * m[3][2]-
        m[0][2] * m[1][1] * m[2][0] * m[3][3]+m[0][1] * m[1][2] * m[2][0] * m[3][3]+
        m[0][2] * m[1][0] * m[2][1] * m[3][3]-m[0][0] * m[1][2] * m[2][1] * m[3][3]-
        m[0][1] * m[1][0] * m[2][2] * m[3][3]+m[0][0] * m[1][1] * m[2][2] * m[3][3];
}

void Matrix4::Debug(){
    std::cout 
        << "DEBUG" << std::endl
        << "[" << std::setw(12) << m[0][0] << std::setw(12) << m[0][1] << std::setw(12) << m[0][2] << std::setw(12) << m[0][3] << "]" << std::endl
        << "[" << std::setw(12) << m[1][0] << std::setw(12) << m[1][1] << std::setw(12) << m[1][2] << std::setw(12) << m[1][3] << "]" << std::endl
        << "[" << std::setw(12) << m[2][0] << std::setw(12) << m[2][1] << std::setw(12) << m[2][2] << std::setw(12) << m[2][3] << "]" << std::endl
        << "[" << std::setw(12) << m[3][0] << std::setw(12) << m[3][1] << std::setw(12) << m[3][2] << std::setw(12) << m[3][3] << "]" << std::endl
        << "Determinant: " << Determinant() << std::endl << std::endl;
}

