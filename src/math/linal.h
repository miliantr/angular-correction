#pragma once
#pragma once
namespace LinearAlgebra
{
	class TMatrix;
	class TQuaternion;
	class TVector {
	protected:
		// ����������� �������
		int n;
		// �������� �������
		double* data;
	public:
		// ����������� �� ���������
		TVector();
		// ����������� � �������� ���-��� ���������
		TVector(int n);
		// ����������� �����
		TVector(const TVector& rvalue);
		// �������� ������������
		TVector& operator = (const TVector& rvalue);
		// ����������
		virtual ~TVector();
		// ������� ��������� ���-�� ��������� �������
		inline int size() const { return n; }
		// ������� ��������� ������� ���������� ��������
		inline int high() const { return n - 1; }
		// ������� ������� ���-�� ��������� �������
		void resize(int n);
		// �������� ������� � ��������� �������
		inline double& operator[](int i) { return data[i]; }
		// �������� ������������ ������� � ��������� �������
		inline const double& operator[](int i) const { return data[i]; }
		// �������� - ������� �����
		TVector operator - () const;
		// �������� ��������� ��������
		TVector operator - (const TVector& arg) const;
		// �������� �������� ��������
		TVector operator + (const TVector& arg) const;
		// �������� ��������� ������� �� �����
		TVector operator * (double arg) const;
		// �������� ���������� ��������� ��������
		double operator * (const TVector& arg) const;
		// �������� ��������� ������� �� �������
		TVector operator * (const TMatrix& arg) const;
		// �������� ��������� ������� �� ����������
		//TQuaternion operator * (const TQuaternion& arg) const;
		// �������� ���������� ��������� ��������
		TVector operator ^ (const TVector& arg) const;
		// ������������� ������� - �������� ��������� ����� �� ������
		friend TVector operator * (double lvalue, const TVector& rvalue);
		// ������� ��������� ������ �������
		double length() const;
		// ������� ������ �������
		void print();
		// ������� ������������ �������
		TVector norm() const;
		// ������� ������� ������ �������� ��� �� �������� ���� ��� ������ ������� �������
		TVector rotateByRodrigFormula(double phi, const TVector& axis) const;
		// ������� ������� ������ �������� ��� �� �������� ���� ��� ������ �����������
		TVector rotate(double phi, const TVector& axis) const;
		// ������� ������ ��� ������ ��������� �����������
		TVector rotateByQuaternion(const TQuaternion& L) const;
	};




	// ���������� ������ ������
	class TMatrix {
	protected:
		// ����������� ������� (����� ����� � ��������)
		int n, m;
		// �������� �������
		double** data;
	public:
		// ����������� �� ���������
		TMatrix();
		// ����������� � �������� ������������
		TMatrix(int n, int m);
		// ����������� �����
		TMatrix(const TMatrix& rvalue);
		// �������� ������������
		TMatrix& operator = (const TMatrix& rvalue);
		// ����������
		virtual ~TMatrix();

		void print();
		// ������� ��������� ���������� �����
		inline int rowCount() const { return n; }
		// ������� ��������� ���-�� ��������
		inline int colCount() const { return m; }
		// ������� ��������� ������� ��������� ������
		inline int rowHigh() const { return n - 1; }
		// ������� ��������� ������� ���������� �������
		inline int colHigh() const { return m - 1; }
		// ������� ������� �����������
		void resize(int n, int m);
		// �������� ������� � ��������� �������
		inline double& operator()(int i, int j) { return data[i][j]; }
		// �������� ������������ ������� � ��������� �������
		inline const double& operator()(int i, int j) const { return data[i][j]; }
		// �������� - ������� �����
		TMatrix operator - () const;
		// �������� ��������� ������
		TMatrix operator - (const TMatrix& arg) const;
		// �������� �������� ������
		TMatrix operator + (const TMatrix& arg) const;
		// �������� ��������� ������� �� �����
		TMatrix operator * (double arg) const;
		// �������� ��������� ������
		TMatrix operator * (const TMatrix& arg) const;
		// �������� ��������� ������� �� ������
		TVector operator * (const TVector& arg) const;
		// ������������� ������� - �������� ��������� ����� �� �������
		friend TMatrix operator * (double lvalue, const TMatrix& rvalue);
		// �������� ��������� ������ (����� ������)
		TMatrix appeal() const;

		// ������� ����������������
		TMatrix t() const;
		// ������� ������������ ��������� �������
		static TMatrix E(int n);
		// ������� ������������ �����
		TMatrix swapRows(int i, int j);
	};
	class TQuaternion {
	protected:
		// ��������� �����
		double q0;
		// ��������� �����
		TVector Q;
	public:
		// ����������� �� ���������
		TQuaternion();
		// ����������� �� ����������� �����������
		TQuaternion(double l0, double l1, double l2, double l3);
		// ����������� �� ���� �������� (���.) � ��� ��������
		TQuaternion(double phi, const TVector& e);
		// ����������� �����������
		TQuaternion(const TQuaternion& rvalue);
		// �������� ������������
		TQuaternion& operator = (const TQuaternion& rvalue);
		// �������� ��������� ������������
		TQuaternion operator - (const TQuaternion& arg) const;
		// �������� �������� ������������
		TQuaternion operator + (const TQuaternion& arg) const;
		// �������� ��������� ������������
		TQuaternion operator * (const TQuaternion& arg) const;
		// �������� ��������� ����������� �� ������
		TQuaternion operator * (const TVector& arg) const;
		// �������� ��������� ����������� �� �����
		TQuaternion operator * (double arg) const;
		// ������������� ������� - �������� ��������� ����� �� ����������
		friend TQuaternion operator * (double lvalue, const TQuaternion&
			rvalue);
		// �������� ��������� �����������
		TQuaternion operator ! () const;
		// ������ � ��������� �����
		inline double scal() const { return q0; }
		// ������ � ��������� �����
		inline TVector vect() const { return Q; }
		// ������� ���������� ����� �����������
		double norma();
		//������� ��������� �������� �� �������
		double index(int i);
		// ������� ������ �����������
		void print();
		// ������� ������������ �����������
		TQuaternion norm();
		// ������� ��������� ������������ �����������
		TQuaternion conj() const;
        TQuaternion appeal();
	};
}
