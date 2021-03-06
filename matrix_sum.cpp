#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <strstream>
#include <vector>
// out_of_range

using namespace std;

//// Реализуйте здесь
//// * класс Matrix
//// * оператор ввода для класса Matrix из потока istream
//// * оператор вывода класса Matrix в поток ostream
//// * оператор проверки на равенство двух объектов класса Matrix
//// * оператор сложения двух объектов класса Matrix

//class Matrix {
//    vector<vector<int>> m;
//    int rows;
//    int cols;
//    friend Matrix operator+(const Matrix& l, const Matrix& r);
//    friend istream& operator>>(istream& s, Matrix& m);
//    friend ostream& operator<<(ostream& s, const Matrix& m);
//    friend bool operator==(const Matrix& l, const Matrix& r);

//public:
//    Matrix()
//        : rows(0)
//        , cols(0)
//    {
//    }
//    Matrix(int rows, int cols)
//        : rows(rows)
//        , cols(cols)
//    {
//        if (rows < 0 || cols < 0)
//            throw out_of_range("{}");
//        m.resize(rows, vector<int>(cols));
//    }
//    void Reset(int rows, int cols)
//    {
//        if (rows < 0 || cols < 0)
//            throw out_of_range("{}");
//        this->rows = rows;
//        this->cols = cols;
//        m.clear();
//        m.resize(rows, vector<int>(cols));

//        for (auto& r : m) {
//            for (auto& c : r) {
//                c = 0;
//            }
//        }
//    }

//    int At(int rows, int cols) const
//    {
//        return m.at(rows).at(cols);
//    }

//    int& At(int rows, int cols)
//    {
//        return m.at(rows).at(cols);
//    }
//    int GetNumRows() const { return rows; }
//    int GetNumColumns() const { return cols; }
//    /*
//    конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
//    конструктор от двух целочисленных параметров: rows и cols, — которые задают количество строк и столбцов матрицы соответственно
//    метод Reset, принимающий два целочисленных параметра, которые задают новое количество строк и столбцов матрицы соответственно; метод Reset меняет размеры матрицы на заданные и обнуляет все её элементы
//    константный метод At, который принимает номер строки и номер столбца (именно в этом порядке; нумерация строк и столбцов начинается с нуля) и возвращает значение в соответствущей ячейке матрицы
//    неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей ячейке матрицы
//    константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов матрицы соответственно
//    */
//};

///*
//оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и столбцов (именно в этом порядке), а затем все элементы матрицы: сначала элемент первой строки и первого столбца, затем элемент первой строки и второго столбца и так далее
//оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает оператор ввода, — в первой строке количество строк и столбцов, во второй — элементы первой строки, в третьей — элементы второй строки и т.д.
//оператор проверки на равенство (==): он должен возвращать true, если сравниваемые матрицы имеют одинаковый размер и все их соответствующие элементы равны между собой, в противном случае он должен возвращать false.
//оператор сложения: он должен принимать две матрицы и возвращать новую матрицу, которая является их суммой; если переданные матрицы имеют разные размеры этот оператор должен выбрасывать стандартное исключение invalid_argument.
//*/

//Matrix operator+(const Matrix& l, const Matrix& r)
//{
//    if (l.GetNumRows() != r.GetNumRows()) {
//        throw invalid_argument("Mismatched number of rows");
//    }
//    if (l.GetNumColumns() != r.GetNumColumns()) {
//        throw invalid_argument("Mismatched number of columns");
//    }
//    const int rows = l.GetNumRows(), cols = l.GetNumColumns();
//    Matrix m(rows, cols);
//    for (int row = 0; row < rows; ++row) {
//        for (int col = 0; col < cols; ++col) {
//            m.At(row, col) = l.At(row, col) + r.At(row, col);
//        }
//    }
//    return m;
//}

//bool operator==(const Matrix& l, const Matrix& r)
//{
//    const int rows = l.GetNumRows(), cols = l.GetNumColumns();
//    if (rows != r.GetNumRows() || cols != r.GetNumColumns())
//        return false;
//    for (int row = 0; row < rows; ++row) {
//        for (int col = 0; col < cols; ++col) {
//            if (l.At(row, col) != r.At(row, col))
//                return false;
//        }
//    }
//    return true;
//}

