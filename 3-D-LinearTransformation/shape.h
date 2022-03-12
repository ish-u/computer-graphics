#include <iostream>
#include <math.h>
#include <graphics.h>
#include "matrix.h"
using namespace std;

// Shape Class
class Shape
{

public:
    // Data Memebers
    Matrix *coOrdinates;
    int numberOfCoOrdinates = 0;
    int numberOfFaces = 0;
    Matrix *faces;
    // Constructor
    Shape()
    {

        // A CUBE WITH A CORNER CUT
        this->numberOfCoOrdinates = 10;
        this->coOrdinates = new Matrix(10, 4);
        // A
        this->coOrdinates->m[0][0] = 200;
        this->coOrdinates->m[0][1] = 100;
        this->coOrdinates->m[0][2] = 200;

        // B
        this->coOrdinates->m[1][0] = 300;
        this->coOrdinates->m[1][1] = 100;
        this->coOrdinates->m[1][2] = 200;

        // C
        this->coOrdinates->m[2][0] = 300;
        this->coOrdinates->m[2][1] = 150;
        this->coOrdinates->m[2][2] = 200;

        // D
        this->coOrdinates->m[3][0] = 250;
        this->coOrdinates->m[3][1] = 200;
        this->coOrdinates->m[3][2] = 200;

        // E
        this->coOrdinates->m[4][0] = 200;
        this->coOrdinates->m[4][1] = 200;
        this->coOrdinates->m[4][2] = 200;

        // F
        this->coOrdinates->m[5][0] = 200;
        this->coOrdinates->m[5][1] = 100;
        this->coOrdinates->m[5][2] = 100;

        // G
        this->coOrdinates->m[6][0] = 300;
        this->coOrdinates->m[6][1] = 100;
        this->coOrdinates->m[6][2] = 100;

        // H
        this->coOrdinates->m[7][0] = 300;
        this->coOrdinates->m[7][1] = 200;
        this->coOrdinates->m[7][2] = 100;

        // I
        this->coOrdinates->m[8][0] = 200;
        this->coOrdinates->m[8][1] = 200;
        this->coOrdinates->m[8][2] = 100;

        // J
        this->coOrdinates->m[9][0] = 300;
        this->coOrdinates->m[9][1] = 200;
        this->coOrdinates->m[9][2] = 150;

        // filling last row as 1 for Homogenous Co-Ordinates
        for (int i = 0; i < numberOfCoOrdinates; i++)
        {
            this->coOrdinates->m[i][3] = 1;
        }
        // this->coOrdinates->display();

        // WE WILL USE A ADJACENCY MATRIX TO REPRESENT WHETHER ANY TWO VERTICES (CO-ORDNIATES) ARE CONNNECTED OR NOT
        // A,B,C, ... ,J --MAPS TO--> 0,1,2, ... ,9
        this->numberOfFaces = 7;
        this->faces = new Matrix(10, 10, 0);
        // A
        this->faces->m[0][1] = 1;
        this->faces->m[0][4] = 1;
        this->faces->m[0][5] = 1;
        // B
        this->faces->m[1][0] = 1;
        this->faces->m[1][2] = 1;
        this->faces->m[1][6] = 1;
        // C
        this->faces->m[2][3] = 1;
        this->faces->m[2][1] = 1;
        this->faces->m[2][9] = 1;
        // D
        this->faces->m[3][2] = 1;
        this->faces->m[3][4] = 1;
        this->faces->m[3][9] = 1;
        // E
        this->faces->m[4][0] = 1;
        this->faces->m[4][3] = 1;
        this->faces->m[4][8] = 1;
        // F
        this->faces->m[5][0] = 1;
        this->faces->m[5][6] = 1;
        this->faces->m[5][8] = 1;
        // G
        this->faces->m[6][1] = 1;
        this->faces->m[6][5] = 1;
        this->faces->m[6][7] = 1;
        // H
        this->faces->m[7][8] = 1;
        this->faces->m[7][9] = 1;
        this->faces->m[7][6] = 1;
        // I
        this->faces->m[8][4] = 1;
        this->faces->m[8][5] = 1;
        this->faces->m[8][7] = 1;
        // J
        this->faces->m[9][2] = 1;
        this->faces->m[9][3] = 1;
        this->faces->m[9][7] = 1;

        // this->faces->display();
    }
    // Overloaded Constructor - to use when want to take input of Co-Ordinates
    Shape(int numberOfCoOrdinates)
    {
        this->numberOfCoOrdinates = numberOfCoOrdinates;
        this->coOrdinates = new Matrix(numberOfCoOrdinates, 3);
        // taking Co-Ordinate Input
        for (int i = 0; i < numberOfCoOrdinates; i++)
        {
            cout << "Co-Ordinate - " << i + 1 << " -> ";
            for (int j = 0; j < 2; j++)
            {
                cin >> this->coOrdinates->m[i][j];
            }
        }
        // filling last row as 1 for Homogenous Co-Ordinates
        for (int i = 0; i < numberOfCoOrdinates; i++)
        {
            this->coOrdinates->m[i][2] = 1;
        }
        // this->coOrdinates->display();
    }

