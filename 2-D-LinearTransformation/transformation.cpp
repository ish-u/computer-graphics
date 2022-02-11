#include <iostream>
#include <graphics.h>
using namespace std;
#include "shape.h"

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Grid Lines
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

    // Polygon
    Shape *shape = new Shape(3);
    shape->drawShape(shape->coOrdinates);

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
             << "5. Translationn\n"
             << "6. Transformation Matrix\n"
             << "7. Exit\n"
             << " : ";
        cin >> option;
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
            flag = 0;
            cout << "EXITING\n";
            break;
        default:
            cout << " INVALID\n";
            break;
        }
        // system("cls");

    } while (flag);

    closegraph();
    system("pause");
    return 0;
}