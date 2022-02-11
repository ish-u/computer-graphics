#include <iostream>
#include <math.h>
#include <graphics.h>
using namespace std;
class Matrix
{

public:
    int r;
    int c;
    float **m;
    Matrix(int r, int c, int identity = 1)
    {
        this->r = r;
        this->c = c;
        m = new float *[r];
        for (int i = 0; i < r; i++)
        {
            m[i] = new float[c];
        }
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (identity == 1)
                {
                    if (i == j)
                    {

                        m[i][j] = 1;
                    }
                    else
                    {
                        m[i][j] = 0;
                    }
                }
                else
                {
                    m[i][j] = 0;
                }
            }
        }
    }
    ~Matrix()
    {
        for (int i = 0; i < r; i++)
        {
            delete[] m[i];
        }
        delete m;
    }
    void print()
    {
        cout << "\n";
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cout << m[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    Matrix *operator*(Matrix &B)
    {
        cout << "[Co-Ordinates]*[T] \n";
        if (this->c != B.r)
        {
            cout << "BAD";
            return new Matrix(0, 0);
        }

        Matrix *C = new Matrix(this->r, B.c, 0);

        for (int i = 0; i < this->r; i++)
        {
            for (int j = 0; j < B.c; j++)
            {
                for (int k = 0; k < this->c; k++)
                {
                    C->m[i][j] += (this->m[i][k] * B.m[k][j]);
                }
            }
        }
        C->print();
        return C;
    }
    Matrix *transpose()
    {
        Matrix *T = new Matrix(this->c, this->r);
        for (int i = 0; i < this->r; i++)
        {
            for (int j = 0; j < this->c; j++)
            {
                T->m[i][j] = this->m[j][i];
            }
        }
        return T;
    }
};
class Shape
{

public:
    // int **coOrdinates;
    Matrix *coOrdinates;
    int numberOfCoOrdinates = 0;
    Shape()
    {
        this->numberOfCoOrdinates = 4;
        this->coOrdinates = new Matrix(4, 3);
        this->coOrdinates->m[0][0] = 50;
        this->coOrdinates->m[0][1] = 50;
        this->coOrdinates->m[1][0] = 150;
        this->coOrdinates->m[1][1] = 75;
        this->coOrdinates->m[2][0] = 175;
        this->coOrdinates->m[2][1] = 150;
        this->coOrdinates->m[3][0] = 50;
        this->coOrdinates->m[3][1] = 150;

        // this->coOrdinates->m[0][0] = 0;
        // this->coOrdinates->m[0][1] = 0;
        // this->coOrdinates->m[1][0] = 100;
        // this->coOrdinates->m[1][1] = 0;
        // this->coOrdinates->m[2][0] = 100;
        // this->coOrdinates->m[2][1] = 100;
        // this->coOrdinates->m[3][0] = 0;
        // this->coOrdinates->m[3][1] = 100;

        // filling last row as 1 for Homogenous Co-Ordinates
        for (int i = 0; i < numberOfCoOrdinates; i++)
        {
            this->coOrdinates->m[i][2] = 1;
        }
        this->coOrdinates->print();
    }
    // constructor
    Shape(int numberOfCoOrdinates)
    {
        this->numberOfCoOrdinates = numberOfCoOrdinates;
        this->coOrdinates = new Matrix(numberOfCoOrdinates, 3);
        // taking Co-Ordinate Input
        for (int i = 0; i < numberOfCoOrdinates; i++)
        {
            cout << "Co-Ordinate - " << i + 1 << " ->\t";
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
        this->coOrdinates->print();
    }

    // desctructor
    ~Shape()
    {
        delete this->coOrdinates;
    }
    // member function
    void drawShape(Matrix *matrix);
    void scaling();
    void reflection();
    void shearing();
    void rotation();
    void translation();
    void transformationMatrix();

    // transformation matrices
    // SCALE MATRIX
    Matrix getScaleMatrix(float scaleFacorX, float scaleFacorY)
    {
        Matrix scaleMatrix(3, 3);
        scaleMatrix.m[2][2] = 1;
        scaleMatrix.m[0][0] = scaleFacorX;
        scaleMatrix.m[1][1] = scaleFacorY;
        return scaleMatrix;
    }
    // SHEARING MATRIX
    Matrix getShearingMatrix(float shearingFactorX, float shearingFactorY)
    {
        Matrix shearingMatrix(3, 3);
        shearingMatrix.m[1][0] = shearingFactorX;
        shearingMatrix.m[0][1] = shearingFactorY;
        shearingMatrix.print();
        return shearingMatrix;
    }
    // REFLECTION MATRIX
    Matrix getReflectionMatrixAboutX()
    {
        Matrix reflectionMatrix(3, 3);
        reflectionMatrix.m[0][0] = 1;
        reflectionMatrix.m[1][1] = -1;
        return reflectionMatrix;
    }
    Matrix getReflectionMatrixAboutY()
    {
        Matrix reflectionMatrix(3, 3);
        reflectionMatrix.m[0][0] = -1;
        reflectionMatrix.m[1][1] = 1;
        return reflectionMatrix;
    }
    Matrix getReflectionMatrixAboutOrigin()
    {
        Matrix reflectionMatrix(3, 3);
        reflectionMatrix.m[0][0] = -1;
        reflectionMatrix.m[1][1] = -1;
        return reflectionMatrix;
    }
    // ROTATION MATRIX
    Matrix getRotationMatrixCounterClockwise(float theta)
    {
        Matrix rotationMatrix(3, 3);
        const double multiplier = pow(10.0, 5);
        rotationMatrix.m[0][0] = cos(theta);
        rotationMatrix.m[0][1] = sin(theta);
        rotationMatrix.m[1][0] = (-1) * sin(theta);
        rotationMatrix.m[1][1] = cos(theta);

        return rotationMatrix;
    }
    Matrix getRotationMatrixClockwise(float theta)
    {
        Matrix rotationMatrix(3, 3);
        rotationMatrix.m[0][0] = cos(theta);
        rotationMatrix.m[0][1] = (-1) * sin(theta);
        rotationMatrix.m[1][0] = sin(theta);
        rotationMatrix.m[1][1] = cos(theta);

        return rotationMatrix;
    }
    // TRANSLATION MATRIX
    Matrix getTranslationMatrix(float xFactor, float yFactor)
    {
        Matrix translationMatrix(3, 3);
        translationMatrix.m[2][0] = -xFactor;
        translationMatrix.m[2][1] = -yFactor;
        return translationMatrix;
    }
};

void Shape::drawShape(Matrix *matrix)
{

    float **coOrdinates = matrix->m;
    int *poly = new int[(numberOfCoOrdinates + 1) * 2];
    int k = 0;
    for (int i = 0; i < numberOfCoOrdinates; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            poly[k++] = coOrdinates[i][j];
        }
    }
    poly[k++] = coOrdinates[0][0];
    poly[k++] = coOrdinates[0][1];
    for (int i = 0; i < ((numberOfCoOrdinates + 1) * 2); i++)
    {
        // reflect about x-axis
        poly[i] *= (((i + 1) % 2 == 0) ? -1 : 1);
        // transtale to center of window
        poly[i] += (((i + 1) % 2 != 0) ? getmaxx() / 2 : getmaxy() / 2);
        // cout << poly[i] << "\t";
    }
    drawpoly(numberOfCoOrdinates + 1, poly);
    delete[] poly;
}

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
    switch (option)
    {
    case 1:
    {
        cout << "Enter Scale : ";
        cin >> scaleFactorX;
        scaleFactorY = scaleFactorX;
    }
    break;
    case 2:
    {
        cout << "Enter Scale Factor in x-direction : ";
        cin >> scaleFactorX;
        cout << "Enter Scale Factor in y-direction : ";
        cin >> scaleFactorY;
    }
    break;
    default:
    {
        cout << "INVALID\n";
    }
    break;
    }
    Matrix scaleMatrix = getScaleMatrix(scaleFactorX, scaleFactorY);
    this->drawShape((*(this->coOrdinates)) * (scaleMatrix));
}

