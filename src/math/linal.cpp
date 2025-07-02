#define _USE_MATH_DEFINES

#include <cstring>
#include <math.h>
#include <iostream>

#include "linal.h"

namespace LinearAlgebra {
    // Векторы


    // Конструктор по умолчанию
    TVector::TVector() : n(0), data(NULL) {}
    // Конструктор по количеству элементов
    TVector::TVector(int n) : n(0), data(NULL) {
        resize(n);
    }
    // Конструктор копирования
    TVector::TVector(const TVector& rvalue) : n(0), data(NULL) {
        (*this) = rvalue;
    }
    // Оператор присваивания
    TVector& TVector::operator = (const TVector& rvalue) {
        // Если левый операнд не совпадает с правым
        if (this != &rvalue) {
            // Если размер левого операнда не совпадает с правым, то память выделяется заново
            if (n != rvalue.n) {
                // Если память уже была выделена, удалить её
                if (data) { delete[] data; }
                // Выделение новой памяти
                data = new double[rvalue.n];
                // Сохранение нового размера
                n = rvalue.n;
            }
            // Перенос данных из правого операнда в левый
            memcpy(data, rvalue.data, sizeof(double) * n);
        }
        // Возврат ссылки на левый операнд для возможности цепочки присваиваний
        return *this;
    }
    // Деструктор
    TVector::~TVector() {
        // Если блок данных ранее был инициализирован, удаляем его
        if (data) {
            delete[] data;
            n = 0;
            data = NULL;
        }
    }
    // Функция задания кол-ва элементов вектора
    void TVector::resize(int n) {
#ifdef _DEBUG
        if (n < 0)
            throw 1;
#endif
        // Если новый размер совпадает со старым - выходим
        if (n == this->n) return;
        // Новый блок памяти
        double* newData = new double[n];
        // Если блок данных ранее был инициализирован...
        if (data) {
            // Минимальный из старого и нового размера блока
            int min_n = (this->n < n) ? this->n : n;
            // Перенос данных из старого блока в новый
            memcpy(newData, data, sizeof(double) * min_n);
            // Удаление старого блока
            delete[] data;
        }
        // Прикрепление нового блока к объекту вектора
        data = newData;
        // Сохранение нового размера
        this->n = n;
    }
    // Оператор сложения векторов
    TVector TVector::operator + (const TVector& arg) const {
#ifdef _DEBUG
        if (n != arg.n)
            throw 1;
#endif
        TVector V(n);
        for (int i = 0; i < n; i++)
            V[i] = data[i] + arg[i];
        return V;
    }
    // Оператор умножения вектора на число
    TVector TVector::operator * (double arg) const {
        TVector V1(n);
        for (int i = 0; i < n; i++)
            V1[i] = data[i] * arg;
        return V1;
    }
    // Оператор скалярного умножения векторов
    double TVector::operator * (const TVector& arg) const {
#ifdef _DEBUG
        if (n != arg.n)
            throw 1;
#endif
        double res = 0;
        for (int i = 0; i < 3; i++)
        {
            res += data[i] * arg[i];
        }
        return res;
    }
    // Оператор вычитания векторов
    TVector TVector::operator - (const TVector& arg) const {
#ifdef _DEBUG
        if (n != arg.n)
            throw 1;
#endif
        TVector V2(n);
        for (int i = 0; i < n; i++)
            V2[i] = data[i] - arg[i];
        return V2;
    }
    // Оператор - унарный минус
    TVector TVector::operator - () const {
        TVector V3(n);
        for (int i = 0; i < n; i++)
            V3[i] = -data[i];
        return V3;
    }
    // Функция получения модуля вектора
    double TVector::length() const {
        double len = 0;
        for (int i = 0; i < n; i++)
        {
            len += data[i] * data[i];
        }
        len = sqrt(len);
        return len;
    }
    // Функция нормирования вектора
    TVector TVector::norm() const {
        TVector V5(n);
        double module = 0;
        for (int i = 0; i < n; i++)
            module += data[i] * data[i];
        module = sqrt(module);
        for (int i = 0; i < n; i++)
            V5[i] = data[i] / module;
        return V5;
    }
    // Оператор умножения вектора на матрицу
    TVector TVector::operator * (const TMatrix& arg) const {
#ifdef _DEBUG
        if ((n != arg.rowCount()))
            throw 1;
#endif
        TVector V6(n);
        V6[0] = 0; V6[1] = 0; V6[2] = 0;
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                V6[j] += data[i] * arg(i, j);
            }
        }
        return V6;
    }
    // Дружественная функция - оператор умножения числа на вектор
    TVector operator * (double lvalue, const TVector& rvalue) {
        TVector V7(rvalue.n);
        for (int i = 0; i < rvalue.n; i++)
            V7[i] = lvalue * rvalue.data[i];
        return V7;
    }
    // Оператор векторного умножения векторов
    TVector TVector::operator ^ (const TVector& arg) const {
#ifdef _DEBUG
        if (n != arg.n || n > 3)
            throw 1;
#endif
        TVector V8(n);
        V8[0] = data[1] * arg[2] - data[2] * arg[1];
        V8[1] = data[2] * arg[0] - data[0] * arg[2];
        V8[2] = data[0] * arg[1] - data[1] * arg[0];
        return V8;
    }



    // Матрицы
    // Конструктор по умолчанию
    TMatrix::TMatrix() : n(0), m(0), data(NULL) {}
    // Конструктор с заданной размерностью
    TMatrix::TMatrix(int n, int m) : n(0), m(0), data(NULL) { resize(n, m); }
    // Конструктор копий
    TMatrix::TMatrix(const TMatrix& rvalue) : n(0), m(0), data(NULL) {
        (*this) = rvalue;
    }
    // Оператор присваивания
    TMatrix& TMatrix::operator = (const TMatrix& rvalue) {
        // Если левый операнд не совпадает с правым
        if (this != &rvalue) {
            // Удаление ранее выделенной памяти
            this->~TMatrix();
            // Выделение новой памяти по размерам правого операнда
            resize(rvalue.n, rvalue.m);
            // Перенос данных из правого операнда в левый построчно
            for (int i = 0; i < n; i++)
                memcpy(data[i], rvalue.data[i], sizeof(double) * m);
        }
        // Возврат ссылки на левый операнд для возможности цепочки присваиваний
        return (*this);
    }
    // Деструктор объекта матрицы
    TMatrix::~TMatrix() {
        if (data) {
            for (int i = 0; i < n; i++)
                delete[] data[i];
            delete[] data;
            data = NULL;
            n = m = 0;
        }
    }
    // Функция задания размерности матрицы
    void TMatrix::resize(int n, int m) {
        // Кол-во строк, которые нужно перенести в новые блоки данных
        int min_n = this->n < n ? this->n : n;
        // Если кол-во столбцов не совпадает
        if (this->m != m) {
            // Кол-во столбцов, которые нужно перенести в новые блоки данных
            int min_m = this->m < m ? this->m : m;
            // Цикл построчного переноса данных в новые блоки
            for (int i = 0; i < min_n; i++) {
                // Создание нового блока-строки
                double* newDataRow = new double[m];
                // Перенос данных в новый блок-строку
                memcpy(newDataRow, data[i], sizeof(double) * min_m);
                // Удаление старого блока строки на этом месте
                delete[] data[i];
                // Прикрепление нового блока-строки на старое место
                data[i] = newDataRow;
            }
            // Сохранение нового размера
            this->m = m;
        }
        // Если кол-во строк не совпадает
        if (this->n != n) {
            // Создание нового блока-контейнера
            double** newData = new double* [n];
            // Перенос содержимого старого контейнера в новый
            memcpy(newData, data, sizeof(double*) * min_n);
            // Удаление лишних строк из старого контейнера
            for (int i = n; i < this->n; i++) { delete[] data[i]; }
            // Удаление старого контейнера
            if (data) { delete[] data; }
            // Создание недостающих строк в новом контейнере
            for (int i = this->n; i < n; i++) { newData[i] = new double[m]; }
            // Привязка старого контейнера к новому
            data = newData;
            this->n = n;
        }
    }
    // Оператор сложения матриц
    TMatrix TMatrix::operator + (const TMatrix& arg) const {
#ifdef _DEBUG
        if ((n != arg.n) || (m != arg.m))
            throw 1;
#endif
        TMatrix M(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                M(i, j) = data[i][j] + arg(i, j);
        return M;
    }
    // Производящая функция для формирования единичной матрицы
    TMatrix TMatrix::E(int n) {
        TMatrix E(n, n);
        for (int i = 0; i < n; i++) {
            E(i, i) = 1;
            for (int j = i + 1; j < n; j++) { E(i, j) = E(j, i) = 0; }
        }
        return E;
    }
    // Оператор - унарный минус
    TMatrix TMatrix::operator - () const {
        TMatrix M1(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                M1(i, j) = -data[i][j];
        return M1;
    }
    // Оператор вычитания матриц
    TMatrix TMatrix::operator - (const TMatrix& arg) const {
#ifdef _DEBUG
        if ((n != arg.n) || (m != arg.m))
            throw 1;
#endif
        TMatrix M2(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                M2(i, j) = data[i][j] - arg(i, j);
        return M2;
    }
    // Функция транспонирования матриц
    TMatrix TMatrix::t() const {
        TMatrix M3(m, n);
        TMatrix M3help(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                M3help(i, j) = data[i][j];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                M3(i, j) = M3help(j, i);
            }
        }
        return M3;
    }
    // Оператор умножения матрицы на число
    TMatrix TMatrix::operator * (double arg) const {
        TMatrix M4(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                M4(i, j) = data[i][j] * arg;
        return M4;
    }
    // Оператор умножения матриц
    TMatrix TMatrix::operator * (const TMatrix& arg) const {
#ifdef _DEBUG
        if ((n != arg.n) || (m != arg.m))
            throw 1;
#endif
        TMatrix M5(m, n);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                M5(i, j) = 0;
                for (int k = 0; k < m; k++)
                    M5(i, j) += data[i][k] * arg(k, j);
            }
        }
        return M5;
    }
    // Функция перестановки строк
    TMatrix TMatrix::swapRows(int i, int j) {

        double temp;
        for (int k = 0; k < n; k++)
            for (int l = 0; l < m; l++)
                if (k == i)
                {
                    temp = data[k][l];
                    data[i][l] = data[j][l];
                    data[j][l] = temp;
                }
        return *this;
    }

    // Оператор обращения матриц (метод Гаусса)
    TMatrix TMatrix::appeal() const {

        TMatrix M8(n, m);
        TMatrix M9(n, m);
        M8 = *this;
        double temp;
        M9 = E(n);
        for (int k = 0; k < n; k++)
        {

            if (M8(k, k) == 0) {
                for (int t = k + 1; t < n; t++)
                {
                    if (M8(t, k) != 0) {
                        M8 = M8.swapRows(k, t);
                    }
                }
            }
            temp = M8(k, k);
            for (int j = 0; j < m; j++)
            {
                M8(k, j) /= temp;
                M9(k, j) /= temp;
            }
            for (int i = k + 1; i < n; i++)
            {
                temp = M8(i, k);
                for (int j = 0; j < n; j++)
                {
                    M8(i, j) -= M8(k, j) * temp;
                    M9(i, j) -= M9(k, j) * temp;
                }
            }
            for (int s = n - 1; s > 0; s--)
            {
                for (int i = s - 1; i >= 0; i--)
                {
                    temp = M8(i, s);
                    for (int j = 0; j < n; j++)
                    {
                        M8(i, j) -= M8(s, j) * temp;
                        M9(i, j) -= M9(s, j) * temp;
                    }
                }
            }
        }

        return M9;

    }
    //Оператор умножения матрицы на вектор
    TVector TMatrix::operator * (const TVector& arg) const {
#ifdef _DEBUG
        if ((m != arg.size()))
            throw 1;
#endif
        TVector V7(n);
        V7[0] = 0; V7[1] = 0; V7[2] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                V7[i] += data[i][j] * arg[j];
            }
        }
        return V7;
    }
    //Дружественная функция - оператор умножения числа на матрицу
    TMatrix operator * (double lvalue, const TMatrix& rvalue) {
        TMatrix M10(rvalue.n, rvalue.m);
        for (int i = 0; i < rvalue.n; i++) {
            for (int j = 0; j < rvalue.m; j++) {
                M10(i, j) = lvalue * rvalue.data[i][j];
            }
        }
        return M10;
    }

    // Кватернионы
    // Конструктор по умолчанию
    TQuaternion::TQuaternion() : q0(0), Q(3) {}
    // Конструктор по компонентам кватерниона
    TQuaternion::TQuaternion(double q0, double q1, double q2, double q3)
        : q0(q0), Q(3) {
        Q[0] = q1; Q[1] = q2; Q[2] = q3;
    }
    // Конструктор по углу поворота (радианы) и оси вращения
    TQuaternion::TQuaternion(double phi, const TVector& e) {
        q0 = cos(phi / 2);
        TVector temp(3);
        temp = e.norm();
        Q = temp * sin(phi / 2);
    }
    // Конструктор копирования
    TQuaternion::TQuaternion(const TQuaternion& rvalue) { *this = rvalue; }
    // Оператор присваивания
    TQuaternion& TQuaternion::operator = (const TQuaternion& rvalue) {
        if (this != &rvalue) {
            q0 = rvalue.q0;
            Q = rvalue.Q;
        }
        return *this;
    }
    // Оператор сложения кватернионов
    TQuaternion TQuaternion::operator + (const TQuaternion& arg) const {
        TQuaternion L;
        L.q0 = q0 + arg.q0;
        L.Q = Q + arg.Q;
        return L;
    }
    // Оператор вычитания кватернионов
    TQuaternion TQuaternion::operator - (const TQuaternion& arg) const {
        TQuaternion L;
        L.q0 = q0 - arg.q0;
        L.Q = Q - arg.Q;
        return L;
    }

    // Оператор умножения кватернионов
    TQuaternion TQuaternion::operator * (const TQuaternion& arg) const {
        TQuaternion L;
        L.q0 = q0 * arg.q0 - Q * arg.Q;
        L.Q = Q * arg.q0 + arg.Q * q0 + (Q ^ arg.Q);
        return L;
    }
    // Функция нахождения нормы кватерниона
    double TQuaternion::norma() {
        TQuaternion L;
        double norm = 0;
        norm = q0 * q0 + Q * Q;
        return pow(norm, 0.5);
    }
    // Функция нормирования кватерниона
    TQuaternion TQuaternion::norm() {
        TQuaternion L;
        L.q0 = q0;
        L.Q = Q;
        double module = L.norma();
        L.q0 = q0 / module;
        for (int i = 0; i < 3; i++)
            L.Q[i] = Q[i] / module;
        return L;
    }
    //Функция получения элемента по индексу
    double TQuaternion::index(int i) {
        double el;
        if (i == 0)
            el = q0;
        else
            el = Q[i];
        return el;
    }
    //Функция получения сопряженного кватерниона
    TQuaternion TQuaternion::conj() const {
        TQuaternion L;
        L.q0 = q0;
        L.Q = -Q;
        return L;
    }
    TQuaternion TQuaternion::appeal() {
        TQuaternion L;
        L.q0 = q0;
        L.Q = -Q;
        L.q0 = L.q0 / L.norma();
        L.Q[1] = L.Q[1] / L.norma();
        L.Q[2] = L.Q[2] / L.norma();
        L.Q[3] = L.Q[3] / L.norma();
        return L;
    }
    // Оператор умножения кватерниона на вектор
    TQuaternion TQuaternion::operator * (const TVector& arg) const {
        TQuaternion L(0, arg[0], arg[1], arg[2]);
        return (*this) * L;
    }
    // Оператор умножения кватерниона на число
    TQuaternion TQuaternion::operator * (double arg) const {
        TQuaternion L;
        L.q0 = q0 * arg;
        L.Q = Q * arg;
        return L;
    }
    // Поворот вектора вокруг заданной оси на заданный угол при помощи формулы Родрига
    TVector TVector::rotateByRodrigFormula(double phi, const TVector& axis1) const {
        TVector V(n);
        TVector axis(n);
        axis = axis1.norm();
        phi = phi / 180 * M_PI;

        V = axis * (*this) * (1 - cos(phi)) * axis + (axis ^ (*this)) * sin(phi) + (*this) * cos(phi);

        return V;
    }
    // Оператор обращения кватерниона
    //TQuaternion TQuaternion::operator ! () const {
    //	TQuaternion L;
    //	double nor = 1 / L.norma();

    //	L = L.conj();

    //	L = L * nor;
    //	return L;
    //}
    TQuaternion TQuaternion::operator ! () const {
        TQuaternion L = this->conj();
        double norm = 1 / L.norma();   // Вычисляем норму

        return L * norm;
    }
    // Поворот вектора при помощи заданного кватерниона

    TVector TVector::rotateByQuaternion(const TQuaternion& L) const {
        TVector V(n);
        /*TQuaternion P = !L;*/
        V = (L * (*this) * !L).vect();
        return V;
    }
    // Поворот вектора вокруг заданной оси на заданный угол при помощи кватерниона
    TVector TVector::rotate(double phi, const TVector& axis) const {
        TVector V(n);
        phi = phi / 180 * M_PI;
        TQuaternion L(phi, axis);
        V = (L * (*this) * !L).vect();
        return V;
    }
    // Вывод кватерниона
    void TQuaternion::print() {
        setlocale(LC_ALL, "Russian");
        //std::cout << std::endl << "Полученный кватернион: " << std::endl;
        std::cout << q0 << " ";
        for (int i = 0; i < 3; i++)
            std::cout << Q[i] << " ";
    }
    // Вывод вектора
    void TVector::print() {
        setlocale(LC_ALL, "Russian");
        for (int i = 0; i < 3; i++)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }
    // Вывод матрицы
    void TMatrix::print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << data[i][j] << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
