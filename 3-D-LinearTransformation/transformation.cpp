#include <iostream>
#include <graphics.h>
#include <math.h>

using namespace std;
#include "shape.h"

int main()
{
    int gd = DETECT, gm;
    // initgraph(&gd, &gm, NULL);
    initwindow(800, 600);

    // Polygon
    // cout << "Enter the Number of Co-ordinates : ";
    // int coOrdinates = 0;
    // cin >> coOrdinates;
    // Shape *shape = new Shape(coOrdinates);
    // Deafult Constructor that draws a Quadrilateral
    Shape *shape = new Shape();

    // Menu
    int flag = 1;
    int option = 0;
    do
    {
        cleardevice();

        cout << "Choose Option\n"
             << "1. Scaling\n"
             << "2. Shearing\n"
             << "3. Reflection\n"
             << "4. Rotation\n"
             << "5. Translation\n"
             << "6. General Transformation Matrix\n"
             << "7. Object Animation\n"
             << "8. Projection Demonstration\n"
             << "9. Exit\n"
             << " : ";
        cin >> option;
        cout << "\n";
        switch (option)
        {
        case 1:
            shape->scaling();
            break;
        // case 2:
        //     shape->shearing();
        //     break;
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
            shape->projectionDemo();
            break;
        case 9:
            flag = 0;
            cout << "EXITING\n";
            break;
        default:
            cout << " INVALID\n";
            break;
        }
        system("pause");
        system("cls");
        setcolor(15);
    } while (flag);

    // getch();
    closegraph();

    delete shape;
    cout << Matrix::deleted << "\t" << Matrix::created << "\n";
    return 0;
}