void Shape ::reflection()
{
    cout << "REFLECTION \n"
         << "1. about x-axis \n"
         << "2. about y-axis \n"
         << "3. about origin \n";
    Matrix reflectionMatrix(3, 3);
    int option;
    cin >> option;
    switch (option)
    {
    case 1:
    {
        Matrix reflectionMatrix = getReflectionMatrixAboutX();
        this->drawShape((*(this->coOrdinates)) * (reflectionMatrix));
    }
    break;
    case 2:
    {
        Matrix reflectionMatrix = getReflectionMatrixAboutY();
        this->drawShape((*(this->coOrdinates)) * (reflectionMatrix));
    }
    break;
    case 3:
    {

        Matrix reflectionMatrix = getReflectionMatrixAboutOrigin();
        this->drawShape((*(this->coOrdinates)) * (reflectionMatrix));
    }
    break;
        break;
    default:
    {
        cout << "INVALID\n";
    }
    break;
    }
}

void Shape ::shearing()
{
    cout << "SHEARING \n"
         << "1. about x-component \n"
         << "2. about y-component \n"
         << "3. about both x-component and y-component \n";
    float shearingX = 1;
    float shearingY = 1;
    int option;
    cin >> option;
    switch (option)
    {
    case 1:
    {
        cout << "Enter Shearing Factor : ";
        cin >> shearingX;
        Matrix shearingMatrix = getShearingMatrix(shearingX, 0);
        this->drawShape((*(this->coOrdinates)) * (shearingMatrix));
    }
    break;
    case 2:
    {
        cout << "Enter Shearing Factor : ";
        cin >> shearingY;
        Matrix shearingMatrix = getShearingMatrix(0, shearingY);
        this->drawShape((*(this->coOrdinates)) * (shearingMatrix));
    }
    break;
    case 3:
    {
        cout << "Enter Shearing Factor x-component : ";
        cin >> shearingX;
        cout << "Enter Shearing Factor y-component : ";
        cin >> shearingY;
        Matrix shearingMatrix = getShearingMatrix(shearingX, shearingY);
        this->drawShape((*(this->coOrdinates)) * (shearingMatrix));
    }
    break;
    default:
    {
        cout << "INVALID\n";
    }
    break;
    }
}