    // Desctructor
    ~Shape()
    {
        delete this->coOrdinates;
        delete this->faces;
    }
    // member function
    void drawShape(Matrix *matrix);
    void sortCoOrdinates(int *poly, int numberOfCoOrdinates);
    void convertToHomogenous(Matrix *matrix);
    void scaling();
    void reflection();
    void shearing();
    void rotation();
    void translation();
    void transformationMatrix();
    float *getCentroid(Matrix *m);
    void orthographicProjection(Matrix *m);
    void axonometricProjection(Matrix *m);
    void prespectiveProjection(Matrix *m);
    void axisAnimation(Matrix *m);
};

// To Draw the Polygon whose Co-Ordinate are passes as in Homogenous Matrix as a "matrix" object
void Shape::drawShape(Matrix *matrix)
{
    float **coOrdinates = matrix->m;
    int numberOfCoOrdinates = matrix->r;

    // cout << "\nDRAWN FIGURE HOMOGENOUS CO_ORDINATES\n";
    // cout << "===================================";
    // matrix->display();
    // cout << "===================================\n\n";

    // DRAWING ALL THE FACES OF THE 3-D OBJECT
    for (int i = 0; i < numberOfCoOrdinates; i++)
    {
        for (int j = 0; j < numberOfCoOrdinates; j++)
        {
            if (this->faces->m[i][j] == 1)
            {
                // reflect about x-axis
                // transtale to center of window
                line((coOrdinates[i][0]) + getmaxx() / 2, -1 * coOrdinates[i][1] + getmaxy() / 2, (coOrdinates[j][0]) + getmaxx() / 2, -1 * coOrdinates[j][1] + getmaxy() / 2);
            }
        }
        // cout << "\n";
    }
}

void Shape::convertToHomogenous(Matrix *matrix)
{
    for (int i = 0; i < matrix->r; i++)
    {
        matrix->m[i][0] /= matrix->m[i][3];
        matrix->m[i][1] /= matrix->m[i][3];
        matrix->m[i][3] = 1;
    }
}

