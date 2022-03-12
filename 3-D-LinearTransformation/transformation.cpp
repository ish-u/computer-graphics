#include <iostream>
#include <graphics.h>
#include <math.h>

using namespace std;
#include "shape.h"

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Polygon
    // cout << "Enter the Number of Co-ordinates : ";
    // int coOrdinates = 0;
    // cin >> coOrdinates;
    // Shape *shape = new Shape(coOrdinates);
    // Deafult Constructor that draws a Quadrilateral
    Shape *shape = new Shape();

    // Grid Lines
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

    // shape->scaling();
    // ANIMATION
    {
        double pi = 4 * atan(1);
        float *centroid = shape->getCentroid(shape->coOrdinates);
        Matrix T = getTranslationMatrix(centroid[0], centroid[1], centroid[2]);
        Matrix T_inv = getTranslationMatrix(-1 * centroid[0] / 4, -1 * centroid[1] / 4, -1 * centroid[2] / 4);
        Matrix pZ = getProjectionZ();
        char text[50 + sizeof(char)];

        int i = 0;
        while (i != 3600)
        {
            float theta = i * (pi / 180);
            float phi = -0.5 * i * (pi / 180);

            Matrix rotateY = getRotationMatrixCounterClockwiseY(theta);
            Matrix rotateX = getRotationMatrixCounterClockwiseX(phi);
            Matrix scaleMatrix = getScaleMatrix(2.5, 2.5, 2.5);
            Matrix requiredMatrix = (*(shape->coOrdinates)) * T * rotateX * rotateY * scaleMatrix * pZ;
            Matrix *requiredMatrixPtr = &requiredMatrix;
            shape->drawShape(requiredMatrixPtr);
            delay(10);
            cleardevice();
            i++;
        }
    }
    // shape->axisAnimation(shape->coOrdinates);
    // shape->orthographicProjection(shape->coOrdinates);
    // shape->axonometricProjection(shape->coOrdinates);
    // shape->prespectiveProjection(shape->coOrdinates);

    // Menu
    // int flag = 1;
    // int option = 0;
    // do
    // {
    //     cleardevice();
    //     // Grid Lines
    //     line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    //     line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
    //     // Drawing the Shape
    //     shape->drawShape((shape->coOrdinates));

    //     setcolor(12);
    //     cout << "Choose Option\n"
    //          << "1. Scaling\n"
    //          << "2. Shearing\n"
    //          << "3. Reflection\n"
    //          << "4. Rotation\n"
    //          << "5. Translation\n"
    //          << "6. General Transformation Matrix\n"
    //          << "7. Exit\n"
    //          << " : ";
    //     cin >> option;
    //     cout << "\n";
    //     switch (option)
    //     {
    //     case 1:
    //         shape->scaling();
    //         break;
    //     case 2:
    //         shape->shearing();
    //         break;
    //     case 3:
    //         shape->reflection();
    //         break;
    //     case 4:
    //         shape->rotation();
    //         break;
    //     case 5:
    //         shape->translation();
    //         break;
    //     case 6:
    //         shape->transformationMatrix();
    //         break;
    //     case 7:
    //         flag = 0;
    //         cout << "EXITING\n";
    //         break;
    //     default:
    //         cout << " INVALID\n";
    //         break;
    //     }
    //     system("pause");
    //     system("cls");
    //     setcolor(15);
    // } while (flag);

    // getch();
    closegraph();

    delete shape;
    cout << Matrix::deleted << "\t" << Matrix::created << "\n";
    return 0;
}