//ostream& operator<<(ostream& s, const Matrix& m)
//{
//    s << m.GetNumRows() << ' ' << m.GetNumColumns() << endl;
//    for (const auto& r : m.m) {
//        for (const auto& c : r) {
//            s << c << ' ';
//        }
//        s << endl;
//    }
//    return s;
//}

//istream& operator>>(istream& s, Matrix& m)
//{
//    int rows, cols;
//    s >> rows >> cols;
//    Matrix tmp(rows, cols);
//    for (auto& r : tmp.m) {
//        for (auto& c : r) {
//            s >> c;
//        }
//    }
//    m = tmp;
//    return s;
//}

class Matrix {
private:
    int num_rows_;
    int num_columns_;

    vector<vector<int>> elements_;

public:
    Matrix()
    {
        num_rows_ = 0;
        num_columns_ = 0;
    }

    Matrix(int num_rows, int num_columns)
    {
        Reset(num_rows, num_columns);
    }

    void Reset(int num_rows, int num_columns)
    {
        if (num_rows < 0) {
            throw out_of_range("num_rows must be >= 0");
        }
        if (num_columns < 0) {
            throw out_of_range("num_columns must be >= 0");
        }
        if (num_rows == 0 || num_columns == 0) {
            num_rows = num_columns = 0;
        }

        num_rows_ = num_rows;
        num_columns_ = num_columns;
        elements_.assign(num_rows, vector<int>(num_columns));
    }

    int& At(int row, int column)
    {
        return elements_.at(row).at(column);
    }

    int At(int row, int column) const
    {
        return elements_.at(row).at(column);
    }

    int GetNumRows() const
    {
        return num_rows_;
    }

    int GetNumColumns() const
    {
        return num_columns_;
    }
};

bool operator==(const Matrix& one, const Matrix& two)
{
    if (one.GetNumRows() != two.GetNumRows()) {
        return false;
    }

    if (one.GetNumColumns() != two.GetNumColumns()) {
        return false;
    }

    for (int row = 0; row < one.GetNumRows(); ++row) {
        for (int column = 0; column < one.GetNumColumns(); ++column) {
            if (one.At(row, column) != two.At(row, column)) {
                return false;
            }
        }
    }

    return true;
}

Matrix operator+(const Matrix& one, const Matrix& two)
{
    if (one.GetNumRows() != two.GetNumRows()) {
        throw invalid_argument("Mismatched number of rows");
    }

    if (one.GetNumColumns() != two.GetNumColumns()) {
        throw invalid_argument("Mismatched number of columns");
    }

    Matrix result(one.GetNumRows(), one.GetNumColumns());
    for (int row = 0; row < result.GetNumRows(); ++row) {
        for (int column = 0; column < result.GetNumColumns(); ++column) {
            result.At(row, column) = one.At(row, column) + two.At(row, column);
        }
    }

    return result;
}

istream& operator>>(istream& in, Matrix& matrix)
{
    int num_rows, num_columns;
    in >> num_rows >> num_columns;

    matrix.Reset(num_rows, num_columns);
    for (int row = 0; row < num_rows; ++row) {
        for (int column = 0; column < num_columns; ++column) {
            in >> matrix.At(row, column);
        }
    }

    return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix)
{
    out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (int row = 0; row < matrix.GetNumRows(); ++row) {
        for (int column = 0; column < matrix.GetNumColumns(); ++column) {
            if (column > 0) {
                out << " ";
            }
            out << matrix.At(row, column);
        }
        out << endl;
    }

    return out;
}

int main()
{
    //    {

    //    }

#ifdef __TEST__
    istrstream cin(
        "3 5\n"
        "6 4 -1 9 8\n"
        "12 1 2 9 -5\n"
        "-4 0 12 8 6\n"
        "3 5\n"
        "5 1 0 -8 23\n"
        "14 5 -6 6 9\n"
        "8 0 5 4 1\n"
        /**/);

    //    3 5
    //    11 5 -1 1 31
    //    26 6 -4 15 4
    //    4 0 17 12 7

    cout << cin.str();
#endif

    Matrix one;
    Matrix two;
    cin >> one >> two;
    cout << one + two << endl;
    cout << (one == one) << endl;
    cout << (one == two) << endl;
    cout << "2222" << endl;
    two.Reset(10, 10);
    cout << two << endl;
    two.Reset(0, 0);
    cout << two << endl;

    return 0;
}