void Shape ::prespectiveProjection(Matrix *m)
{
    double pi = 4 * atan(1);
    float *centroid = getCentroid(m);
    this->coOrdinates->display();
    Matrix T = getTranslationMatrix(centroid[0], centroid[1], centroid[2]);
    Matrix T_inv = getTranslationMatrix(-1 * centroid[0], -1 * centroid[1], -1 * centroid[2]);
    Matrix pZ = getProjectionZ();
    char text[50 + sizeof(char)];
    float p = 0;
    float q = 0;
    float r = 0;

    // SINGLE POINT
    { // z -axis

        for (int i = 0; i < 10; i++)
        {
            // Grid Lines
            line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
            line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
            r = -1 * (float)i / 1000;

            sprintf(text, "Prespective -> Single Point");
            outtextxy(20, 20, text);
            sprintf(text, "p : %f \t", p);
            outtextxy(20, 40, text);
            sprintf(text, "q : %f", q);
            outtextxy(20, 60, text);
            sprintf(text, "r : %f", r);
            outtextxy(20, 80, text);

            Matrix prespective = getPrespectiveProjMatrix(p, q, r);
            Matrix requiredMatrix = (*(m)) * T * prespective * T_inv * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            this->convertToHomogenous(requiredMatrixPtr);
            this->drawShape(requiredMatrixPtr);
            delay(1000);
            cleardevice();
        }

        p = q = r = 0;
        sprintf(text, "Prespective -> Single Point");
        outtextxy(20, 20, text);
        sprintf(text, "p : %f \t", 0);
        outtextxy(20, 40, text);
        sprintf(text, "q : %f", 0);
        outtextxy(20, 60, text);
        sprintf(text, "r : %f", 0);
        outtextxy(20, 80, text);

        // y -axis
        for (int i = 0; i < 10; i++)
        {
            // Grid Lines
            line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
            line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

            q = -1 * (float)i / 1000;

            sprintf(text, "Prespective -> Single Point");
            outtextxy(20, 20, text);
            sprintf(text, "p : %f \t", p);
            outtextxy(20, 40, text);
            sprintf(text, "q : %f", q);
            outtextxy(20, 60, text);
            sprintf(text, "r : %f", r);
            outtextxy(20, 80, text);

            Matrix prespective = getPrespectiveProjMatrix(p, q, r);
            Matrix requiredMatrix = (*(m)) * T * prespective * T_inv * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            this->convertToHomogenous(requiredMatrixPtr);
            this->drawShape(requiredMatrixPtr);
            delay(1000);
            cleardevice();
        }

        p = q = r = 0;
        sprintf(text, "Prespective -> Single Point");
        outtextxy(20, 20, text);
        sprintf(text, "p : %f \t", 0);
        outtextxy(20, 40, text);
        sprintf(text, "q : %f", 0);
        outtextxy(20, 60, text);
        sprintf(text, "r : %f", 0);
        outtextxy(20, 80, text);

        // x -axis
        for (int i = 0; i < 10; i++)
        {
            // Grid Lines
            line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
            line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

            p = -1 * (float)i / 1000;

            sprintf(text, "Prespective -> Single Point");
            outtextxy(20, 20, text);
            sprintf(text, "p : %f \t", p);
            outtextxy(20, 40, text);
            sprintf(text, "q : %f", q);
            outtextxy(20, 60, text);
            sprintf(text, "r : %f", r);
            outtextxy(20, 80, text);

            Matrix prespective = getPrespectiveProjMatrix(p, q, r);
            Matrix requiredMatrix = (*(m)) * T * prespective * T_inv * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            this->convertToHomogenous(requiredMatrixPtr);
            this->drawShape(requiredMatrixPtr);
            delay(1000);
            cleardevice();
        }
    }

    // TWO POINT
    {
        p = q = r = 0;
        sprintf(text, "Prespective -> Two Point");
        outtextxy(20, 20, text);
        sprintf(text, "p : %f \t", 0);
        outtextxy(20, 40, text);
        sprintf(text, "q : %f", 0);
        outtextxy(20, 60, text);
        sprintf(text, "r : %f", 0);
        outtextxy(20, 80, text);
        // xy -axis
        for (int i = 0; i < 10; i++)
        {
            // Grid Lines
            line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
            line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
            p = -1 * (float)i / 1000;
            q = -1 * (float)i / 1000;

            sprintf(text, "Prespective -> Two Point");
            outtextxy(20, 20, text);
            sprintf(text, "p : %f \t", p);
            outtextxy(20, 40, text);
            sprintf(text, "q : %f", q);
            outtextxy(20, 60, text);
            sprintf(text, "r : %f", r);
            outtextxy(20, 80, text);

            Matrix prespectiveZ = getPrespectiveProjMatrix(p, q, r);
            Matrix requiredMatrix = (*(m)) * T * prespectiveZ * T_inv * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            this->convertToHomogenous(requiredMatrixPtr);
            this->drawShape(requiredMatrixPtr);
            delay(1000);
            cleardevice();
        }

        sprintf(text, "Prespective -> Two Point");
        outtextxy(20, 20, text);
        sprintf(text, "p : %f \t", 0);
        outtextxy(20, 40, text);
        sprintf(text, "q : %f", 0);
        outtextxy(20, 60, text);
        sprintf(text, "r : %f", 0);
        outtextxy(20, 80, text);

        // xz -axis
        p = q = r = 0;
        for (int i = 0; i < 10; i++)
        {
            // Grid Lines
            line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
            line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

            p = -1 * (float)i / 1000;
            r = -1 * (float)i / 1000;

            sprintf(text, "Prespective -> Two Point");
            outtextxy(20, 20, text);
            sprintf(text, "p : %f \t", p);
            outtextxy(20, 40, text);
            sprintf(text, "q : %f", q);
            outtextxy(20, 60, text);
            sprintf(text, "r : %f", r);
            outtextxy(20, 80, text);

            Matrix prespectiveY = getPrespectiveProjMatrix(p, q, r);
            Matrix requiredMatrix = (*(m)) * T * prespectiveY * T_inv * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            this->convertToHomogenous(requiredMatrixPtr);
            this->drawShape(requiredMatrixPtr);
            delay(1000);
            cleardevice();
        }

        sprintf(text, "Prespective -> Two Point");
        outtextxy(20, 20, text);
        sprintf(text, "p : %f \t", 0);
        outtextxy(20, 40, text);
        sprintf(text, "q : %f", 0);
        outtextxy(20, 60, text);
        sprintf(text, "r : %f", 0);
        outtextxy(20, 80, text);

        // yz -axis
        p = q = r = 0;
        for (int i = 0; i < 10; i++)
        {
            // Grid Lines
            line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
            line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

            q = -1 * (float)i / 1000;
            r = -1 * (float)i / 1000;

            sprintf(text, "Prespective -> Two Point");
            outtextxy(20, 20, text);
            sprintf(text, "p : %f \t", p);
            outtextxy(20, 40, text);
            sprintf(text, "q : %f", q);
            outtextxy(20, 60, text);
            sprintf(text, "r : %f", r);
            outtextxy(20, 80, text);

            Matrix prespective = getPrespectiveProjMatrix(p, q, r);
            Matrix requiredMatrix = (*(m)) * T * prespective * T_inv * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            this->convertToHomogenous(requiredMatrixPtr);
            this->drawShape(requiredMatrixPtr);
            delay(1000);
            cleardevice();
        }
    }

    // THREE POINT
    {
        p = q = r = 0;
        sprintf(text, "Prespective -> Three Point");
        outtextxy(20, 20, text);
        sprintf(text, "p : %f \t", 0);
        outtextxy(20, 40, text);
        sprintf(text, "q : %f", 0);
        outtextxy(20, 60, text);
        sprintf(text, "r : %f", 0);
        outtextxy(20, 80, text);

        p = q = r = 0;
        for (int i = 0; i < 10; i++)
        {
            // Grid Lines
            line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
            line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

            p = -1 * (float)i / 1000;
            q = -1 * (float)i / 1000;
            r = -1 * (float)i / 1000;

            sprintf(text, "Prespective -> Three Point");
            outtextxy(20, 20, text);
            sprintf(text, "p : %f \t", p);
            outtextxy(20, 40, text);
            sprintf(text, "q : %f", q);
            outtextxy(20, 60, text);
            sprintf(text, "r : %f", r);
            outtextxy(20, 80, text);

            Matrix prespective = getPrespectiveProjMatrix(p, q, r);
            Matrix requiredMatrix = (*(m)) * T * prespective * T_inv * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            this->convertToHomogenous(requiredMatrixPtr);
            this->drawShape(requiredMatrixPtr);
            delay(1000);
            cleardevice();
        }
    }
}

