#include <fstream>
#include <iostream>
#include <stdexcept>
#include <strstream>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

class Matrix {
    vector<vector<int>> m;
    friend Matrix operator+(const Matrix& l, const Matrix& r);
    friend istream& operator>>(istream& s, Matrix& m);
    friend ostream& operator<<(ostream& s, const Matrix& m);

public:
    Matrix() {}
    Matrix(int num_rows, int num_cols)
    {
        m.resize(num_rows);
        for (auto& r : m) {
            r.resize(num_cols);
        }
    }
    void Reset(int num_rows, int num_cols)
    {
        m.resize(num_rows, vector<int>(num_cols));
        for (auto& r : m) {
            for (auto& c : r) {
                c = 0;
            }
        }
    }

    int At(int num_rows, int num_cols) const
    {
        return m[num_rows][num_cols];
    }

    int& At(int num_rows, int num_cols)
    {
        return m[num_rows][num_cols];
    }
    int GetNumRows() const { return m.size(); }
    int GetNumColumns() const { return m.size() ? m.front().size() : 0; }
    /*
    конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
    конструктор от двух целочисленных параметров: num_rows и num_cols, — которые задают количество строк и столбцов матрицы соответственно
    метод Reset, принимающий два целочисленных параметра, которые задают новое количество строк и столбцов матрицы соответственно; метод Reset меняет размеры матрицы на заданные и обнуляет все её элементы
    константный метод At, который принимает номер строки и номер столбца (именно в этом порядке; нумерация строк и столбцов начинается с нуля) и возвращает значение в соответствущей ячейке матрицы
    неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей ячейке матрицы
    константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов матрицы соответственно
    */
};

/*
оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и столбцов (именно в этом порядке), а затем все элементы матрицы: сначала элемент первой строки и первого столбца, затем элемент первой строки и второго столбца и так далее
оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает оператор ввода, — в первой строке количество строк и столбцов, во второй — элементы первой строки, в третьей — элементы второй строки и т.д.
оператор проверки на равенство (==): он должен возвращать true, если сравниваемые матрицы имеют одинаковый размер и все их соответствующие элементы равны между собой, в противном случае он должен возвращать false.
оператор сложения: он должен принимать две матрицы и возвращать новую матрицу, которая является их суммой; если переданные матрицы имеют разные размеры этот оператор должен выбрасывать стандартное исключение invalid_argument.
*/

Matrix operator+(const Matrix& l, const Matrix& r)
{
    return Matrix{};
}

ostream& operator<<(ostream& s, const Matrix& m)
{
    s << m.GetNumRows() << m.GetNumColumns() << endl;
    for (const auto& r : m.m) {
        for (const auto& c : r) {
            s << c;
        }
        s << endl;
    }
    return s;
}

istream& operator>>(istream& s, Matrix& m)
{
    int num_rows, num_cols;
    s >> num_rows >> num_cols;
    Matrix tmp(num_rows, num_cols);
    for (auto& r : tmp.m) {
        for (auto& c : r) {
            s >> c;
        }
    }
    m = tmp;
    return s;
}

int main()
{

#ifdef __TEST__
    istrstream ss("3 5\n"
                  "6 4 -1 9 8\n"
                  "12 1 2 9 -5\n"
                  "-4 0 12 8 6\n"
                  "3 5\n"
                  "5 1 0 -8 23\n"
                  "14 5 -6 6 9\n"
                  "8 0 5 4 1\n");
//    3 5
//    11 5 -1 1 31
//    26 6 -4 15 4
//    4 0 17 12 7
#endif
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;

    return 0;
}
