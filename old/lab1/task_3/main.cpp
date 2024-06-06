#include <iostream>
#include <optional>
#include <fstream>
#include <cmath>

using namespace std;

#define MATRIX_SIZE_2 2
#define MATRIX_SIZE_3 3

typedef double Matrix3x3[MATRIX_SIZE_3][MATRIX_SIZE_3];
typedef double Matrix2x2[MATRIX_SIZE_2][MATRIX_SIZE_2];

struct WrapperMatrix3x3
{
    Matrix3x3 items;
};

struct WrapperMatrix2x2
{
    Matrix2x2 items;
};

struct Vec2
{
    int x;
    int y;
};

optional<string> ParseCommandLine(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "File name required!" << endl;
        return nullopt;
    }

    return argv[1];
}

optional<WrapperMatrix3x3> ReadMatrixFromFile(ifstream& inputFile) {
    WrapperMatrix3x3 matrix = {};

    for (int i = 0; i < MATRIX_SIZE_3; i++)
    {
        for (int j = 0; j < MATRIX_SIZE_3; j++)
        {
            if (!(inputFile >> matrix.items[j][i]))
            {
                cout << "Incorrect matrix file format." << endl;
                return nullopt;
            }
        }
    }

    if (inputFile.bad() || !inputFile.eof())
    {
        cout << "Matrix should be 3 x 3" << endl;
        return nullopt;
    }

    return matrix;
}

void PrintSquareMatrix(WrapperMatrix3x3 matrix)
{
    for (int i = 0; i < MATRIX_SIZE_3; i++)
    {
        for (int j = 0; j < MATRIX_SIZE_3; j++)
        {
            cout.width(10);
            cout.setf(ios::fixed);
            cout.precision(3);
            cout << matrix.items[j][i];
        }
        cout << endl;
    }
}

double GetInvertMatrix(WrapperMatrix3x3 const &matrix)
{
    double determinant = 0;
    for (int i = 0; i < MATRIX_SIZE_3; ++i) {
        determinant = determinant + (matrix.items[0][i] * (matrix.items[1][(i+1)%3] * matrix.items[2][(i+2)%3] - matrix.items[1][(i+2)%3] * matrix.items[2][(i+1)%3])); //TODO: use several lines
    }

    return determinant;
}

double CalculateSecondOrderDeterminant(WrapperMatrix3x3 const &matrix, Vec2 cell) {
    WrapperMatrix2x2 matrix2x2 = {};
    int ii, jj = 0;

    for (int i = 0; i < MATRIX_SIZE_3; i++)
    {
        if (cell.x == i)
        {
            continue;
        }

        ii = 0;
        for (int j = 0; j < MATRIX_SIZE_3; j++)
        {
            if (cell.y == j)
            {
                continue;
            }

            matrix2x2.items[ii][jj] = matrix.items[j][i];
            ii++;
        }

        jj++;
    }

    double algebraicAddition = pow(-1, cell.x + cell.y);
    return algebraicAddition * (matrix2x2.items[0][0] * matrix2x2.items[1][1] - matrix2x2.items[1][0] * matrix2x2.items[0][1]);
}

WrapperMatrix3x3 CalculateInverseMatrix(WrapperMatrix3x3 const &matrix, double matrixDeterminant) {
    WrapperMatrix3x3 InverseMatrix = {};

    for (int i = 0; i < MATRIX_SIZE_3; i++)
    {
        for (int j = 0; j < MATRIX_SIZE_3; j++)
        {
            double secondOrderDeterminant = CalculateSecondOrderDeterminant(matrix, {j,i});
            InverseMatrix.items[j][i] = secondOrderDeterminant * (1./matrixDeterminant);
        }
    }

    return InverseMatrix;
}

optional<ifstream> ReadFile(const string& filePath) {
    ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        cout << "File not found!"<< endl;
        inputFile.close();

        return nullopt;
    }

    return inputFile;
}

int main(int argc, char* argv[]) {
    auto filePath = ParseCommandLine(argc, argv);
    if (!filePath)
    {
        return EXIT_FAILURE;
    }

    auto inputFile = ReadFile(filePath.value());
    if (!inputFile)
    {
        return EXIT_FAILURE;
    }

    auto matrix = ReadMatrixFromFile(inputFile.value());
    if (!matrix)
    {
        return EXIT_FAILURE;
    }

    auto matrixDeterminant = GetInvertMatrix(matrix.value());

    if (matrixDeterminant == 0)
    {
        cout << "The determinant is zero!" << endl;
        return EXIT_FAILURE;
    }
    auto invertMatrix = CalculateInverseMatrix(*matrix, matrixDeterminant);

    PrintSquareMatrix(invertMatrix);

    return EXIT_SUCCESS;
}
// 0,75
//