#include <graphics.h>
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // // Grid Lines
    // DDA(10, 10, 10, 480);
    // for (int i = 10; i < 480; i += 10)
    // {
    //     DDA(10, i, 10, i);
    // }
    // DDA(10, 10, 640, 10);
    // for (int i = 10; i < 640; i += 10)
    // {
    //     DDA(i, 10, i, 10);
    // }

    /*

        WRITE CODE HERE

    */

    getch();
    closegraph();
    return 0;
}