void Shape ::rotation()
{
    cout << "ROTATION \n"
         << "1. Counter Clockwise about Origin \n"
         << "2. Clockwise about Origin \n"
         << "3. Counter Clockwise about an arbitary point\n"
         << "4. Clockwise about an arbitary point\n";
    int option;
    cin >> option;
    double pi = 4 * atan(1);
    float theta = 0;
    switch (option)
    {
    case 1:
    {
        cout << "Enter Angle : ";
        cin >> theta;
        theta *= (pi / 180);
        Matrix rotationMatrix = getRotationMatrixCounterClockwise(theta);
        this->drawShape((*(this->coOrdinates)) * (rotationMatrix));
    }
    break;
    case 2:
    {
        cout << "Enter Angle : ";
        cin >> theta;
        theta *= (pi / 180);
        Matrix rotationMatrix = getRotationMatrixClockwise(theta);
        this->drawShape((*(this->coOrdinates)) * (rotationMatrix));
    }
    break;
    case 3:
    {
        cout << "Enter Angle : ";
        cin >> theta;
        theta *= (pi / 180);
        int x, y;
        cout << "Enter Co-Ordinates of the Points \n";
        cout << "x : ";
        cin >> x;
        cout << "y : ";
        cin >> y;
        Matrix T = getTranslationMatrix(x, y);
        Matrix R = getRotationMatrixCounterClockwise(theta);
        Matrix T_inverse = getTranslationMatrix(-x, -y);
        Matrix *requiredMatrix = (*(T * R) * T_inverse);
        this->drawShape((*(this->coOrdinates)) * (*requiredMatrix));
    }
    break;
    case 4:
    {
        cout << "Enter Angle : ";
        cin >> theta;
        theta *= (pi / 180);
        int x, y;
        cout << "Enter Co-Ordinates of the Points \n";
        cout << "x : ";
        cin >> x;
        cout << "y : ";
        cin >> y;
        Matrix T = getTranslationMatrix(x, y);
        Matrix R = getRotationMatrixClockwise(theta);
        Matrix T_inverse = getTranslationMatrix(-x, -y);
        Matrix *requiredMatrix = (*(T * R) * T_inverse);
        this->drawShape((*(this->coOrdinates)) * (*requiredMatrix));
    }
    break;

    default:
    {
        cout << "INVALID\n";
    }
    break;
    }
}

void Shape::translation()
{
    cout << "TRANSLATION \n";
    int xFactor = 0;
    int yFactor = 0;
    cout << "Translate x co-ordinate by : ";
    cin >> xFactor;
    cout << "Translate y co-ordinate by : ";
    cin >> yFactor;
    Matrix translationMatrix = getTranslationMatrix(xFactor, yFactor);
    this->drawShape((*(this->coOrdinates)) * (translationMatrix));
}

void Shape ::transformationMatrix()
{
    Matrix transformationMat(3, 3);
    int option = 0;
    cout << "Choose Option\n"
         << "2x2 Matrix\n"
         << "3x3 Matrix\n"
         << " : ";
    cin >> option;
    switch (option)
    {
    case 1:
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << "(" << (i + 1) << " , " << (j + 1) << ") : ";
                cin >> transformationMat.m[i][j];
            }
        }
        break;
    case 2:
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << "(" << (i + 1) << " , " << (j + 1) << ") : ";
                cin >> transformationMat.m[i][j];
            }
        }

        break;
    default:
        break;
    }
    transformationMat.print();
    this->drawShape((*(this->coOrdinates)) * (transformationMat));
}