void Shape::axonometricProjection(Matrix *m)
{
    double pi = 4 * atan(1);
    float *centroid = getCentroid(m);
    this->coOrdinates->display();
    Matrix T = getTranslationMatrix(centroid[0], centroid[1], centroid[2]);
    Matrix T_inv = getTranslationMatrix(-1 * centroid[0], -1 * centroid[1], -1 * centroid[2]);
    Matrix pZ = getProjectionZ();

    // TRIMETRIC
    // TAKING THE EXAMPLE OF ROTAION IN x-axis FOLLOWED BY y-axis
    for (int i = 0; i <= 90; i += 15)
    {
        for (int j = 15; j <= 45; j += 15)
        {
            // Grid Lines
            line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
            line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
            float theta = i * (pi / 180);
            float phi = j * (pi / 180);

            char text[50 + sizeof(char)];
            sprintf(text, "Axonometric -> Trimetric", i);
            outtextxy(20, 20, text);
            sprintf(text, "theta : %d \t", i);
            outtextxy(20, 40, text);
            sprintf(text, "phi : %d", j);
            outtextxy(20, 60, text);

            Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
            Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
            Matrix translate = getTranslationMatrix(centroid[0] / 20, centroid[1] / 20, centroid[2] / 20);
            Matrix requiredMatrix = (*(m)) * T * rotateY * rotateX * T_inv * translate * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            this->drawShape(requiredMatrixPtr);
            delay(1000);
            // system("pause");
            cleardevice();
        }
    }

    // DIMETRIC
    {
        for (int i = 0; i < 9; i++)
        {
            // Grid Lines
            line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
            line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
            float fz = 0.125 * i;
            // cout << fz << "\n";
            float theta = asin(fz / sqrt(2));
            float phi = asin(fz / sqrt(2 - powf(fz, 2)));

            char text[50 + sizeof(char)];
            sprintf(text, "Axonometric -> Dimetric");
            outtextxy(20, 20, text);
            sprintf(text, "theta : %f \t", theta * 180 / pi);
            outtextxy(20, 40, text);
            sprintf(text, "phi : %f", phi * 180 / pi);
            outtextxy(20, 60, text);
            sprintf(text, "fz : %f", fz);
            outtextxy(20, 80, text);

            Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
            Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
            Matrix requiredMatrix = (*(m)) * T * rotateY * rotateX * T_inv * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            this->drawShape(requiredMatrixPtr);
            delay(1000);
            cleardevice();
        }
    }
    // ISOMETRIC
    {
        // Grid Lines
        line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
        line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
        float theta = 35.26 * (pi / 180);
        float phi = -45 * (pi / 180);

        char text[50 + sizeof(char)];
        sprintf(text, "Axonometric -> Isometric");
        outtextxy(20, 20, text);
        sprintf(text, "theta : %f \t", theta * 180 / pi);
        outtextxy(20, 40, text);
        sprintf(text, "phi : %f", phi * 180 / pi);
        outtextxy(20, 60, text);

        Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
        Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
        Matrix requiredMatrix = (*(m)) * T * rotateY * rotateX * T_inv * pZ;
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawShape(requiredMatrixPtr);
        delay(1000);
        cleardevice();
    }
    {
        // Grid Lines
        line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
        line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
        float theta = -35.26 * (pi / 180);
        float phi = -45 * (pi / 180);

        char text[50 + sizeof(char)];
        sprintf(text, "Axonometric -> Isometric");
        outtextxy(20, 20, text);
        sprintf(text, "theta : %f \t", theta * 180 / pi);
        outtextxy(20, 40, text);
        sprintf(text, "phi : %f", phi * 180 / pi);
        outtextxy(20, 60, text);

        Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
        Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
        Matrix requiredMatrix = (*(m)) * T * rotateY * rotateX * T_inv * pZ;
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawShape(requiredMatrixPtr);
        delay(1000);
        cleardevice();
    }
    {
        // Grid Lines
        line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
        line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
        float theta = 35.26 * (pi / 180);
        float phi = 45 * (pi / 180);

        char text[50 + sizeof(char)];
        sprintf(text, "Axonometric -> Isometric");
        outtextxy(20, 20, text);
        sprintf(text, "theta : %f \t", theta * 180 / pi);
        outtextxy(20, 40, text);
        sprintf(text, "phi : %f", phi * 180 / pi);
        outtextxy(20, 60, text);

        Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
        Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
        Matrix requiredMatrix = (*(m)) * T * rotateY * rotateX * T_inv * pZ;
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawShape(requiredMatrixPtr);
        delay(1000);
        cleardevice();
    }
    {
        // Grid Lines
        line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
        line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
        float theta = -35.26 * (pi / 180);
        float phi = 45 * (pi / 180);

        char text[50 + sizeof(char)];
        sprintf(text, "Axonometric -> Isometric");
        outtextxy(20, 20, text);
        sprintf(text, "theta : %f \t", theta * 180 / pi);
        outtextxy(20, 40, text);
        sprintf(text, "phi : %f", phi * 180 / pi);
        outtextxy(20, 60, text);

        Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
        Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
        Matrix requiredMatrix = (*(m)) * T * rotateY * rotateX * T_inv * pZ;
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawShape(requiredMatrixPtr);
        delay(1000);
        cleardevice();
    }
}

