#include <iostream>
#include <math.h>
#include <graphics.h>
#include "matrix.h"
using namespace std;

void drawLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float pi = 4 * atanf(1);
    float theta = 15 * (pi / 180);
    float phi = 30 * (pi / 180);

    Matrix *Lines = new Matrix(2, 4);
    Lines->m[0][0] = x1;
    Lines->m[0][1] = y2;
    Lines->m[0][2] = z1;

    Lines->m[1][0] = x2;
    Lines->m[1][1] = y2;
    Lines->m[1][2] = z2;
    Lines->display();

    Matrix pZ = getProjectionZ();

    Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
    Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
    Matrix requiredMatrix = (*(Lines)) * rotateY * rotateX * pZ;
    requiredMatrix.display();

    line(requiredMatrix.m[0][0] + getmaxx() / 2, -1 * requiredMatrix.m[0][1] + getmaxy() / 2, requiredMatrix.m[1][0] + (getmaxx() / 2), -1 * requiredMatrix.m[1][1] + (getmaxy() / 2));

    delete Lines;
}

void drawAxis(float theta = 15 * (3.14159265359 / 180), float phi = 30 * (3.14159265359 / 180))
{
    // line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    // line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
    float pi = 4 * atanf(1);
    // float theta = 15 * (pi / 180);
    // float phi = 30 * (pi / 180);
    Matrix *Lines = new Matrix(6, 4);
    Lines->m[0][0] = 2000;
    Lines->m[0][1] = 0;
    Lines->m[0][2] = 0;

    Lines->m[1][0] = 0;
    Lines->m[1][1] = 2000;
    Lines->m[1][2] = 0;

    Lines->m[2][0] = 0;
    Lines->m[2][1] = 0;
    Lines->m[2][2] = 2000;

    Lines->m[3][0] = -2000,
    Lines->m[3][1] = 0;
    Lines->m[3][2] = 0;

    Lines->m[4][0] = 0;
    Lines->m[4][1] = -2000;
    Lines->m[4][2] = 0;

    Lines->m[5][0] = 0,
    Lines->m[5][1] = 0;
    Lines->m[5][2] = -2000;

    Matrix pZ = getProjectionZ();

    Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
    Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
    Matrix requiredMatrix = (*(Lines)) * rotateY * rotateX * pZ;
    // requiredMatrix.display();
    for (int i = 0; i < Lines->r; i++)
    {
        line(getmaxx() / 2, getmaxy() / 2, requiredMatrix.m[i][0] + (getmaxx() / 2), -1 * requiredMatrix.m[i][1] + (getmaxy() / 2));
    }

    delete Lines;
}

// Shape Class
class Shape
{

public:
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
    void scaling();
    void reflection();
    void shearing();
    void rotation();
    void translation();
    void transformationMatrix();
    void animation();
    void projectionDemo();

private:
    // Data Memebers
    Matrix *coOrdinates;
    int numberOfCoOrdinates = 0;
    int numberOfFaces = 0;
    Matrix *faces;
    // Member Functions
    void drawShape(Matrix *coOrdinates);
    void convertToHomogenous(Matrix *coOrdinates);
    float *getCentroid(Matrix *coOrdinates);
    void drawOrthographicProjection(Matrix *coOrdinates, float theta, float phi, float ita, char *heading);
    void orthographicProjection(Matrix *coOrdinates);
    void drawAxonometricProjection(Matrix *coOrdinates, float theta, float phi, char *heading);
    void axonometricProjection(Matrix *coOrdinates);
    void drawPrespectiveProjection(Matrix *coOrdinates, float p, float q, float r, char *heading);
    void prespectiveProjection(Matrix *coOrdinates);
    void axisAnimation(Matrix *coOrdinates);
};

