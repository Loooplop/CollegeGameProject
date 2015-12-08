#pragma once
#include <iostream>
#include "WE_Vector.h"
using namespace std;
template<typename T>
class mat2
{
#define  mat2s mat2<short>
#define  mat2d mat2<double>
#define  mat2i mat2<int>
#define  mat2f mat2<float>
public:
	mat2()
	{

	};
	mat2(T TopLeft, T TopRight,
		T BottomLeft, T BottomRight)
	{
		M[0] = TopLeft; M[1] = TopRight;
		M[2] = BottomLeft; M[3] = BottomRight;
	}
	~mat2()
	{
		
	}

	mat2<T> operator +(mat2<T> &other)
	{
		return mat2<T>(M[0]+other.getElement(0,0),M[1]+other.getElement(1,0),
			           M[2] + other.getElement(0, 1), M[3] + other.getElement(1, 1));
	}
	mat2<T> operator -(mat2<T> &other)
	{
		return mat2<T>(M[0] - other.getElement(0, 0), M[1] - other.getElement(1, 0),
			M[2] - other.getElement(0, 1), M[3] - other.getElement(1, 1));
	}
	mat2<T> operator *(mat2<T> &other)
	{
		vec2<T> row1(M[0], M[1]);
		vec2<T> row2(M[2], M[3]);

		vec2<T> column1(other.getElement(0, 0), other.getElement(0, 1));
		vec2<T> column2(other.getElement(1, 0), other.getElement(1, 1));

		return mat2<T>(row1.DotProduct(column1), row1.DotProduct(column2),
			           row2.DotProduct(column1), row2.DotProduct(column2));
	}
	vec2<T> operator *(vec2<T> &other)
	{
		return vec2<T>(M[0] * other.getX() + M[1] * other.getY(), M[2] * other.getX() + M[3] * other.getY());
	}
	mat2<T> operator /(mat2<T> &other)
	{
		return (*this)*other.getInverse();
	}
	mat2<T> getInverse()
	{
		if ((M[0] * M[3] - M[1] * M[2]) == 0)
		{
			cerr << "Error: 2x2 Matrix Determinant is Zero";
			return mat2<T>(1,0,0,1);
		}
		T determinant = (T)1 / (M[0] * M[3] - M[1] * M[2]);
		return  mat2<T>(M[3], -M[1],
			-M[2], M[0])*mat2<T>(determinant, 0, 0, determinant);
	}
	void invertMatrix()
	{
		mat2<T> temp = getInverse();
		for (int y = 0; y < 2; y++)
			for (int x = 0; x < 2; x++)
				SetElement(temp.getElement(x, y), x, y);

	}
	T getElement(int Column, int row)
	{
		return M[row * 2 + Column];
	}
	void SetElement(T element, int Column, int Row)
	{
		M[Row * 2 + Column] = element;
	}
	T* getArray()
	{
		return M;
	}
	template<typename T>
	friend std::ostream& operator<< (std::ostream &out, mat2<T> &Vector);

private:
	T M[4];
};
template<typename T>
std::ostream& operator<< (std::ostream &out, mat2<T> &Vector)
{
	out << Vector.M[0] << ", " << Vector.M[1]<<endl<<
		   Vector.M[2] << ", " << Vector.M[3];
	return out;
};

template<typename T>
class mat3
{

#define  mat3s mat3<short>
#define  mat3d mat3<double>
#define  mat3i mat3<int>
#define  mat3f mat3<float>
public:
	mat3()
	{

	};
	mat3(T TopLeft, T TopMiddle,T TopRight,
		 T MiddleLeft,T MiddleMiddle ,T MiddleRight,
		 T BottomLeft, T BottomMiddle, T BottomRight)
	{
		M[0] = TopLeft;    M[1] = TopMiddle;    M[2] = TopRight;
		M[3] = MiddleLeft; M[4] = MiddleMiddle; M[5] = MiddleRight;
		M[6] = BottomLeft; M[7] = BottomMiddle; M[8] = BottomRight;
	}
	~mat3()
	{
		
	}