void Shape::orthographicProjection(Matrix *m)
{
    double pi = 4 * atan(1);
    float *centroid = getCentroid(m);
    this->coOrdinates->display();
    Matrix T = getTranslationMatrix(centroid[0], centroid[1], centroid[2]);
    Matrix T_inv = getTranslationMatrix(-1 * centroid[0], -1 * centroid[1], -1 * centroid[2]);
    Matrix pZ = getProjectionZ();
    char text[50 + sizeof(char)];

    // FRONT
    sprintf(text, "Orthographic -> FRONT");
    outtextxy(20, 20, text);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
    Matrix Front = (*(m)) * pZ;
    Matrix *requiredMatrixPtr = &Front;
    this->drawShape(requiredMatrixPtr);
    system("pause");
    cleardevice();

    // RIGHT
    // Grid Lines
    sprintf(text, "Orthographic -> RIGHT");
    outtextxy(20, 20, text);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
    float theta = -90 * (pi / 180);
    Matrix rotateY_90 = getRotationMatrixCounterClockwiseY(theta);
    Matrix Right = (*(m)) * T * rotateY_90 * T_inv * pZ;
    requiredMatrixPtr = &Right;
    this->drawShape(requiredMatrixPtr);
    system("pause");
    cleardevice();

    // TOP
    // Grid Lines
    sprintf(text, "Orthographic -> TOP");
    outtextxy(20, 20, text);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
    theta = 90 * (pi / 180);
    Matrix rotateX90 = getRotationMatrixCounterClockwiseX(theta);
    Matrix Top = (*(m)) * T * rotateX90 * T_inv * pZ;
    requiredMatrixPtr = &Top;
    this->drawShape(requiredMatrixPtr);
    system("pause");
    cleardevice();

    // BOTTOM
    // Grid Lines
    sprintf(text, "Orthographic -> BOTTOM");
    outtextxy(20, 20, text);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
    theta = -90 * (pi / 180);
    Matrix rotateX_90 = getRotationMatrixCounterClockwiseX(theta);
    Matrix Bottom = (*(m)) * T * rotateX_90 * T_inv * pZ;
    requiredMatrixPtr = &Bottom;
    this->drawShape(requiredMatrixPtr);
    system("pause");
    cleardevice();

    // REAR
    // Grid Lines
    sprintf(text, "Orthographic -> REAR");
    outtextxy(20, 20, text);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
    theta = 180 * (pi / 180);
    Matrix rotateY180 = getRotationMatrixCounterClockwiseY(theta);
    Matrix Rear = (*(m)) * T * rotateY180 * T_inv * pZ;
    requiredMatrixPtr = &Rear;
    this->drawShape(requiredMatrixPtr);
    system("pause");
    cleardevice();

    // LEFT
    // Grid Lines
    sprintf(text, "Orthographic -> LEFT");
    outtextxy(20, 20, text);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
    theta = 90 * (pi / 180);
    Matrix rotateY90 = getRotationMatrixCounterClockwiseY(theta);
    Matrix Left = (*(m)) * T * rotateY90 * T_inv * pZ;
    requiredMatrixPtr = &Left;
    this->drawShape(requiredMatrixPtr);
    system("pause");
    cleardevice();
}

void Shape ::axisAnimation(Matrix *m)
{
    double pi = 4 * atan(1);
    float *centroid = getCentroid(m);
    this->coOrdinates->display();
    Matrix T = getTranslationMatrix(centroid[0], centroid[1], centroid[2]);
    Matrix T_inv = getTranslationMatrix(-1 * centroid[0], -1 * centroid[1], -1 * centroid[2]);
    Matrix pZ = getProjectionZ();
    char text[50 + sizeof(char)];

    // X - AXIS
    for (int i = 0; i < 360; i++)
    {
        // Grid Lines
        line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
        line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
        float theta = i * (pi / 180);
        sprintf(text, "x-axis");
        outtextxy(20, 20, text);
        sprintf(text, "%d", i);
        outtextxy(20, 40, text);

        Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
        Matrix Top = (*(m)) * T * rotateX * T_inv * pZ;
        Matrix *requiredMatrixPtr = &Top;
        this->drawShape(requiredMatrixPtr);
        delay(10);
        cleardevice();
    }

    // Y - AXIS
    for (int i = 0; i < 360; i++)
    {
        // Grid Lines
        line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
        line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
        float theta = i * (pi / 180);
        sprintf(text, "y-axis");
        outtextxy(20, 20, text);
        sprintf(text, "%d", i);
        outtextxy(20, 40, text);

        Matrix rotateY = getRotationMatrixCounterClockwiseY(theta);
        Matrix Right = (*(m)) * T * rotateY * T_inv * pZ;
        Matrix *requiredMatrixPtr = &Right;
        this->drawShape(requiredMatrixPtr);
        delay(10);
        cleardevice();
    }

    // Z - AXIS
    for (int i = 0; i < 360; i++)
    {
        // Grid Lines
        line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
        line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
        float theta = i * (pi / 180);
        sprintf(text, "z-axis");
        outtextxy(20, 20, text);
        sprintf(text, "%d", i);
        outtextxy(20, 40, text);

        Matrix rotateZ = getRotationMatrixCounterClockwiseZ(theta);
        Matrix requiredMatrix = (*(m)) * T * rotateZ * T_inv * (pZ);
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawShape(requiredMatrixPtr);
        delay(10);
        cleardevice();
    }
}

