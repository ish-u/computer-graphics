#include <iostream>
#include <graphics.h>
#include <math.h>

        // delta *= PI / 180;
using namespace std;
#include "shape.h"

int main()
{
    int gd = DETECT, gm;
    // initgraph(&gd, &gm, NULL);
    initwindow(800, 800);

    // cout << "Enter the Number of Co-ordinates : ";
    // int coOrdinates = 0;
    // cin >> coOrdinates;
    // Shape *shape = new Shape(coOrdinates);
    // Default Constructor that draws a Cube with one cutted corner
    Shape *shape = new Shape();

    // Menu
    int flag = 1;
    int option = 0;
    do
    {

        cout << "Choose Option\n"
             << "1. Scaling\n"
             << "2. Shearing\n"
             << "3. Reflection\n"
             << "4. Rotation\n"
             << "5. Translation\n"
             << "6. General Transformation Matrix\n"
             << "7. Object Animation\n"
             << "8. Orthographic Projection Demonstration\n"
             << "9. Axonometric Projection Demonstration\n"
             << "10. Oblique Projection Demonstration\n"
             << "11. Prespective Projection Demonstration\n"
             << "12. Exit\n"
             << " : ";
        cin >> option;
        cout << "\n";
        switch (option)
        {
        case 1:
            shape->scaling();
            break;
        case 2:
            shape->shearing();
            break;
        case 3:
            shape->reflection();
            break;
        case 4:
            shape->rotation();
            break;
        case 5:
            shape->translation();
            break;
        case 6:
            shape->transformationMatrix();
            break;
        case 7:
            shape->animation();
            break;
        case 8:
            shape->orthographicProjectionDemo();
            break;
        case 9:
            shape->axonometricProjectionDemo();
            break;
        case 10:
            shape->obliqueProjectionDemo();
            break;
        case 11:
            shape->prespectiveProjectionDemo();
            break;
        case 12:
            flag = 0;
            cout << "EXITING\n";
            break;
        default:
            cout << " INVALID\n";
            break;
        }
        system("pause");
        system("cls");
        cleardevice();
        setcolor(15);
    } while (flag);

    // getch();
    closegraph();

    delete shape;
    cout << Matrix::deleted << "\t" << Matrix::created << "\n";
    return 0;
}