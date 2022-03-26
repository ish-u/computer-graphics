#include <graphics.h>
#include <graphics.h>
#include <math.h>

using namespace std;
// #include "object.h"
#include "matrix.h"

const double PI = 4 * atanf(1);
;
const float THETA = 0 * (PI / 180);
const float PHI = 0 * (PI / 180);

void drawAxis(float theta = THETA, float phi = PHI)
{
    Matrix *Lines = new Matrix(6, 4);
    Lines->m[0][0] = 2000;
    Lines->m[0][1] = 0;
    Lines->m[0][2] = 0;

    Lines->m[1][0] = -2000,
    Lines->m[1][1] = 0;
    Lines->m[1][2] = 0;

    Lines->m[2][0] = 0;
    Lines->m[2][1] = 2000;
    Lines->m[2][2] = 0;

    Lines->m[3][0] = 0;
    Lines->m[3][1] = -2000;
    Lines->m[3][2] = 0;

    Lines->m[4][0] = 0;
    Lines->m[4][1] = 0;
    Lines->m[4][2] = 2000;

    Lines->m[5][0] = 0,
    Lines->m[5][1] = 0;
    Lines->m[5][2] = -2000;

    Matrix pZ = getProjectionZ();

    Matrix rotateX = getRotationMatrixCounterClockwiseX(theta);
    Matrix rotateY = getRotationMatrixCounterClockwiseY(phi);
    Matrix requiredMatrix = (*(Lines)) * rotateY * rotateX * pZ;
    // requiredMatrix.display();
    int c = 1;
    for (int i = 0; i < Lines->r; i++)
    {
        switch (i)
        {
        case 0:
            setcolor(4);
            break;
        case 2:
            setcolor(2);
            break;
        case 4:
            setcolor(1);
            break;
        default:
            break;
        }
        line(getmaxx() / 2, getmaxy() / 2, requiredMatrix.m[i][0] + (getmaxx() / 2), -1 * requiredMatrix.m[i][1] + (getmaxy() / 2));
    }
    setcolor(15);

    delete Lines;
}

class HermiteCurve
{
private:
    Matrix *geometricMatrix;
    int n;

public:
    // Constructor
    HermiteCurve(int n = 4)
    {
        this->n = n;
        this->geometricMatrix = new Matrix(4, 3, 0);
        // this->geometricMatrix->input();
        this->geometricMatrix->m[0][0] = -300;
        this->geometricMatrix->m[0][1] = -100;
        this->geometricMatrix->m[0][2] = 0;

        this->geometricMatrix->m[1][0] = 400;
        this->geometricMatrix->m[1][1] = 100;
        this->geometricMatrix->m[1][2] = 0;

        this->geometricMatrix->m[2][0] = 0;
        this->geometricMatrix->m[2][1] = -100;
        this->geometricMatrix->m[2][2] = 0;

        this->geometricMatrix->m[3][0] = 0;
        this->geometricMatrix->m[3][1] = 100;
        this->geometricMatrix->m[3][2] = 0;

        this->geometricMatrix->display();
    }
    // Destructor
    ~HermiteCurve()
    {
        delete this->geometricMatrix;
    }
    // display
    void display();
};

