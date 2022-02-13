#include <iostream>
#include <graphics.h>
using namespace std;
#include "shape.h"

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Polygon
    cout << "Enter the Number of Co-ordinates : ";
    int coOrdinates = 0;
    cin >> coOrdinates;
    Shape *shape = new Shape(coOrdinates);
    // Deafult Constructor that draws a Quadrilateral
    // Shape *shape = new Shape();

    // Menu
    int flag = 1;
    int option = 0;
    do
    {
        cleardevice();
        // Grid Lines
        line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
        line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
        // Drawing the Shape
        shape->drawShape((shape->coOrdinates));

        setcolor(12);
        cout << "Choose Option\n"
             << "1. Scaling\n"
             << "2. Shearing\n"
             << "3. Reflection\n"
             << "4. Rotation\n"
             << "5. Translation\n"
             << "6. General Transformation Matrix\n"
             << "7. Exit\n"
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

    closegraph();

    delete shape;
    cout << "Deleting Temporary Matrices : "
         << Matrix::tempMatrices.size() << "\n";
    for (auto i = Matrix::tempMatrices.begin(); i != Matrix::tempMatrices.end(); i++)
    {
        try
        {
            delete (*i);
            cout << ".";
        }
        catch (exception &e)
        {
            cout << "ERROR : \t " << e.what() << "\n";
        }
    }
    return 0;
}