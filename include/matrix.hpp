#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class matrix_t
{
private:
    int** data;
    unsigned int rows;
    unsigned int columns;

public:
    matrix_t()
    {
        int** data = nullptr;
        columns = 0;
        rows = 0;
    }

    matrix_t(const matrix_t& other)
    {
        rows = other.rows;
        columns = other.columns;
        data = new int*[rows];
        for (unsigned int i = 0; i < rows; ++i)
        {
            data[i] = new int[columns];
            for (unsigned int j = 0; j < columns; ++j)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }

    matrix_t& operator=(const matrix_t& other)
    {
        if (this != &other)
        {
            if (data != nullptr && rows && columns)
            {
                for (unsigned int i = 0; i < rows; ++i)
                {
                    delete[] data[i];
                }
                delete[] data;
            }
            rows = other.rows;
            columns = other.columns;
            data = new int*[rows];
            for (unsigned int i = 0; i < rows; ++i)
            {
                data[i] = new int[columns];
                for (unsigned int j = 0; j < columns; ++j)
                {
                    data[i][j] = other.data[i][j];
                }
            }
            return *this;
        }
    }

    ~matrix_t()
    {
        for (unsigned int i = 0; i < this->rows; i++)
        {
            delete[] this->data[i];
        }
        delete[] this->data;
        columns = 0;
        rows = 0;
    }

    matrix_t add(matrix_t& other) const
    {
        matrix_t result;
        if (this->rows == other.rows && this->columns == other.columns)
        {
            result.rows = this->rows;
            result.columns = this->columns;
            result.data = new int*[rows];
            for (unsigned int i = 0; i < rows; i++)
            {
                result.data[i] = new int[columns];
                for (unsigned int j = 0; j < columns; j++)
                {
                    result.data[i][j] = this->data[i][j] + other.data[i][j];
                }
            }
        }
        else
        {
            cout << "An error has occured while reading input data";
            cout << endl;
        }
        return result;
    }

    matrix_t sub(matrix_t& other) const
    {
        matrix_t result;
        if (this->rows == other.rows && this->columns == other.columns)
        {
            result.rows = this->rows;
            result.columns = this->columns;
            result.data = new int*[rows];
            for (unsigned int i = 0; i < rows; i++)
            {
                result.data[i] = new int[columns];
                for (unsigned int j = 0; j < columns; j++)
                {
                    result.data[i][j] = this->data[i][j] - other.data[i][j];
                }
            }
        }
        else
        {
            cout << "An error has occured while reading input data";
            cout << endl;
        }
        return result;
    }

    matrix_t mul(matrix_t& other) const
    {
        matrix_t result;
        if (this->columns == other.rows)
        {
            result.rows = this->rows;
            float sum = 0;
            result.columns = other.columns;
            result.data = new int*[result.rows];
            for (unsigned int i = 0; i < result.rows; ++i)
            {
                result.data[i] = new int[result.columns];
                for (unsigned int j = 0; j < result.columns; ++j)
                {
                    sum = 0;
                    for (unsigned int k = 0; k < this->columns; ++k)
                    {
                        sum += this->data[i][k] * other.data[k][j];
                    }
                    result.data[i][j] = sum;
                }
            }
        }
        else
        {
            cout << "An error has occured while reading input data";
            cout << endl;
        }
        return result;
    }

    matrix_t trans() const
    {
        matrix_t result;
        result.rows = this->columns;
        result.columns = this->rows;
        result.data = new int*[result.rows];
        for (unsigned int i = 0; i < result.rows; i++)
        {
            result.data[i] = new int[result.columns];
            for (unsigned int j = 0; j < result.columns; j++)
            {
                result.data[i][j] = this->data[j][i];
            }
        }
        return result;
    }

    ifstream& read(ifstream& fin, string name)
    {
        fin.open(name.c_str());
        if (!(fin.is_open()))
        {
            {
                cout << "An error has occured while reading input data";
                cout << endl;
            }
            return fin;
        }
        char op;
        if (fin >> rows && fin >> op && op == ',' && fin >> columns)
        {
            data = new int*[rows];
            for (unsigned int i = 0; i < rows; i++)
            {
                data[i] = new int[columns];
                for (unsigned int j = 0; j < columns; j++)
                {
                    fin >> data[i][j];
                }
            }
        }
        else
        {
            cout << "An error has occured while reading input data";
            cout << endl;
        }
        fin.close();
        return fin;
    }
    ostream& write(ostream& stream)
    {
        for (unsigned int i = 0; i < rows; i++)
        {
            cout << endl;
            for (unsigned int j = 0; j < columns; j++)
            {
                stream << data[i][j] << ' ';
            }
        }
        cout << endl;
        return stream;
    }
};

int main()
{
    matrix_t matrix1, matrix2, result;
    string name_file1, name_file2, stroka;
    char op;
    getline(cin, stroka);
    istringstream stream(stroka);
    if (stream >> name_file1 && stream >> op)
    {
        ifstream fin1, fin2;
        if (matrix1.read(fin1, name_file1))
        {
            if (op == 'T')
            {
                result = matrix1.trans();
                result.write(cout);
            }
            else if (stream >> name_file2)
            {
                if (matrix2.read(fin2, name_file2))
                {
                    switch (op)
                    {
                        case '+':
                        {
                            result = matrix1.add(matrix2);
                            result.write(cout);
                            break;
                        }
                        case '-':
                        {
                            result = matrix1.sub(matrix2);
                            result.write(cout);
                            break;
                        }
                        case '*':
                        {
                            result = matrix1.mul(matrix2);
                            result.write(cout);
                            break;
                        }
                        default:
                        {
                            cout << "An error has occured while reading input data";
                            cout << endl;
                        }
                        break;
                    }
                }
                else
                {
                    cout << "An error has occured while reading input data";
                    return -1;
                    cout << endl;
                }
            }
            else
            {
                cout << "An error has occured while reading input data";
                cout << endl;
                return -1;
            }
        }
        else
        {
            cout << "An error has occured while reading input data";
            cout << endl;
            return -1;
        }
    }
    else
    {
        cout << "An error has occured while reading input data";
        cout << endl;
        return -1;
    }
    return 0;
}
