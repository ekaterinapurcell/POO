// Să se creeze clasa Matrix – matrice. Clasa conţine pointer spre Complex, numărul de rînduri şi de coloane şi o variabilă – codul erorii.
//  Să se definească constructorul fără parametri (constructorul implicit), constructorul cu un parametru – matrice pătrată şi constructorul cu doi parametri – matrice dreptunghiulară ş. a.
//  Să se definească funcţiile membru de acces: returnarea şi setarea valorii elementului (i,j).
//  Să se definească funcţiile de adunare şi scădere a două matrice; înmulţirea unei matrice cu alta; înmulţirea unei matrice cu un număr.
//  Să se testeze funcţionarea clasei. În caz de insuficienţă de memorie, necorespondenţă a dimensiunilor matricelor, depăşire a limitei memoriei utilizate să se stabilească codul erorii.

#include <iostream>

class Complex
{
private:
    double real;
    double imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex &other) const
    {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex &other) const
    {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex &other) const
    {
        double r = real * other.real - imag * other.imag;
        double i = real * other.imag + imag * other.real;
        return Complex(r, i);
    }

    Complex operator*(double scalar) const
    {
        return Complex(real * scalar, imag * scalar);
    }

    void display() const
    {
        std::cout << real << " + " << imag << "i";
    }
};

class Matrix
{
private:
    Complex **elements;
    int rows;
    int cols;
    int errorCode;

public:
    Matrix() : elements(nullptr), rows(0), cols(0), errorCode(0) {}
    Matrix(int size) : rows(size), cols(size), errorCode(0)
    {
        initializeMatrix();
    }
    Matrix(int numRows, int numCols) : rows(numRows), cols(numCols), errorCode(0)
    {
        initializeMatrix();
    }
    ~Matrix()
    {
        for (int i = 0; i < rows; ++i)
        {
            delete[] elements[i];
        }
        delete[] elements;
    }

    void initializeMatrix()
    {
        elements = new Complex *[rows];
        for (int i = 0; i < rows; ++i)
        {
            elements[i] = new Complex[cols];
            for (int j = 0; j < cols; ++j)
            {
                elements[i][j] = Complex();
            }
        }
    }

    void setElement(int row, int col, const Complex &value)
    {
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            elements[row][col] = value;
        }
        else
        {
            errorCode = 1;
        }
    }

    Complex getElement(int row, int col)
    {
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            return elements[row][col];
        }
        else
        {
            errorCode = 1;
            return Complex();
        }
    }

    Matrix add(const Matrix &other)
    {
        if (rows != other.rows || cols != other.cols)
        {
            errorCode = 2;
            return Matrix();
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result.setElement(i, j, elements[i][j] + other.elements[i][j]);
            }
        }
        return result;
    }

    Matrix subtract(const Matrix &other)
    {
        if (rows != other.rows || cols != other.cols)
        {
            errorCode = 2;
            return Matrix();
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result.setElement(i, j, elements[i][j] - other.elements[i][j]);
            }
        }
        return result;
    }

    Matrix multiply(const Matrix &other)
    {
        if (cols != other.rows)
        {
            errorCode = 2;
            return Matrix();
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < other.cols; ++j)
            {
                Complex sum;
                for (int k = 0; k < cols; ++k)
                {
                    sum = sum + (elements[i][k] * other.elements[k][j]);
                }
                result.setElement(i, j, sum);
            }
        }
        return result;
    }

    Matrix multiply(double scalar)
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result.setElement(i, j, elements[i][j] * scalar);
            }
        }
        return result;
    }

    void display()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                elements[i][j].display();
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    int getErrorCode()
    {
        return errorCode;
    }
};

int main()
{
    Matrix squareMatrix(2);
    Matrix rectangularMatrix(2, 3);

    squareMatrix.setElement(0, 0, Complex(1, 2));
    squareMatrix.setElement(0, 1, Complex(3, 4));
    squareMatrix.setElement(1, 0, Complex(5, 6));
    squareMatrix.setElement(1, 1, Complex(7, 8));

    rectangularMatrix.setElement(0, 0, Complex(1, 1));
    rectangularMatrix.setElement(0, 1, Complex(2, 2));
    rectangularMatrix.setElement(0, 2, Complex(3, 3));
    rectangularMatrix.setElement(1, 0, Complex(4, 4));
    rectangularMatrix.setElement(1, 1, Complex(5, 5));
    rectangularMatrix.setElement(1, 2, Complex(6, 6));

    std::cout << "Square Matrix:" << std::endl;
    squareMatrix.display();
    std::cout << std::endl;

    std::cout << "Rectangular Matrix:" << std::endl;
    rectangularMatrix.display();
    std::cout << std::endl;

    Matrix resultAdd = squareMatrix.add(rectangularMatrix);
    std::cout << "Addition Result:" << std::endl;
    resultAdd.display();
    std::cout << std::endl;

    Matrix resultSubtract = squareMatrix.subtract(rectangularMatrix);
    std::cout << "Subtraction Result:" << std::endl;
    resultSubtract.display();
    std::cout << std::endl;

    Matrix resultMultiplyMatrices = squareMatrix.multiply(rectangularMatrix);
    std::cout << "Multiplication Result (Matrices):" << std::endl;
    resultMultiplyMatrices.display();
    std::cout << std::endl;

    Matrix resultMultiplyScalar = squareMatrix.multiply(2.5);
    std::cout << "Multiplication Result (Scalar):" << std::endl;
    resultMultiplyScalar.display();
    std::cout << std::endl;

    return 0;
}