void HermiteCurve::display()
{
    // for (int i = 0; i < 500; i += 1)
    // {
    delay(10);
    this->geometricMatrix->m[2][0] += 1;
    this->geometricMatrix->m[3][1] -= 10;
    cleardevice();

    // Hermite Basis and Coefficient Matrix
    Matrix hermiteBasis = getBasisHermiteCurve();
    Matrix coefficientMatrix = hermiteBasis * (*(this->geometricMatrix));

    // Calculating the Co-Ordinates
    Matrix coOrdinates(this->n + 1, 4);
    double d = 1.0 / this->n;
    double t = 0;
    Matrix T(1, 4, 0);
    for (int i = 0; i < this->n + 1; i++)
    {
        T.m[0][0] = t * t * t;
        T.m[0][1] = t * t;
        T.m[0][2] = t;
        T.m[0][3] = 1;

        // T.display();

        Matrix coOrdinate = T * coefficientMatrix;
        coOrdinates.m[i][0] = coOrdinate.m[0][0];
        coOrdinates.m[i][1] = coOrdinate.m[0][1];
        coOrdinates.m[i][2] = coOrdinate.m[0][2];
        coOrdinates.m[i][3] = 1;

        t += d;
    }

    // Axonometric Projection with THETA and PHI
    Matrix pZ = getProjectionZ();
    char text[50 + sizeof(char)] = "";
    // Displaying Angle Information
    outtextxy(20, 20, text);
    sprintf(text, "theta : %d \t", (int)(THETA * 180 / PI));
    outtextxy(20, 40, text);
    sprintf(text, "phi : %d", (int)(PHI * 180 / PI));
    outtextxy(20, 60, text);
    // Axonometric Projection
    Matrix rotateX = getRotationMatrixCounterClockwiseX(THETA);
    Matrix rotateY = getRotationMatrixCounterClockwiseY(PHI);
    Matrix requiredMatrix = coOrdinates * rotateY * rotateX * pZ;

    // display the Axis
    drawAxis();

    // Draw the Curve
    for (int i = 1; i <= this->n; i++)
    {
        // reflect about x-axis
        // transtale to center of window
        line((requiredMatrix.m[i - 1][0]) + getmaxx() / 2, -1 * requiredMatrix.m[i - 1][1] + getmaxy() / 2, (requiredMatrix.m[i][0]) + getmaxx() / 2, -1 * requiredMatrix.m[i][1] + getmaxy() / 2);
    }
    setcolor(3);
    line((this->geometricMatrix->m[0][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[0][1] + getmaxy() / 2, (this->geometricMatrix->m[1][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[1][1] + getmaxy() / 2);
    // line((this->geometricMatrix->m[1][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[1][1] + getmaxy() / 2, (this->geometricMatrix->m[2][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[2][1] + getmaxy() / 2);
    // line((this->geometricMatrix->m[2][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[2][1] + getmaxy() / 2, (this->geometricMatrix->m[3][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[3][1] + getmaxy() / 2);
    // line((this->geometricMatrix->m[3][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[3][1] + getmaxy() / 2, (this->geometricMatrix->m[0][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[0][1] + getmaxy() / 2);
    // }
}

class BezierCurve
{
private:
    Matrix *geometricMatrix;
    int n;

public:
    // Constructor
    BezierCurve(int n = 4)
    {
        this->n = n;
        this->geometricMatrix = new Matrix(4, 3, 0);
        // this->geometricMatrix->input();
        this->geometricMatrix->m[0][0] = 100;
        this->geometricMatrix->m[0][1] = 100;
        this->geometricMatrix->m[0][2] = 0;

        this->geometricMatrix->m[1][0] = 100;
        this->geometricMatrix->m[1][1] = 150;
        this->geometricMatrix->m[1][2] = 0;

        this->geometricMatrix->m[2][0] = 150;
        this->geometricMatrix->m[2][1] = 200;
        this->geometricMatrix->m[2][2] = 0;

        this->geometricMatrix->m[3][0] = 200;
        this->geometricMatrix->m[3][1] = 200;
        this->geometricMatrix->m[3][2] = 0;

        this->geometricMatrix->display();
    }
    // Destructor
    ~BezierCurve()
    {
        delete this->geometricMatrix;
    }
    // display
    void display();
};

void BezierCurve::display()
{
    // for (int i = 0; i < 500; i += 1)
    // {
    //     delay(10);
    //     this->geometricMatrix->m[2][0] += 1;
    //     this->geometricMatrix->m[1][1] -= 1;
    //     cleardevice();

    // Hermite Basis and Coefficient Matrix
    Matrix hermiteBasis = getBasisBezierCurve();
    Matrix coefficientMatrix = hermiteBasis * (*(this->geometricMatrix));

    // Calculating the Co-Ordinates
    Matrix coOrdinates(this->n + 1, 4);
    double d = 1.0 / this->n;
    double t = 0;
    Matrix T(1, 4, 0);
    for (int i = 0; i < this->n + 1; i++)
    {
        T.m[0][0] = t * t * t;
        T.m[0][1] = t * t;
        T.m[0][2] = t;
        T.m[0][3] = 1;

        // T.display();

        Matrix coOrdinate = T * coefficientMatrix;
        coOrdinates.m[i][0] = coOrdinate.m[0][0];
        coOrdinates.m[i][1] = coOrdinate.m[0][1];
        coOrdinates.m[i][2] = coOrdinate.m[0][2];
        coOrdinates.m[i][3] = 1;

        t += d;
    }

    // Axonometric Projection with THETA and PHI
    Matrix pZ = getProjectionZ();
    char text[50 + sizeof(char)] = "";
    // Displaying Angle Information
    outtextxy(20, 20, text);
    sprintf(text, "theta : %d \t", (int)(THETA * 180 / PI));
    outtextxy(20, 40, text);
    sprintf(text, "phi : %d", (int)(PHI * 180 / PI));
    outtextxy(20, 60, text);
    // Axonometric Projection
    Matrix rotateX = getRotationMatrixCounterClockwiseX(THETA);
    Matrix rotateY = getRotationMatrixCounterClockwiseY(PHI);
    Matrix requiredMatrix = coOrdinates * rotateY * rotateX * pZ;

    // display the Axis
    drawAxis();

    // Draw the Curve
    for (int i = 1; i <= this->n; i++)
    {
        // reflect about x-axis
        // transtale to center of window
        line((requiredMatrix.m[i - 1][0]) + getmaxx() / 2, -1 * requiredMatrix.m[i - 1][1] + getmaxy() / 2, (requiredMatrix.m[i][0]) + getmaxx() / 2, -1 * requiredMatrix.m[i][1] + getmaxy() / 2);
    }
    setcolor(3);

    line((this->geometricMatrix->m[0][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[0][1] + getmaxy() / 2, (this->geometricMatrix->m[1][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[1][1] + getmaxy() / 2);
    line((this->geometricMatrix->m[1][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[1][1] + getmaxy() / 2, (this->geometricMatrix->m[2][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[2][1] + getmaxy() / 2);
    line((this->geometricMatrix->m[2][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[2][1] + getmaxy() / 2, (this->geometricMatrix->m[3][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[3][1] + getmaxy() / 2);
    line((this->geometricMatrix->m[3][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[3][1] + getmaxy() / 2, (this->geometricMatrix->m[0][0]) + getmaxx() / 2, -1 * this->geometricMatrix->m[0][1] + getmaxy() / 2);
    // }
}

int main()
{
    int gd = DETECT, gm;
    // initgraph(&gd, &gm, NULL);
    initwindow(1080, 720);

    HermiteCurve *hCurve = new HermiteCurve(100);
    hCurve->display();

    BezierCurve *bCurve = new BezierCurve(100);
    bCurve->display();

    system("pause");
    closegraph();

    delete hCurve;
    delete bCurve;
    cout << Matrix::created << "\t" << Matrix::deleted << "\n";

    return 0;
}