float *Shape ::getCentroid(Matrix *coOrdinates)
{
    float centroidX = 0;
    float centroidY = 0;
    float centroidZ = 0;

    double thetaPoly[numberOfCoOrdinates];

    for (int i = 0; i < numberOfCoOrdinates; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            if (j == 0)
            {
                centroidX += coOrdinates->m[i][j];
            }
            else if (j == 1)
            {
                centroidY += coOrdinates->m[i][j];
            }
            else if (j == 2)
            {
                centroidZ += coOrdinates->m[i][j];
            }
        }
    }

    centroidX /= numberOfCoOrdinates;
    centroidY /= numberOfCoOrdinates;
    centroidZ /= numberOfCoOrdinates;

    static float centroid[3];
    centroid[0] = centroidX;
    centroid[1] = centroidY;
    centroid[2] = centroidZ;
    return centroid;
}

// To show Scaling Demonstration
void Shape::scaling()
{
    cout << "SCALING\n"
         << "1. Uniform Scaling \n"
         << "2. Non-Uniform Scaling \n"
         << "Enter Option : ";
    int option;
    cin >> option;
    float scaleFactorX = 1;
    float scaleFactorY = 1;
    float scaleFactorZ = 1;
    switch (option)
    {
    case 1:
    {
        cout << "Enter Scale : ";
        cin >> scaleFactorX;
        scaleFactorY = scaleFactorX;
        scaleFactorZ = scaleFactorX;
    }
    break;
    case 2:
    {
        cout << "Enter Scale Factor in x-direction : ";
        cin >> scaleFactorX;
        cout << "Enter Scale Factor in y-direction : ";
        cin >> scaleFactorY;
        cout << "Enter Scale Factor in z-direction : ";
        cin >> scaleFactorZ;
    }
    break;
    default:
    {
        cout << "INVALID\n";
    }
        return;
    }
    // original Figure
    // this->orthographicProjection(this->coOrdinates);
    // scaled figure
    Matrix scaleMatrix = getScaleMatrix(scaleFactorX, scaleFactorY, scaleFactorZ);
    Matrix requiredMatrix = (*(this->coOrdinates)) * (scaleMatrix);
    Matrix *requiredMatrixPtr = &requiredMatrix;
    this->orthographicProjection(requiredMatrixPtr);
    requiredMatrixPtr = NULL;
}

