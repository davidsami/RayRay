// David Sami 2015

#include "Matrix.h"
#include <string.h>
#include <iostream>

Matrix4 :: Matrix4() { 
    // Identity Matrix
    memset(m,0,sizeof(m)); 
    for(int i=0; i<4; i++){
        m[i][i]=1;
    } 
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

Matrix4 Matrix4 :: Inverse(){
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


    // Row by row
    for (int i = 0; i < 4; i++) {
        // If the leftmost number is zero, switch row out with another row
        if (a[i][i] == 0){
            bool validRowFound = false;
            for(int j = i + 1; j < 4; j++) {
                if (a[i][i] != 0){
                    validRowFound = true;

                    // Switch those rows
                    for(int k = 0; k < 8; k++){
                        double temp = a[i][k];
                        a[i][k] = a[j][k];
                        a[j][k] = temp;
                    }
                    break;
                }
            }
            if (!validRowFound)
                goto error;
        }

        // Divide row by leftmost number
        if (a[i][i] != 1){
            double div = a[i][i];
            for (int j = i; j < 8; j++){
                a[i][j] /= div;
            }
        }

        // Set leftmost column to 0 under current row
        // by subtracting the current row * leftmost number
        for(int j = i + 1; j < 4; j++){
            double mul = a[j][i];
            for(int k = i; k < 8; k++){
                a[j][k] -= mul * a[i][k];
            }
        }
    }

    // Work up the Matrix
    for (int i = 3; i >= 0; i--){
        for(int j = i - 1; j >= 0; j--){
            double mul = a[j][i];
            for(int k = i; k < 8; k++){
                a[j][k] -= mul * a[i][k];
            }
        }
    }

    double out[4][4];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            out[i][j] = a[i][j+4];
        }
    }

    return Matrix4(out);
error:
    std::cout << "ERROR\n";
    return Matrix4();
}