// To Draw the Polygon whose Co-Ordinate are passes as in Homogenous Matrix as a "matrix" object
void Shape::drawShape(Matrix *matrix)
{
    float **coOrdinates = matrix->m;
    int numberOfCoOrdinates = matrix->r;

    if (numberOfCoOrdinates != this->numberOfCoOrdinates)
    {
        cout << "BAD \n";
        return;
    }

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

// Convert the Co-Ordinates to Homogenous Co-Ordinates of a Matrix Object
void Shape::convertToHomogenous(Matrix *matrix)
{
    for (int i = 0; i < matrix->r; i++)
    {
        matrix->m[i][0] /= matrix->m[i][3];
        matrix->m[i][1] /= matrix->m[i][3];
        matrix->m[i][3] = 1;
    }
}

// Get Centroid of an Matrix Object
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
    // cout << centroidX << "\t" << centroidY << "\t" << centroidZ << "\n";
    static float centroid[3];
    centroid[0] = centroidX;
    centroid[1] = centroidY;
    centroid[2] = centroidZ;

    return centroid;
}

// ORTHOGRAPHIC PROJECTION
// =============================================================
void Shape ::drawOrthographicProjection(Matrix *m, float theta, float phi, float ita, char *heading)
{
    double pi = 4 * atan(1);
    float *centroid = getCentroid(m);
    Matrix T = getTranslationMatrix(centroid[0], centroid[1], centroid[2]);
    Matrix T_inv = getTranslationMatrix(-1 * centroid[0], -1 * centroid[1], -1 * centroid[2]);
    Matrix pZ = getProjectionZ();

    Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
    Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
    Matrix rotateZ = getRotationMatrixCounterClockwiseZ(ita);

    drawAxis(0, 0);
    outtextxy(20, 20, heading);

    Matrix face = (*(m)) * T * rotateX * rotateY * rotateZ * T_inv * pZ;
    Matrix *requiredMatrixPtr = &face;
    this->drawShape(requiredMatrixPtr);
}

void Shape::orthographicProjection(Matrix *m)
{
    double pi = 4 * atan(1);
    char text[50 + sizeof(char)];
    float theta = 0;
    float phi = 0;
    float ita = 0;

    // FRONT
    sprintf(text, "Orthographic -> FRONT");
    drawOrthographicProjection(m, theta, phi, ita, text);
    delay(1000);
    cleardevice();

    // RIGHT
    theta = phi = ita = 0;
    sprintf(text, "Orthographic -> RIGHT");
    phi = -90 * (pi / 180);
    drawOrthographicProjection(m, theta, phi, ita, text);
    delay(1000);
    cleardevice();

    // TOP
    theta = phi = ita = 0;
    sprintf(text, "Orthographic -> TOP");
    theta = 90 * (pi / 180);
    drawOrthographicProjection(m, theta, phi, ita, text);
    delay(1000);
    cleardevice();

    // BOTTOM
    theta = phi = ita = 0;
    sprintf(text, "Orthographic -> BOTTOM");
    theta = -90 * (pi / 180);
    drawOrthographicProjection(m, theta, phi, ita, text);
    delay(1000);
    cleardevice();

    // REAR
    theta = phi = ita = 0;
    sprintf(text, "Orthographic -> REAR");
    phi = 180 * (pi / 180);
    drawOrthographicProjection(m, theta, phi, ita, text);
    delay(1000);
    cleardevice();

    // LEFT
    theta = phi = ita = 0;
    sprintf(text, "Orthographic -> LEFT");
    phi = 90 * (pi / 180);
    drawOrthographicProjection(m, theta, phi, ita, text);
    delay(1000);
    cleardevice();
}
// =============================================================

// AXONOMETRIC PROJECTION
// =============================================================
void Shape::drawAxonometricProjection(Matrix *m, float theta, float phi, char *heading)
{
    double pi = 4 * atanf(1);
    float *centroid = getCentroid(m);
    Matrix pZ = getProjectionZ();
    char text[50 + sizeof(char)];

    outtextxy(20, 20, heading);
    sprintf(text, "theta : %d \t", (int)(theta * 180 / pi));
    outtextxy(20, 40, text);
    sprintf(text, "phi : %d", (int)(phi * 180 / pi));
    outtextxy(20, 60, text);

    Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
    Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
    Matrix requiredMatrix = (*(m)) * rotateY * rotateX * pZ;
    Matrix *requiredMatrixPtr = &requiredMatrix;
    this->drawShape(requiredMatrixPtr);
    // requiredMatrix.display();
}

