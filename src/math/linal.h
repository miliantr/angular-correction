#pragma once
#pragma once
namespace LinearAlgebra
{
	class TMatrix;
	class TQuaternion;
	class TVector {
	protected:
		// Размерность вектора
		int n;
		// Элементы вектора
		double* data;
	public:
		// Конструктор по умолчанию
		TVector();
		// Конструктор с заданным кол-вом элементов
		TVector(int n);
		// Конструктор копий
		TVector(const TVector& rvalue);
		// Оператор присваивания
		TVector& operator = (const TVector& rvalue);
		// Деструктор
		virtual ~TVector();
		// Функция получение кол-ва элементов вектора
		inline int size() const { return n; }
		// Функция получения индекса последнего элемента
		inline int high() const { return n - 1; }
		// Функция задания кол-ва элементов вектора
		void resize(int n);
		// Оператор доступа к элементам вектора
		inline double& operator[](int i) { return data[i]; }
		// Оператор константного доступа к элементам вектора
		inline const double& operator[](int i) const { return data[i]; }
		// Оператор - унарный минус
		TVector operator - () const;
		// Оператор вычитания векторов
		TVector operator - (const TVector& arg) const;
		// Оператор сложения векторов
		TVector operator + (const TVector& arg) const;
		// Оператор умножения вектора на число
		TVector operator * (double arg) const;
		// Оператор скалярного умножения векторов
		double operator * (const TVector& arg) const;
		// Оператор умножения вектора на матрицу
		TVector operator * (const TMatrix& arg) const;
		// Оператор умножения вектора на кватернион
		//TQuaternion operator * (const TQuaternion& arg) const;
		// Оператор векторного умножения векторов
		TVector operator ^ (const TVector& arg) const;
		// Дружественная функция - оператор умножения числа на вектор
		friend TVector operator * (double lvalue, const TVector& rvalue);
		// Функция получения модуля вектора
		double length() const;
		// Функция вывода вектора
		void print();
		// Функция нормирования вектора
		TVector norm() const;
		// Поворот вектора вокруг заданной оси на заданный угол при помощи формулы Родрига
		TVector rotateByRodrigFormula(double phi, const TVector& axis) const;
		// Поворот вектора вокруг заданной оси на заданный угол при помощи кватерниона
		TVector rotate(double phi, const TVector& axis) const;
		// Поворот векора при помощи заданного кватерниона
		TVector rotateByQuaternion(const TQuaternion& L) const;
	};




	// Объявление класса матриц
	class TMatrix {
	protected:
		// Размерность матрицы (число строк и столбцов)
		int n, m;
		// Элементы матрицы
		double** data;
	public:
		// Конструктор по умолчанию
		TMatrix();
		// Конструктор с заданной размерностью
		TMatrix(int n, int m);
		// Конструктор копий
		TMatrix(const TMatrix& rvalue);
		// Оператор присваивания
		TMatrix& operator = (const TMatrix& rvalue);
		// Деструктор
		virtual ~TMatrix();

		void print();
		// Функция получения количества строк
		inline int rowCount() const { return n; }
		// Функция получения кол-ва столбцов
		inline int colCount() const { return m; }
		// Функция получения индекса последней строки
		inline int rowHigh() const { return n - 1; }
		// Функция получения индекса последнего столбца
		inline int colHigh() const { return m - 1; }
		// Функция задания размерности
		void resize(int n, int m);
		// Оператор доступа к элементам матрицы
		inline double& operator()(int i, int j) { return data[i][j]; }
		// Оператор константного доступа к элементам вектора
		inline const double& operator()(int i, int j) const { return data[i][j]; }
		// Оператор - унарный минус
		TMatrix operator - () const;
		// Оператор вычитания матриц
		TMatrix operator - (const TMatrix& arg) const;
		// Оператор сложения матриц
		TMatrix operator + (const TMatrix& arg) const;
		// Оператор умножения матрицы на число
		TMatrix operator * (double arg) const;
		// Оператор умножения матриц
		TMatrix operator * (const TMatrix& arg) const;
		// Оператор умножения матрицы на вектор
		TVector operator * (const TVector& arg) const;
		// Дружественная функция - оператор умножения числа на матрицу
		friend TMatrix operator * (double lvalue, const TMatrix& rvalue);
		// Оператор обращения матриц (метод Гаусса)
		TMatrix appeal() const;

		// Функция транспонирования
		TMatrix t() const;
		// Функция формирования единичной матрицы
		static TMatrix E(int n);
		// Функция перестановки строк
		TMatrix swapRows(int i, int j);
	};
	class TQuaternion {
	protected:
		// Скалярная часть
		double q0;
		// Векторная часть
		TVector Q;
	public:
		// Конструктор по умолчанию
		TQuaternion();
		// Конструктор по компонентам кватерниона
		TQuaternion(double l0, double l1, double l2, double l3);
		// Конструктор по углу поворота (рад.) и оси вращения
		TQuaternion(double phi, const TVector& e);
		// Конструктор копирования
		TQuaternion(const TQuaternion& rvalue);
		// Оператор присваивания
		TQuaternion& operator = (const TQuaternion& rvalue);
		// Оператор вычитания кватернионов
		TQuaternion operator - (const TQuaternion& arg) const;
		// Оператор сложения кватернионов
		TQuaternion operator + (const TQuaternion& arg) const;
		// Оператор умножения кватернионов
		TQuaternion operator * (const TQuaternion& arg) const;
		// Оператор умножения кватерниона на вектор
		TQuaternion operator * (const TVector& arg) const;
		// Оператор умножения кватерниона на число
		TQuaternion operator * (double arg) const;
		// Дружественная функция - оператор умножения числа на кватернион
		friend TQuaternion operator * (double lvalue, const TQuaternion&
			rvalue);
		// Оператор обращения кватерниона
		TQuaternion operator ! () const;
		// Доступ к скалярной части
		inline double scal() const { return q0; }
		// Доступ к векторной части
		inline TVector vect() const { return Q; }
		// Функция нахождения нормы кватерниона
		double norma();
		//Функция получения элемента по индексу
		double index(int i);
		// Функция вывода кватерниона
		void print();
		// Функция нормирования кватерниона
		TQuaternion norm();
		// Функция получения сопряженного кватерниона
		TQuaternion conj() const;
        TQuaternion appeal();
	};
}