// To show Reflection Demonstration
// void Shape ::reflection()
// {
//     cout << "REFLECTION \n"
//          << "1. about x-axis \n"
//          << "2. about y-axis \n"
//          << "3. about origin \n"
//          << "4. about x = y \n"
//          << "5. about x = -y \n"
//          << "6. about an arbitary line\n"
//          << "Enter Option : ";
//     int option;
//     cin >> option;
//     switch (option)
//     {
//     case 1:
//     {
//         Matrix reflectionMatrix = getReflectionMatrixAboutX();
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (reflectionMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 2:
//     {
//         Matrix reflectionMatrix = getReflectionMatrixAboutY();
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (reflectionMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 3:
//     {
//         Matrix reflectionMatrix = getReflectionMatrixAboutOrigin();
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (reflectionMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 4:
//     {
//         Matrix reflectionMatrix = getReflectionMatrixAboutXY();
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (reflectionMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 5:
//     {
//         Matrix reflectionMatrix = getReflectionMatrixAboutX_Y();
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (reflectionMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 6:
//     {
//         cout << "Enter Equation of Line in this form : F(x,y) = Ax + By + C = 0 \n";
//         float A = 0;
//         float B = 0;
//         float C = 0;
//         cout << "A : ";
//         cin >> A;
//         cout << "B : ";
//         cin >> B;
//         cout << "C : ";
//         cin >> C;

//         // About x-axis with some translation
//         if ((A != 0) && (B == 0) && (C != 0))
//         {
//             // Line about which the reflection will be performed
//             Matrix *reflectionLine = new Matrix(2, 3);
//             reflectionLine->m[0][0] = 0;
//             reflectionLine->m[0][1] = getmaxy();
//             reflectionLine->m[0][2] = 1;
//             reflectionLine->m[1][0] = 0;
//             reflectionLine->m[1][1] = -getmaxy();
//             reflectionLine->m[1][2] = 1;

//             // Drawing the Reflection Line
//             Matrix translationMatrix = getTranslationMatrix(C, 0);
//             Matrix requiredLineMatrix = (*reflectionLine) * translationMatrix;
//             Matrix *requiredLineMatrixPtr = &requiredLineMatrix;
//             this->drawShape(requiredLineMatrixPtr);
//             requiredLineMatrixPtr = NULL;
//             delete reflectionLine;

//             // Drawing the Reflected Figure
//             Matrix reflectionMatrix = getReflectionMatrixAboutY();
//             Matrix requiredMatrix = (*(this->coOrdinates)) * reflectionMatrix * translationMatrix;
//             Matrix *requiredMatrixPtr = &requiredMatrix;
//             this->drawShape(requiredMatrixPtr);
//             requiredMatrixPtr = NULL;
//         }
//         // About y-axis with some translation
//         else if ((A == 0) && (B != 0) && (C != 0))
//         {
//             // Line about which the reflection will be performed
//             Matrix *reflectionLine = new Matrix(2, 3);
//             reflectionLine->m[0][0] = getmaxx();
//             reflectionLine->m[0][1] = 0;
//             reflectionLine->m[0][2] = 1;
//             reflectionLine->m[1][0] = -getmaxx();
//             reflectionLine->m[1][1] = 0;
//             reflectionLine->m[1][2] = 1;

//             // Drawing the Reflection Line
//             Matrix translationMatrix = getTranslationMatrix(0, C);
//             Matrix requiredLineMatrix = (*reflectionLine) * translationMatrix;
//             requiredLineMatrix.display();
//             Matrix *requiredLineMatrixPtr = &requiredLineMatrix;
//             this->drawShape(requiredLineMatrixPtr);
//             requiredLineMatrixPtr = NULL;
//             delete reflectionLine;

//             // Drawing the Reflected Figure
//             Matrix reflectionMatrix = getReflectionMatrixAboutX();
//             Matrix requiredMatrix = (*(this->coOrdinates)) * reflectionMatrix * translationMatrix;
//             Matrix *requiredMatrixPtr = &requiredMatrix;
//             this->drawShape(requiredMatrixPtr);
//             requiredMatrixPtr = NULL;
//         }
//         else
//         {
//             // Arbitary Line Parameters
//             float slope = (-A) / (B);
//             float y_intercept = (-C) / (B);
//             float x_intercept = (-C) / (A);
//             float theta = atan(slope);
//             cout << "Slope : " << slope << "\n";
//             cout << "x_intercept : " << x_intercept << "\n";
//             cout << "y_intercept : " << y_intercept << "\n";
//             cout << "theta : " << theta << "\n";

//             // Drawing the Reflection Line
//             float x1 = getmaxx();
//             float y1 = slope * x1 + y_intercept;
//             float y2 = getmaxy();
//             float x2 = (y2 - y_intercept) / slope;
//             float x3 = -1 * getmaxx();
//             float y3 = slope * x3 + y_intercept;
//             float y4 = -1 * getmaxy();
//             float x4 = (y4 - y_intercept) / slope;
//             Matrix *reflectionLine = new Matrix(4, 3);
//             reflectionLine->m[0][0] = x1;
//             reflectionLine->m[0][1] = y1;
//             reflectionLine->m[1][0] = x2;
//             reflectionLine->m[1][1] = y2;
//             reflectionLine->m[2][0] = x3;
//             reflectionLine->m[2][1] = y3;
//             reflectionLine->m[3][0] = x4;
//             reflectionLine->m[3][1] = y4;
//             this->drawShape(reflectionLine);
//             delete reflectionLine;

//             // Translate the line to Origin
//             Matrix translateMat = getTranslationMatrix(0, y_intercept);
//             // Rotate the line to coincide with x-axis
//             Matrix rotationMatrix = getRotationMatrixClockwise(theta);
//             // Reflection about x-axis
//             Matrix reflectionMatrix = getReflectionMatrixAboutX();
//             // Rotate the line to coincide with x-axis
//             Matrix rotationMatrixInverse = rotationMatrix.transpose();
//             // Re-translate to original point
//             Matrix translateMatInverse = getTranslationMatrix(0, -y_intercept);
//             // Composition Matrix
//             Matrix compositionMatrix = translateMat * rotationMatrix * reflectionMatrix * rotationMatrixInverse * translateMatInverse;
//             Matrix requiredMatrix = (*(this->coOrdinates)) * (compositionMatrix);
//             Matrix *requiredMatrixPtr = &requiredMatrix;
//             this->drawShape(requiredMatrixPtr);
//             requiredMatrixPtr = NULL;
//         }
//     }
//     break;
//     default:
//     {
//         cout << "INVALID\n";
//     }
//         return;
//     }
// }

// // To show Shearing Demonstration
// void Shape ::shearing()
// {
//     cout << "SHEARING \n"
//          << "1. about x-component \n"
//          << "2. about y-component \n"
//          << "3. about both x-component and y-component \n"
//          << "Enter Option : ";
//     float shearingX = 1;
//     float shearingY = 1;
//     int option;
//     cin >> option;
//     switch (option)
//     {
//     case 1:
//     {
//         cout << "Enter Shearing Factor : ";
//         cin >> shearingX;
//         Matrix shearingMatrix = getShearingMatrix(shearingX, 0);
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (shearingMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 2:
//     {
//         cout << "Enter Shearing Factor : ";
//         cin >> shearingY;
//         Matrix shearingMatrix = getShearingMatrix(0, shearingY);
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (shearingMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 3:
//     {
//         cout << "Enter Shearing Factor x-component : ";
//         cin >> shearingX;
//         cout << "Enter Shearing Factor y-component : ";
//         cin >> shearingY;
//         Matrix shearingMatrix = getShearingMatrix(shearingX, shearingY);
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (shearingMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     default:
//     {
//         cout << "INVALID\n";
//     }
//         return;
//     }
// }

// // To show Rotation Demonstration
// void Shape ::rotation()
// {
//     cout << "ROTATION \n"
//          << "1. Counter Clockwise about Origin \n"
//          << "2. Clockwise about Origin \n"
//          << "3. Counter Clockwise about an arbitary point\n"
//          << "4. Clockwise about an arbitary point\n"
//          << "Enter Option : ";
//     int option;
//     cin >> option;
//     double pi = 4 * atan(1);
//     float theta = 0;
//     switch (option)
//     {
//     case 1:
//     {
//         cout << "Enter Angle : ";
//         cin >> theta;
//         theta *= (pi / 180);
//         Matrix rotationMatrix = getRotationMatrixCounterClockwise(theta);
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (rotationMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 2:
//     {
//         cout << "Enter Angle : ";
//         cin >> theta;
//         theta *= (pi / 180);
//         Matrix rotationMatrix = getRotationMatrixClockwise(theta);
//         Matrix requiredMatrix = (*(this->coOrdinates)) * (rotationMatrix);
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 3:
//     {
//         cout << "Enter Angle : ";
//         cin >> theta;
//         theta *= (pi / 180);
//         float x, y;
//         cout << "Enter Co-Ordinates of the Points \n";
//         cout << "x : ";
//         cin >> x;
//         cout << "y : ";
//         cin >> y;
//         // Plotting the arbitary Co-Ordinate
//         putpixel((x + (getmaxx() / 2)), ((-1 * y) + (getmaxy() / 2)), 3);
//         Matrix T = getTranslationMatrix(x, y);
//         Matrix R = getRotationMatrixCounterClockwise(theta);
//         Matrix T_inverse = getTranslationMatrix(-x, -y);
//         Matrix requiredMatrix = (*(this->coOrdinates)) * T * R * T_inverse;
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;
//     case 4:
//     {
//         cout << "Enter Angle : ";
//         cin >> theta;
//         theta *= (pi / 180);
//         int x, y;
//         cout << "Enter Co-Ordinates of the Points \n";
//         cout << "x : ";
//         cin >> x;
//         cout << "y : ";
//         cin >> y;
//         // Plotting the arbitary Co-Ordinate
//         putpixel((x + (getmaxx() / 2)), ((-1 * y) + (getmaxy() / 2)), 3);
//         Matrix T = getTranslationMatrix(x, y);
//         Matrix R = getRotationMatrixClockwise(theta);
//         Matrix T_inverse = getTranslationMatrix(-x, -y);
//         Matrix requiredMatrix = (*(this->coOrdinates)) * T * R * T_inverse;
//         Matrix *requiredMatrixPtr = &requiredMatrix;
//         cout << requiredMatrixPtr << "\n";
//         this->drawShape(requiredMatrixPtr);
//         requiredMatrixPtr = NULL;
//     }
//     break;

//     default:
//     {
//         cout << "INVALID\n";
//     }
//         return;
//     }
// }

// // To show Translation Demonstration
// void Shape::translation()
// {
//     cout << "TRANSLATION \n";
//     float xFactor = 0;
//     float yFactor = 0;
//     cout << "Translate x co-ordinate by : ";
//     cin >> xFactor;
//     cout << "Translate y co-ordinate by : ";
//     cin >> yFactor;
//     Matrix translationMatrix = getTranslationMatrix(xFactor, yFactor);
//     Matrix requiredMatrix = (*(this->coOrdinates)) * (translationMatrix);
//     Matrix *requiredMatrixPtr = &requiredMatrix;
//     this->drawShape(requiredMatrixPtr);
//     requiredMatrixPtr = NULL;
// }

// // To show Translation Demonstration
// void Shape ::transformationMatrix()
// {
//     Matrix transformationMat(3, 3);
//     int option = 0;
//     cout << "Choose Option\n"
//          << "1. 2x2 Matrix\n"
//          << "2. 3x3 Matrix\n"
//          << " : ";
//     cin >> option;
//     switch (option)
//     {
//     case 1:
//         for (int i = 0; i < 2; i++)
//         {
//             for (int j = 0; j < 2; j++)
//             {
//                 cout << "(" << (i + 1) << " , " << (j + 1) << ") : ";
//                 cin >> transformationMat.m[i][j];
//             }
//         }
//         break;
//     case 2:
//         for (int i = 0; i < 3; i++)
//         {
//             for (int j = 0; j < 3; j++)
//             {
//                 cout << "(" << (i + 1) << " , " << (j + 1) << ") : ";
//                 cin >> transformationMat.m[i][j];
//             }
//         }

//         break;
//     default:
//         cout << "INVALID\n";
//         return;
//     }
//     cout << "Transformation Matrix : \n";
//     transformationMat.display();
//     cout << "\n";
//     Matrix requiredMatrix = (*(this->coOrdinates)) * (transformationMat);
//     Matrix *requiredMatrixPtr = &requiredMatrix;
//     this->drawShape(requiredMatrixPtr);
//     requiredMatrixPtr = NULL;
// }