	mat3<T> operator +(mat3<T> &other)
	{
		return mat3<T>(M[0] + other.getElement(0, 0), M[1] + other.getElement(1, 0), M[2] + other.getElement(2, 0),
			           M[5] + other.getElement(0, 1), M[4] + other.getElement(1, 1), M[5] + other.getElement(2, 1),
					   M[6] + other.getElement(0, 2), M[7] + other.getElement(1, 2), M[8] + other.getElement(2, 2),
					   );
	}
	mat3<T> operator -(mat3<T> &other)
	{
		return mat3<T>(M[0] - other.getElement(0, 0), M[1] - other.getElement(1, 0), M[2] - other.getElement(2, 0),
			           M[5] - other.getElement(0, 1), M[4] - other.getElement(1, 1), M[5] - other.getElement(2, 1),
			           M[6] - other.getElement(0, 2), M[7] - other.getElement(1, 2), M[8] - other.getElement(2, 2),
			);
	}
	mat3<T> operator *(mat3<T> &other)
	{
		vec3<T> row1(M[0], M[1], M[2]);
		vec3<T> row2(M[3], M[4], M[5]);
		vec3<T> row3(M[6], M[7], M[8]);

		vec3<T> column1(other.getElement(0, 0), other.getElement(0, 1), other.getElement(0, 2));
		vec3<T> column2(other.getElement(1, 0), other.getElement(1, 1), other.getElement(1, 2));
		vec3<T> column3(other.getElement(2, 0), other.getElement(2, 1), other.getElement(2, 2));
		return mat3<T>(row1.DotProduct(column1), row1.DotProduct(column2), row1.DotProduct(column3),
			           row2.DotProduct(column1), row2.DotProduct(column2), row2.DotProduct(column3),
					   row3.DotProduct(column1), row3.DotProduct(column2), row3.DotProduct(column3)
			);
	}
	vec3<T> operator *(vec3<T> &other)
	{

		vec3<T> row1(M[0], M[1], M[2]);
		vec3<T> row2(M[3], M[4], M[5]);
		vec3<T> row3(M[6], M[7], M[8]); 
		return vec3<T>(row1.DotProduct(other),row2.DotProduct(other),row3.DotProduct(other));
	}
	mat3<T> operator /(mat3<T> &other)
	{
		return (*this)*other.getInverse();
	}
	mat3<T> getInverse()
	{
		T determinant = (M[0] * M[4] * M[8]) + (M[3] * M[7] * M[2]) + (M[6] * M[1] * M[5]) - (M[0] * M[7] * M[5]) - (M[6] * M[4] * M[2]) - (M[3] * M[1] * M[8]);
		if (determinant == 0)
		{
			cerr << "Error: 3x3 Matrix Determinant is Zero";
			return mat3<T>(1, 0, 0,
				           0, 1, 0,
				           0, 0, 1);
		}
		determinant = (double)1 / determinant;
		return mat3<T>((M[4] * M[8] - M[5] * M[7])*determinant, (M[2] * M[7] - M[1] * M[8])*determinant, (M[1] * M[5] - M[2] * M[4])*determinant,
			           (M[5] * M[6] - M[3] * M[8])*determinant, (M[0] * M[8] - M[2] * M[6])*determinant, (M[2] * M[3] - M[0] * M[5])*determinant,
					   (M[3] * M[7] - M[4] * M[6])*determinant, (M[1] * M[6] - M[0] * M[7])*determinant, (M[0] * M[4] - M[1] * M[3])*determinant
			          );
	}
	void invertMatrix()
	{
		mat3<T> temp = getInverse();
		for (int y = 0; y < 3; y++)
			for (int x = 0; x < 3; x++)
				SetElement(temp.getElement(x, y), x, y);

	}
	T getElement(int Column, int row)
	{
		return M[row * 3 + Column];
	}
	void SetElement(T element, int Column, int Row)
	{
		M[Row * 3 + Column] = element;
	}
	T* getArray()
	{
		return M;
	}
	template<typename T>
	friend std::ostream& operator<< (std::ostream &out, mat3<T> &Vector);

private:
	T M[9];
};
template<typename T>
std::ostream& operator<< (std::ostream &out, mat3<T> &Vector)
{
	out << "Matrix 3x3" << endl<<
		   Vector.M[0] << ", " << Vector.M[1] << ", " << Vector.M[2] << endl <<
		   Vector.M[3] << ", " << Vector.M[4] << ", " << Vector.M[5] << endl <<
		   Vector.M[6] << ", " << Vector.M[7] << ", " << Vector.M[8];
	return out;
};

template<typename T>
class mat4
{

#define  mat4s mat4<short>
#define  mat4d mat4<double>
#define  mat4i mat4<int>
#define  mat4f mat4<float>
   public:
	mat4()
	{
	
	}
	mat4(T TopLeftCorner, T TopLeftMiddle, T TopRightMiddle, T TopRightCorner,
		T TopMiddleLeftCorner, T TopMiddleLeftMiddle, T TopMiddleRightMiddle, T TopMiddleRightCorner,
		T BottomMiddleLeftCorner, T BottomMiddleLeftMiddle, T BottomMiddleRightMiddle, T BottomMiddleRightCorner,
		T BottomLeftCorner, T BottomLeftMiddle, T BottomRightMiddle, T BottomRightCorner)
	{
		M[0] = TopLeftCorner; M[1] = TopLeftMiddle; M[2] = TopRightMiddle; M[3] = TopRightCorner;
		M[4] = TopMiddleLeftCorner; M[5] = TopMiddleLeftMiddle; M[6] = TopMiddleRightMiddle; M[7] = TopMiddleRightCorner;
		M[8] = BottomMiddleLeftCorner; M[9] = BottomMiddleLeftMiddle; M[10] = BottomMiddleRightMiddle; M[11] = BottomMiddleRightCorner;
		M[12] = BottomLeftCorner; M[13] = BottomLeftMiddle; M[14] = BottomRightMiddle; M[15] = BottomRightCorner;
	}
	mat4<T> operator+ (mat4<T> &other)
	{
		return mat4<T>(M[0] + other.getElement(0, 0), M[1] + other.getElement(1, 0), M[2] + other.getElement(2, 0), M[3] + other.getElement(3, 0),
			           M[4] + other.getElement(0, 1), M[5] + other.getElement(1, 1), M[6] + other.getElement(2, 1), M[7] + other.getElement(3, 1),
			           M[8] + other.getElement(0, 2), M[9] + other.getElement(1, 2), M[10] + other.getElement(2, 2), M[11] + other.getElement(3, 2),
			           M[12] + other.getElement(0, 3), M[13] + other.getElement(1, 3), M[14] + other.getElement(2, 3), M[15] + other.getElement(3, 3));
	}
	mat4<T> operator- (mat4<T> &other)
	{
		return mat4<T>(M[0] - other.getElement(0, 0), M[1] - other.getElement(1, 0), M[2] - other.getElement(2, 0), M[3] - other.getElement(3, 0),
			M[4] - other.getElement(0, 1), M[5] - other.getElement(1, 1), M[6] - other.getElement(2, 1), M[7] - other.getElement(3, 1),
			M[8] - other.getElement(0, 2), M[9] - other.getElement(1, 2), M[10] - other.getElement(2, 2), M[11] - other.getElement(3, 2),
			M[12] - other.getElement(0, 3), M[13] - other.getElement(1, 3), M[14] - other.getElement(2, 3), M[15] - other.getElement(3, 3));
	}
	mat4<T> operator* (mat4<T> &other)
	{
		vec4<T> row1(M[0], M[1], M[2], M[3]);
		vec4<T> row2(M[4], M[5], M[6], M[7]);
		vec4<T> row3(M[8], M[9], M[10], M[11]);
		vec4<T> row4(M[12], M[13], M[14], M[15]);

		vec4<T> column1(other.getElement(0, 0), other.getElement(0, 1), other.getElement(0, 2), other.getElement(0, 3));
		vec4<T> column2(other.getElement(1, 0), other.getElement(1, 1), other.getElement(1, 2), other.getElement(1, 3));
		vec4<T> column3(other.getElement(2, 0), other.getElement(2, 1), other.getElement(2, 2), other.getElement(2, 3));
		vec4<T> column4(other.getElement(3, 0), other.getElement(3, 1), other.getElement(3, 2), other.getElement(3, 3));


		return mat4<T>(row1.DotProduct(column1), row1.DotProduct(column2), row1.DotProduct(column3), row1.DotProduct(column4),
			row2.DotProduct(column1), row2.DotProduct(column2), row2.DotProduct(column3), row2.DotProduct(column4),
			row3.DotProduct(column1), row3.DotProduct(column2), row3.DotProduct(column3), row3.DotProduct(column4),
			row4.DotProduct(column1), row4.DotProduct(column2), row4.DotProduct(column3), row4.DotProduct(column4));
	}
	vec4<T> operator* (vec4<T> &other)
	{
		vec4<T> row1(M[0], M[1], M[2], M[3]);
		vec4<T> row2(M[4], M[5], M[6], M[7]);
		vec4<T> row3(M[8], M[9], M[10], M[11]);
		vec4<T> row4(M[12], M[13], M[14], M[15]);

		return vec4<T>(row1.DotProduct(other), row2.DotProduct(other), row3.DotProduct(other), row4.DotProduct(other));
	}
	mat4<T> operator/ (mat4<T> &other)
	{
		return (*this)*other.getInverse();
	}
	mat4<T> getInverse()
	{
		double S0 = M[0] * M[5] - M[1] * M[4];
		double S1 = M[0] * M[6] - M[2] * M[4];
		double S2 = M[0] * M[7] - M[3] * M[4];
		double S3 = M[1] * M[6] - M[2] * M[5];
		double S4 = M[1] * M[7] - M[3] * M[5];
		double S5 = M[2] * M[7] - M[3] * M[6];

		double C5 = M[10] * M[15] - M[11] * M[14];
		double C4 = M[9] * M[15] - M[11] * M[13];
		double C3 = M[9] * M[14] - M[10] * M[13];
		double C2 = M[8] * M[15] - M[11] * M[12];
		double C1 = M[8] * M[14] - M[10] * M[12];
		double C0 = M[8] * M[13] - M[9] * M[12];

		// If deterMinant equals 0, there is no inverse
		double det = S0 * C5 - S1 * C4 + S2 * C3 + S3 * C2 - S4 * C1 + S5 * C0;
		if (det == 0)
		{
			cerr << "Error: 4x4 Matrix Determinant is Zero";
			return mat4<T>(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}
		det = 1.0 / det;
		mat4<T> detMatrix(det, 0, 0, 0,
			0, det, 0, 0,
			0, 0, det, 0,
			0, 0, 0, det);
		// CoMpute adjugate Matrix
		return mat4<T>(
			M[5] * C5 - M[6] * C4 + M[7] * C3, -M[1] * C5 + M[2] * C4 - M[3] * C3,
			M[13] * S5 - M[14] * S4 + M[15] * S3, -M[9] * S5 + M[10] * S4 - M[11] * S3,

			-M[4] * C5 + M[6] * C2 - M[7] * C1, M[0] * C5 - M[2] * C2 + M[3] * C1,
			-M[12] * S5 + M[14] * S2 - M[15] * S1, M[8] * S5 - M[10] * S2 + M[11] * S1,

			M[4] * C4 - M[5] * C2 + M[7] * C0, -M[0] * C4 + M[1] * C2 - M[3] * C0,
			M[12] * S4 - M[13] * S2 + M[15] * S0, -M[8] * S4 + M[9] * S2 - M[11] * S0,

			-M[4] * C3 + M[5] * C1 - M[6] * C0, M[0] * C3 - M[1] * C1 + M[2] * C0,
			-M[12] * S3 + M[13] * S1 - M[14] * S0, M[8] * S3 - M[9] * S1 + M[10] * S0)*detMatrix;
	};
	mat4<T> getTranspose()
	{
		return mat4<T>(M[0], M[4], M[8], M[12],
			M[1], M[5], M[9], M[13],
			M[2], M[6], M[10], M[14],
			M[3], M[7], M[11], M[15]);
	}
	T getElement(int Column, int Row)
	{
		return M[Row * 4 + Column];
	}
	void SetElement(T element, int Column, int Row)
	{
		M[Row * 4 + Column] = element;
	}
	T *getArray()
	{
		return M;
	}
	template<typename T>
	friend std::ostream& operator<< (std::ostream &out, mat4<T> &Vector);

private:
	T M[16];
};
template<typename T>
std::ostream& operator<< (std::ostream &out, mat4<T> &Vector)
{
	out << "Matrix 4x4" << endl <<
		Vector.M[0] << ", " << Vector.M[1] << ", " << Vector.M[2] << ", " << Vector.M[3] << endl <<
		Vector.M[4] << ", " << Vector.M[5] << ", " << Vector.M[6] << ", " << Vector.M[7] << endl <<
		Vector.M[8] << ", " << Vector.M[9] << ", " << Vector.M[10] << ", " << Vector.M[11] << endl <<
		Vector.M[12] << ", " << Vector.M[13] << ", " << Vector.M[14] << ", " << Vector.M[15];
	return out;
};