void Shape::axonometricProjection(Matrix *m)
{
    double pi = 4 * atan(1);
    char text[50 + sizeof(char)];
    float theta = 0;
    float phi = 0;

    // TRIMETRIC
    // TAKING THE EXAMPLE OF ROTAION IN y-axis FOLLOWED BY x-axis
    sprintf(text, "Axonometric -> Trimetric");
    for (int i = 0; i <= 90; i += 15)
    {
        for (int j = 15; j <= 45; j += 15)
        {
            // Grid Lines
            theta = i * (pi / 180);
            phi = j * (pi / 180);
            drawAxis(theta, phi);
            drawAxonometricProjection(m, theta, phi, text);
            delay(1000);
            // system("pause");
            cleardevice();
        }
    }

    // DIMETRIC
    {
        float fz = 0;
        for (int i = 0; i < 9; i++)
        {
            sprintf(text, "Axonometric -> Dimetric");
            fz = 0.125 * i;
            theta = asin(fz / sqrt(2));
            phi = asin(fz / sqrt(2 - powf(fz, 2)));
            drawAxis(theta, phi);
            drawAxonometricProjection(m, theta, phi, text);
            sprintf(text, "fz : %f", fz);
            outtextxy(20, 80, text);
            delay(1000);
            cleardevice();
        }
    }
    // ISOMETRIC
    {
        sprintf(text, "Axonometric -> Isometric");

        // (35.26, -45)
        theta = 35.26 * (pi / 180);
        phi = -45 * (pi / 180);
        drawAxis(theta, phi);
        drawAxonometricProjection(m, theta, phi, text);
        delay(1000);
        cleardevice();

        // (-35.26, -45)
        theta = -35.26 * (pi / 180);
        phi = -45 * (pi / 180);
        drawAxis(theta, phi);
        drawAxonometricProjection(m, theta, phi, text);
        delay(1000);
        cleardevice();

        // (35.26, 45)
        theta = 35.26 * (pi / 180);
        phi = 45 * (pi / 180);
        drawAxis(theta, phi);
        drawAxonometricProjection(m, theta, phi, text);
        delay(1000);
        cleardevice();

        // (-35.26, 45)
        theta = -35.26 * (pi / 180);
        phi = 45 * (pi / 180);
        drawAxis(theta, phi);
        drawAxonometricProjection(m, theta, phi, text);
        delay(1000);
        cleardevice();
    }
}

// =============================================================

// PRESPECTIVE PROJECTION
// =============================================================
void Shape::drawPrespectiveProjection(Matrix *m, float p, float q, float r, char *heading)
{
    float *centroid = getCentroid(m);
    Matrix T = getTranslationMatrix(centroid[0], centroid[1], centroid[2]);
    Matrix T_inv = getTranslationMatrix(-1 * centroid[0], -1 * centroid[1], -1 * centroid[2]);
    Matrix pZ = getProjectionZ();
    char text[50 + sizeof(char)];

    sprintf(text, "Prespective -> Single Point");
    outtextxy(20, 20, heading);
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
}

