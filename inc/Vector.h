// David Sami 2015

#include <math.h>
#include <string.h>

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
    Vector() { x=0; y=0; z=0; }
    Vector(double aX, double aY, double aZ) { x=aX; y=aY; z=aZ; }
    Vector(const Vector& aVector) { x=aVector.x; y=aVector.y; z=aVector.z; }

    Vector& operator=(const Vector& aVector) { x=aVector.x; y=aVector.y; z=aVector.z; return *this; }

    Vector operator-() { return Vector(-x, -y, -z); }

    Vector operator+(const Vector& aVector) const { return Vector(x+aVector.x, y+aVector.y, z+aVector.z); }
    Vector operator-(const Vector& aVector) const { return Vector(x-aVector.x, y-aVector.y, z-aVector.z); }
    Vector operator*(const Vector& aVector) const { return Vector(x*aVector.x, y*aVector.y, z*aVector.z); }
    Vector operator/(const Vector& aVector) const { return Vector(x/aVector.x, y/aVector.y, z/aVector.z); }

    Vector& operator+=(const Vector& aVector) { x+=aVector.x; y+=aVector.y; z+=aVector.z; return *this; }
    Vector& operator-=(const Vector& aVector) { x-=aVector.x; y-=aVector.y; z-=aVector.z; return *this; }
    Vector& operator*=(const Vector& aVector) { x*=aVector.x; y*=aVector.y; z*=aVector.z; return *this; }
    Vector& operator/=(const Vector& aVector) { x/=aVector.x; y/=aVector.y; z/=aVector.z; return *this; }

    Vector operator*(const double aF) { return Vector(x*aF, y*aF, z*aF); }
    Vector operator/(const double aF) { return Vector(x/aF, y/aF, z/aF); }
    Vector& operator*=(const double aF) { x*=aF; y*=aF; z*=aF; return *this; }
    Vector& operator/=(const double aF) { x/=aF; y/=aF; z/=aF; return *this; }

    bool operator==(const Vector& aVector) { return (x==aVector.x && y==aVector.y && z==aVector.z); }
    bool operator!=(const Vector& aVector) { return !(*this==aVector); }

    double LengthSquared() { return x*x + y*y + z*z; }
    double Length() { return sqrtf(LengthSquared()); }

    Vector Normal() { return *this / Length(); }

    static double DistanceSquared(const Vector& a, const Vector& b) { return (a-b).LengthSquared(); }
    static double Distance(const Vector& a, const Vector& b) { return (a-b).Length(); }

    static double Dot(const Vector& a, const Vector& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
    static Vector Cross(const Vector& a, const Vector& b) { 
        return Vector(a.y*b.z - a.z*b.y,
                      a.z*b.x - a.x*b.z,
                      a.x*b.y - a.y*b.x);
    }

    double x, y, z;
};

class Ray{
public:
    Vector o, d;
};

class Matrix4{
public:
    Matrix4() { 
        memset(m,0,sizeof(m)); 
        for(int i=0; i<4; i++){
            m[i][i]=1;
        } 
    }

    Matrix4(double aM[4][4]) { 
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                m[i][j] = aM[i][j];
            }
        }
    }

    bool operator==(const Matrix4 &m2) const{
        for (int i=0; i<4; i++){
            for (int j=0; j<4; j++){
                if (m[i][j] != m2.m[i][j])
                    return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix4 &m2) const{
        return !(*this == m2);
    }

    Matrix4 operator*(const Matrix4 &aM) const{
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

    Matrix4 Transpose(){
        Matrix4 out;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                out.m[j][i] = m[i][j];
            }
        }
        return out;
    }

    Matrix4 Inverse(){
        // Gauss-Jordan Elimination
        // Set up A as [M I]
        // Apply Gaussian Elimination
        // Return B from a = [I B]

        // Initialize
        double a[4][8] = {0};
        PrintGaussianMatrix(a);
        a[0][4] = a[1][5] = a[2][6] = a[3][7] = 1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                a[i][j] = m[i][j];
            }
        }

        PrintGaussianMatrix(a);

        // Row by row
        for (int i = 0; i < 4; i++) {
            PrintGaussianMatrix(a);
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

        PrintGaussianMatrix(a);

        // Work up the Matrix
        for (int i = 3; i >= 0; i--){
            for(int j = i - 1; j >= 0; j--){
                double mul = a[j][i];
                std::cout << mul << std::endl;
                for(int k = i; k < 8; k++){
                    a[j][k] -= mul * a[i][k];
                }
            }
        }

        PrintGaussianMatrix(a);

        double out[4][4];
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                out[i][j] = a[i][j+4];
            }
        }

        PrintGaussianMatrix(a);
        return Matrix4(out);
error:
        std::cout << "ERROR\n";
        return Matrix4();
    }

    double m[4][4];
private:
    static void PrintGaussianMatrix(double m[4][8]){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 8; j++){
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif
