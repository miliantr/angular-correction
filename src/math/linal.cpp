#define _USE_MATH_DEFINES

#include <cstring>
#include <math.h>
#include <iostream>

#include "linal.h"

namespace LinearAlgebra {
    // �������


    // ����������� �� ���������
    TVector::TVector() : n(0), data(NULL) {}
    // ����������� �� ���������� ���������
    TVector::TVector(int n) : n(0), data(NULL) {
        resize(n);
    }
    // ����������� �����������
    TVector::TVector(const TVector& rvalue) : n(0), data(NULL) {
        (*this) = rvalue;
    }
    // �������� ������������
    TVector& TVector::operator = (const TVector& rvalue) {
        // ���� ����� ������� �� ��������� � ������
        if (this != &rvalue) {
            // ���� ������ ������ �������� �� ��������� � ������, �� ������ ���������� ������
            if (n != rvalue.n) {
                // ���� ������ ��� ���� ��������, ������� �
                if (data) { delete[] data; }
                // ��������� ����� ������
                data = new double[rvalue.n];
                // ���������� ������ �������
                n = rvalue.n;
            }
            // ������� ������ �� ������� �������� � �����
            memcpy(data, rvalue.data, sizeof(double) * n);
        }
        // ������� ������ �� ����� ������� ��� ����������� ������� ������������
        return *this;
    }
    // ����������
    TVector::~TVector() {
        // ���� ���� ������ ����� ��� ���������������, ������� ���
        if (data) {
            delete[] data;
            n = 0;
            data = NULL;
        }
    }
    // ������� ������� ���-�� ��������� �������
    void TVector::resize(int n) {
#ifdef _DEBUG
        if (n < 0)
            throw 1;
#endif
        // ���� ����� ������ ��������� �� ������ - �������
        if (n == this->n) return;
        // ����� ���� ������
        double* newData = new double[n];
        // ���� ���� ������ ����� ��� ���������������...
        if (data) {
            // ����������� �� ������� � ������ ������� �����
            int min_n = (this->n < n) ? this->n : n;
            // ������� ������ �� ������� ����� � �����
            memcpy(newData, data, sizeof(double) * min_n);
            // �������� ������� �����
            delete[] data;
        }
        // ������������ ������ ����� � ������� �������
        data = newData;
        // ���������� ������ �������
        this->n = n;
    }
    // �������� �������� ��������
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
    // �������� ��������� ������� �� �����
    TVector TVector::operator * (double arg) const {
        TVector V1(n);
        for (int i = 0; i < n; i++)
            V1[i] = data[i] * arg;
        return V1;
    }
    // �������� ���������� ��������� ��������
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
    // �������� ��������� ��������
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
    // �������� - ������� �����
    TVector TVector::operator - () const {
        TVector V3(n);
        for (int i = 0; i < n; i++)
            V3[i] = -data[i];
        return V3;
    }
    // ������� ��������� ������ �������
    double TVector::length() const {
        double len = 0;
        for (int i = 0; i < n; i++)
        {
            len += data[i] * data[i];
        }
        len = sqrt(len);
        return len;
    }
    // ������� ������������ �������
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
    // �������� ��������� ������� �� �������
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
    // ������������� ������� - �������� ��������� ����� �� ������
    TVector operator * (double lvalue, const TVector& rvalue) {
        TVector V7(rvalue.n);
        for (int i = 0; i < rvalue.n; i++)
            V7[i] = lvalue * rvalue.data[i];
        return V7;
    }
    // �������� ���������� ��������� ��������
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



    // �������
    // ����������� �� ���������
    TMatrix::TMatrix() : n(0), m(0), data(NULL) {}
    // ����������� � �������� ������������
    TMatrix::TMatrix(int n, int m) : n(0), m(0), data(NULL) { resize(n, m); }
    // ����������� �����
    TMatrix::TMatrix(const TMatrix& rvalue) : n(0), m(0), data(NULL) {
        (*this) = rvalue;
    }
    // �������� ������������
    TMatrix& TMatrix::operator = (const TMatrix& rvalue) {
        // ���� ����� ������� �� ��������� � ������
        if (this != &rvalue) {
            // �������� ����� ���������� ������
            this->~TMatrix();
            // ��������� ����� ������ �� �������� ������� ��������
            resize(rvalue.n, rvalue.m);
            // ������� ������ �� ������� �������� � ����� ���������
            for (int i = 0; i < n; i++)
                memcpy(data[i], rvalue.data[i], sizeof(double) * m);
        }
        // ������� ������ �� ����� ������� ��� ����������� ������� ������������
        return (*this);
    }
    // ���������� ������� �������
    TMatrix::~TMatrix() {
        if (data) {
            for (int i = 0; i < n; i++)
                delete[] data[i];
            delete[] data;
            data = NULL;
            n = m = 0;
        }
    }
    // ������� ������� ����������� �������
    void TMatrix::resize(int n, int m) {
        // ���-�� �����, ������� ����� ��������� � ����� ����� ������
        int min_n = this->n < n ? this->n : n;
        // ���� ���-�� �������� �� ���������
        if (this->m != m) {
            // ���-�� ��������, ������� ����� ��������� � ����� ����� ������
            int min_m = this->m < m ? this->m : m;
            // ���� ����������� �������� ������ � ����� �����
            for (int i = 0; i < min_n; i++) {
                // �������� ������ �����-������
                double* newDataRow = new double[m];
                // ������� ������ � ����� ����-������
                memcpy(newDataRow, data[i], sizeof(double) * min_m);
                // �������� ������� ����� ������ �� ���� �����
                delete[] data[i];
                // ������������ ������ �����-������ �� ������ �����
                data[i] = newDataRow;
            }
            // ���������� ������ �������
            this->m = m;
        }
        // ���� ���-�� ����� �� ���������
        if (this->n != n) {
            // �������� ������ �����-����������
            double** newData = new double* [n];
            // ������� ����������� ������� ���������� � �����
            memcpy(newData, data, sizeof(double*) * min_n);
            // �������� ������ ����� �� ������� ����������
            for (int i = n; i < this->n; i++) { delete[] data[i]; }
            // �������� ������� ����������
            if (data) { delete[] data; }
            // �������� ����������� ����� � ����� ����������
            for (int i = this->n; i < n; i++) { newData[i] = new double[m]; }
            // �������� ������� ���������� � ������
            data = newData;
            this->n = n;
        }
    }
    // �������� �������� ������
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
    // ������������ ������� ��� ������������ ��������� �������
    TMatrix TMatrix::E(int n) {
        TMatrix E(n, n);
        for (int i = 0; i < n; i++) {
            E(i, i) = 1;
            for (int j = i + 1; j < n; j++) { E(i, j) = E(j, i) = 0; }
        }
        return E;
    }
    // �������� - ������� �����
    TMatrix TMatrix::operator - () const {
        TMatrix M1(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                M1(i, j) = -data[i][j];
        return M1;
    }
    // �������� ��������� ������
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
    // ������� ���������������� ������
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
    // �������� ��������� ������� �� �����
    TMatrix TMatrix::operator * (double arg) const {
        TMatrix M4(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                M4(i, j) = data[i][j] * arg;
        return M4;
    }
    // �������� ��������� ������
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
    // ������� ������������ �����
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

    // �������� ��������� ������ (����� ������)
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
    //�������� ��������� ������� �� ������
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
    //������������� ������� - �������� ��������� ����� �� �������
    TMatrix operator * (double lvalue, const TMatrix& rvalue) {
        TMatrix M10(rvalue.n, rvalue.m);
        for (int i = 0; i < rvalue.n; i++) {
            for (int j = 0; j < rvalue.m; j++) {
                M10(i, j) = lvalue * rvalue.data[i][j];
            }
        }
        return M10;
    }

    // �����������
    // ����������� �� ���������
    TQuaternion::TQuaternion() : q0(0), Q(3) {}
    // ����������� �� ����������� �����������
    TQuaternion::TQuaternion(double q0, double q1, double q2, double q3)
        : q0(q0), Q(3) {
        Q[0] = q1; Q[1] = q2; Q[2] = q3;
    }
    // ����������� �� ���� �������� (�������) � ��� ��������
    TQuaternion::TQuaternion(double phi, const TVector& e) {
        q0 = cos(phi / 2);
        TVector temp(3);
        temp = e.norm();
        Q = temp * sin(phi / 2);
    }
    // ����������� �����������
    TQuaternion::TQuaternion(const TQuaternion& rvalue) { *this = rvalue; }
    // �������� ������������
    TQuaternion& TQuaternion::operator = (const TQuaternion& rvalue) {
        if (this != &rvalue) {
            q0 = rvalue.q0;
            Q = rvalue.Q;
        }
        return *this;
    }
    // �������� �������� ������������
    TQuaternion TQuaternion::operator + (const TQuaternion& arg) const {
        TQuaternion L;
        L.q0 = q0 + arg.q0;
        L.Q = Q + arg.Q;
        return L;
    }
    // �������� ��������� ������������
    TQuaternion TQuaternion::operator - (const TQuaternion& arg) const {
        TQuaternion L;
        L.q0 = q0 - arg.q0;
        L.Q = Q - arg.Q;
        return L;
    }

    // �������� ��������� ������������
    TQuaternion TQuaternion::operator * (const TQuaternion& arg) const {
        TQuaternion L;
        L.q0 = q0 * arg.q0 - Q * arg.Q;
        L.Q = Q * arg.q0 + arg.Q * q0 + (Q ^ arg.Q);
        return L;
    }
    // ������� ���������� ����� �����������
    double TQuaternion::norma() {
        TQuaternion L;
        double norm = 0;
        norm = q0 * q0 + Q * Q;
        return pow(norm, 0.5);
    }
    // ������� ������������ �����������
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
    //������� ��������� �������� �� �������
    double TQuaternion::index(int i) {
        double el;
        if (i == 0)
            el = q0;
        else
            el = Q[i];
        return el;
    }
    //������� ��������� ������������ �����������
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
    // �������� ��������� ����������� �� ������
    TQuaternion TQuaternion::operator * (const TVector& arg) const {
        TQuaternion L(0, arg[0], arg[1], arg[2]);
        return (*this) * L;
    }
    // �������� ��������� ����������� �� �����
    TQuaternion TQuaternion::operator * (double arg) const {
        TQuaternion L;
        L.q0 = q0 * arg;
        L.Q = Q * arg;
        return L;
    }
    // ������� ������� ������ �������� ��� �� �������� ���� ��� ������ ������� �������
    TVector TVector::rotateByRodrigFormula(double phi, const TVector& axis1) const {
        TVector V(n);
        TVector axis(n);
        axis = axis1.norm();
        phi = phi / 180 * M_PI;

        V = axis * (*this) * (1 - cos(phi)) * axis + (axis ^ (*this)) * sin(phi) + (*this) * cos(phi);

        return V;
    }
    // �������� ��������� �����������
    //TQuaternion TQuaternion::operator ! () const {
    //	TQuaternion L;
    //	double nor = 1 / L.norma();

    //	L = L.conj();

    //	L = L * nor;
    //	return L;
    //}
    TQuaternion TQuaternion::operator ! () const {
        TQuaternion L = this->conj();
        double norm = 1 / L.norma();   // ��������� �����

        return L * norm;
    }
    // ������� ������� ��� ������ ��������� �����������

    TVector TVector::rotateByQuaternion(const TQuaternion& L) const {
        TVector V(n);
        /*TQuaternion P = !L;*/
        V = (L * (*this) * !L).vect();
        return V;
    }
    // ������� ������� ������ �������� ��� �� �������� ���� ��� ������ �����������
    TVector TVector::rotate(double phi, const TVector& axis) const {
        TVector V(n);
        phi = phi / 180 * M_PI;
        TQuaternion L(phi, axis);
        V = (L * (*this) * !L).vect();
        return V;
    }
    // ����� �����������
    void TQuaternion::print() {
        setlocale(LC_ALL, "Russian");
        //std::cout << std::endl << "���������� ����������: " << std::endl;
        std::cout << q0 << " ";
        for (int i = 0; i < 3; i++)
            std::cout << Q[i] << " ";
    }
    // ����� �������
    void TVector::print() {
        setlocale(LC_ALL, "Russian");
        for (int i = 0; i < 3; i++)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }
    // ����� �������
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