void Shape ::prespectiveProjection(Matrix *m)
{
    char text[50 + sizeof(char)];
    float p = 0;
    float q = 0;
    float r = 0;

    // SINGLE POINT
    sprintf(text, "Prespective -> Single Point");
    {
        // z -axis
        for (int i = 0; i < 10; i++)
        {
            drawAxis(0, 0);
            r = -1 * (float)i / 1000;
            this->drawPrespectiveProjection(m, p, q, r, text);
            delay(1000);
            cleardevice();
        }

        // y
        p = q = r = 0;
        for (int i = 0; i < 10; i++)
        {
            drawAxis(0, 0);

            q = -1 * (float)i / 1000;
            this->drawPrespectiveProjection(m, p, q, r, text);
            delay(1000);
            cleardevice();
        }

        // x
        p = q = r = 0;
        for (int i = 0; i < 10; i++)
        {
            drawAxis();
            p = -1 * (float)i / 1000;
            this->drawPrespectiveProjection(m, p, q, r, text);
            delay(1000);
            cleardevice();
        }
    }

    // TWO POINT
    sprintf(text, "Prespective -> Two Point");
    {
        // xy
        p = q = r = 0;
        for (int i = 0; i < 10; i++)
        {
            drawAxis(0, 0);
            p = -1 * (float)i / 1000;
            q = -1 * (float)i / 1000;
            this->drawPrespectiveProjection(m, p, q, r, text);
            delay(1000);
            cleardevice();
        }

        // xz
        p = q = r = 0;
        for (int i = 0; i < 10; i++)
        {
            drawAxis(0, 0);
            p = -1 * (float)i / 1000;
            r = -1 * (float)i / 1000;
            this->drawPrespectiveProjection(m, p, q, r, text);
            delay(1000);
            cleardevice();
        }

        // yz
        p = q = r = 0;
        for (int i = 0; i < 10; i++)
        {
            drawAxis(0, 0);
            q = -1 * (float)i / 1000;
            r = -1 * (float)i / 1000;
            this->drawPrespectiveProjection(m, p, q, r, text);
            delay(1000);
            cleardevice();
        }
    }

    // THREE POINT
    sprintf(text, "Prespective -> Three Point");
    {
        p = q = r = 0;

        for (int i = 0; i < 10; i++)
        {
            drawAxis(0, 0);
            p = -1 * (float)i / 1000;
            q = -1 * (float)i / 1000;
            r = -1 * (float)i / 1000;
            this->drawPrespectiveProjection(m, p, q, r, text);
            delay(1000);
            cleardevice();
        }
    }
}
// =============================================================

// PROJECTION DEMO
// =============================================================
void Shape ::projectionDemo()
{
    this->axisAnimation(this->coOrdinates);
    this->axonometricProjection(this->coOrdinates);
    this->orthographicProjection(this->coOrdinates);
    this->prespectiveProjection(this->coOrdinates);
}
// =============================================================

// AXIS ANIMATION
// =============================================================
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
        drawAxis(theta, 0);

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

        drawAxis(0, theta);

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

        drawAxis(0, 0);

        Matrix rotateZ = getRotationMatrixCounterClockwiseZ(theta);
        Matrix requiredMatrix = (*(m)) * T * rotateZ * T_inv * (pZ);
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawShape(requiredMatrixPtr);
        delay(10);
        cleardevice();
    }
}
// =============================================================

// OBJECT ANIMATION
// =============================================================
void Shape ::animation()
{
    double pi = 4 * atan(1);
    float *centroid = this->getCentroid(this->coOrdinates);
    Matrix T = getTranslationMatrix(centroid[0], centroid[1], centroid[2]);
    Matrix T_inv = getTranslationMatrix(-1 * centroid[0], -1 * centroid[1], -1 * centroid[2]);
    Matrix pZ = getProjectionZ();
    char text[50 + sizeof(char)];
    cout << "Rotating Object Translated to Origin uniformly Scaled by a factor of 2.5\n";

    int i = 0;
    while (i != 720)
    {
        float theta = i * (pi / 180);
        float phi = -0.25 * i * (pi / 180);
        float ita = 0.25 * i * (pi / 180);
        float threeSixty = 360;

        sprintf(text, "Rotation Angles");
        outtextxy(20, 20, text);
        // drawAxis(theta, phi);
        sprintf(text, "theta : %f \t", fmod((theta * 180 / pi), threeSixty));
        outtextxy(20, 40, text);
        sprintf(text, "phi : %f", fmod((phi * 180 / pi), threeSixty));
        outtextxy(20, 60, text);
        sprintf(text, "ita : %f", fmod((ita * 180 / pi), threeSixty));
        outtextxy(20, 80, text);

        Matrix rotateY = getRotationMatrixCounterClockwiseY(theta);
        Matrix rotateX = getRotationMatrixCounterClockwiseX(phi);
        Matrix rotateZ = getRotationMatrixCounterClockwiseX(ita);
        Matrix scaleMatrix = getScaleMatrix(2.5, 2.5, 2.5);
        Matrix requiredMatrix = (*(this->coOrdinates)) * T * rotateX * rotateY * rotateZ * scaleMatrix * pZ;
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawShape(requiredMatrixPtr);
        delay(10);
        cleardevice();
        i++;
    }
}
// =============================================================

// TRANSFORMATION DEMONSTRATION

// To show Scaling Demonstration
void Shape::scaling()
{
    double pi = 4 * atan(1);
    float theta = 15 * (pi / 180);
    float phi = 30 * (pi / 180);
    char heading[] = "";
    drawAxis();
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
    Matrix scaleMatrix = getScaleMatrix(scaleFactorX, scaleFactorY, scaleFactorZ);
    Matrix requiredMatrix = (*(this->coOrdinates)) * (scaleMatrix);
    Matrix *requiredMatrixPtr = &requiredMatrix;
    // original figure
    this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
    // scaled figure
    this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
    requiredMatrixPtr = NULL;
}

// To show Reflection Demonstration
void Shape ::reflection()
{
    Matrix pZ = getProjectionZ();
    double pi = 4 * atan(1);
    float theta = 15 * (pi / 180);
    float phi = 30 * (pi / 180);
    // drawAxis(theta, phi);
    char heading[] = "";

    cout << "REFLECTION \n"
         << "1. about xy-plane \n"
         << "2. about yz-plane \n"
         << "3. about xz-plane \n"
         //  << "4. about arbitary plane \n"
         << "Enter Option : ";
    int option;
    cin >> option;
    switch (option)
    {
    case 1:
    {
        for (int i = 0; i <= 90; i += 15)
        {
            for (int j = 0; j <= 45; j += 15)
            {
                // Grid Lines
                theta = i * (pi / 180);
                phi = j * (pi / 180);
                drawAxis(theta, phi);
                Matrix reflectionMatrix = getReflectionMatrixAboutXYPlane();
                Matrix requiredMatrix = (*(this->coOrdinates)) * reflectionMatrix;
                Matrix *requiredMatrixPtr = &requiredMatrix;
                this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
                this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
                system("pause");
                cleardevice();
                requiredMatrixPtr = NULL;
            }
        }
    }
    break;
    case 2:
    {
        for (int i = 0; i <= 90; i += 15)
        {
            for (int j = 0; j <= 45; j += 15)
            {
                // Grid Lines
                theta = i * (pi / 180);
                phi = j * (pi / 180);
                drawAxis(theta, phi);
                Matrix reflectionMatrix = getReflectionMatrixAboutYZPlane();
                Matrix requiredMatrix = (*(this->coOrdinates)) * reflectionMatrix;
                Matrix *requiredMatrixPtr = &requiredMatrix;
                this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
                this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
                system("pause");
                cleardevice();
                requiredMatrixPtr = NULL;
            }
        }
    }
    break;
    case 3:
    {
        for (int i = 0; i <= 90; i += 15)
        {
            for (int j = 0; j <= 45; j += 15)
            {
                // Grid Lines
                theta = i * (pi / 180);
                phi = j * (pi / 180);
                drawAxis(theta, phi);
                Matrix reflectionMatrix = getReflectionMatrixAboutXZPlane();
                Matrix requiredMatrix = (*(this->coOrdinates)) * reflectionMatrix;
                Matrix *requiredMatrixPtr = &requiredMatrix;
                this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
                this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
                system("pause");
                cleardevice();
                requiredMatrixPtr = NULL;
            }
        }
    }
    break;
    case 4:
    {
        // ARBITARY PLANE
    }
    break;
    default:
    {
        cout << "INVALID\n";
    }
        return;
    }
    setcolor(15);
    system("pause");
    cleardevice();
}

// To show Shearing Demonstration
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
//         this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
//         setcolor(4);
//         this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
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
//         this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
//         setcolor(4);
//         this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
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
//         this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
//         setcolor(4);
//         this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
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

// To show Rotation Demonstration
void Shape ::rotation()
{
    Matrix pZ = getProjectionZ();
    double pi = 4 * atan(1);
    float theta = 15 * (3.14159265359 / 180);
    float phi = 30 * (3.14159265359 / 180);
    Matrix scaleMatrix = getScaleMatrix(0.5, 0.5, 0.5);
    drawAxis(theta, phi);
    char heading[] = "";

    cout << "ROTATION \n"
         << "1. Counter Clockwise about x-axis \n"
         << "2. Counter Clockwise about y-axis \n"
         << "3. Counter Clockwise about z-axis \n"
         //  << "4. Counter Clockwise about an arbitary axis\n"
         << "Enter Option : ";
    int option;
    cin >> option;
    float ita = 0;
    switch (option)
    {
    case 1:
    {

        cout << "Enter Angle : ";
        cin >> ita;
        ita *= (pi / 180);
        Matrix rotationMatrix = getRotationMatrixCounterClockwiseX(ita);
        Matrix requiredMatrix = (*(this->coOrdinates)) * (rotationMatrix);
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
        this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
        requiredMatrixPtr = NULL;
        system("pause");
        cleardevice();
        drawAxis(theta, phi);
    }
    break;
    case 2:
    {

        cout << "Enter Angle : ";
        cin >> ita;
        ita *= (pi / 180);
        Matrix rotationMatrix = getRotationMatrixCounterClockwiseY(ita);
        Matrix requiredMatrix = (*(this->coOrdinates)) * (rotationMatrix);
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
        this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
        requiredMatrixPtr = NULL;
        system("pause");
        cleardevice();
        drawAxis(theta, phi);
    }
    break;
    case 3:
    {

        ita *= (pi / 180);
        Matrix rotationMatrix = getRotationMatrixCounterClockwiseZ(ita);
        Matrix requiredMatrix = (*(this->coOrdinates)) * (rotationMatrix);
        Matrix *requiredMatrixPtr = &requiredMatrix;
        this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
        this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
        requiredMatrixPtr = NULL;
        system("pause");
        cleardevice();
        drawAxis(theta, phi);
    }
    break;
    case 4:
    {
        // ARBITARY AXIS
    }
    break;
    default:
    {
        cout << "INVALID\n";
    }
        return;
    }
}

// To show Translation Demonstration
void Shape::translation()
{

    Matrix pZ = getProjectionZ();
    double pi = 4 * atan(1);
    float theta = 15 * (pi / 180);
    float phi = 30 * (pi / 180);
    drawAxis(theta, phi);
    char heading[] = "";

    cout << "TRANSLATION \n";
    float xFactor = 0;
    float yFactor = 0;
    float zFactor = 0;
    cout << "Translate x co-ordinate by : ";
    cin >> xFactor;
    cout << "Translate y co-ordinate by : ";
    cin >> yFactor;
    cout << "Translate z co-ordinate by : ";
    cin >> zFactor;
    Matrix translationMatrix = getTranslationMatrix(xFactor, yFactor, zFactor);
    Matrix requiredMatrix = (*(this->coOrdinates)) * (translationMatrix);
    Matrix *requiredMatrixPtr = &requiredMatrix;
    this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
    setcolor(4);
    this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
    requiredMatrixPtr = NULL;
}

// To show Transformation Demonstration
void Shape ::transformationMatrix()
{
    Matrix transformationMat(4, 4);
    Matrix pZ = getProjectionZ();
    double pi = 4 * atan(1);
    float theta = 15 * (pi / 180);
    float phi = 30 * (pi / 180);
    drawAxis(theta, phi);
    char heading[] = "";
    cout << "Enter General 4x4 Transformation Matrix Co-Ordinates\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << "(" << (i + 1) << " , " << (j + 1) << ") : ";
            cin >> transformationMat.m[i][j];
        }
    }
    cout << "Transformation Matrix : \n";
    transformationMat.display();
    cout << "\n";
    Matrix requiredMatrix = (*(this->coOrdinates)) * (transformationMat);
    Matrix *requiredMatrixPtr = &requiredMatrix;
    requiredMatrixPtr->display();
    this->drawAxonometricProjection(this->coOrdinates, theta, phi, heading);
    setcolor(4);
    this->drawAxonometricProjection(requiredMatrixPtr, theta, phi, heading);
    requiredMatrixPtr = NULL;
}
