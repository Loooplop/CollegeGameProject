#pragma once
#include <iostream>







template<typename T>
class vec2
{
#define  vec2s vec2<short>
#define  vec2d vec2<double>
#define  vec2i vec2<int>
#define  vec2f vec2<float>
public:
	vec2(T X, T Y)
	{
		m_x = X;
		m_y = Y;
	};
	vec2()
	{
		m_x = m_y = 0;
	}
	~vec2()
	{

	};
	vec2<T> operator +( vec2<T> &other)
	{
		return vec2<T>(m_x+other.getX(),m_y + other.getY());
	}
	vec2<T> operator -(vec2<T> &other)
	{
		return vec2<T>(m_x - other.getX(), m_y - other.getY());
	}
	vec2<T> operator *(vec2<T> &other)
	{
		return vec2<T>(m_x * other.getX(), m_y * other.getY());
	}
	vec2<T> operator *(T &other)
	{
		return vec2<T>(m_x * other, m_y * other);
	}
	vec2<T> operator /(vec2<T> &other)
	{
		return vec2<T>(m_x / other.getX(), m_y / other.getY());
	}
	vec2<T> operator /(T &other)
	{
		return vec2<T>(m_x / other, m_y / other);
	}
	T DotProduct(vec2<T> &other)
	{
		return m_x*other.getX() + m_y*other.getY();
	}
	T getX()
	{
		return m_x;
	};
	T getY()
	{
		return m_y;
	}
	void SetX(T x)
	{
		m_x = x;
	}
	void SetY(T y)
	{
		m_y = y;
	}
	double getLength()
	{
		return sqrt((m_x*m_x) + (m_y*m_y));
	}
private:
	T m_x, m_y;
};

template<typename T>
std::ostream& operator<< (std::ostream &out, vec2<T> &Vector)
{
	out << Vector.getX() << ", " << Vector.getY();
	return out;
};
template<typename T>
class vec3
{
#define  vec3s vec3<short>
#define  vec3d vec3<double>
#define  vec3i vec3<int>
#define  vec3f vec3<float>
public:
	vec3(T X, T Y,T Z)
	{
		m_x = X;
		m_y = Y;
		m_z = Z;
	};
	vec3()
	{
		m_x = m_y = m_z = 0;
	}
	~vec3()
	{

	};
	vec3<T> operator +(vec3<T> other)
	{
		return vec3<T>(m_x + other.getX(), m_y + other.getY(), m_z + other.getZ());
	}
	void operator +=(vec3<T> other)
	{
		m_x += other.getX();
		m_y += other.getY();
		m_z += other.getZ();
	}
	vec3<T> operator -(vec3<T> other)
	{
		return vec3<T>(m_x - other.getX(), m_y - other.getY(), m_z - other.getZ());
	}
	void operator -=(vec3<T> other)
	{
		m_x -= other.getX();
		m_y -= other.getY();
		m_z -= other.getZ();
	}
	vec3<T> operator *(vec3<T> other)
	{
		return vec3<T>(m_x * other.getX(), m_y * other.getY(), m_z * other.getZ());
	}
	void operator *=(vec3<T> other)
	{
		m_x *= other.getX();
		m_y *= other.getY();
		m_z *= other.getZ();
	}
	vec3<T> operator *(T other)
	{
		return vec3<T>(m_x * other, m_y * other,m_z * other);
	}
	void operator *=(T other)
	{
		m_x *= other;
		m_y *= other;
		m_z *= other;
	}
	vec3<T> operator /(vec3<T> other)
	{
		return vec3<T>(m_x / other.getX(), m_y / other.getY(), m_z / other.getZ());
	}
	void operator /=(vec3<T> other)
	{
		m_x /= other.getX();
		m_y /= other.getY();
		m_z /= other.getZ();
	}
	vec3<T> operator /(T other)
	{
		return vec3<T>(m_x / other, m_y / other, m_z / other);
	}
	void operator /=(T other)
	{
		m_x /= other;
		m_y /= other;
		m_z /= other;
	}
	T DotProduct(vec3<T> other)
	{
		return m_x*other.getX() + m_y*other.getY() + m_z*other.getZ();
	}
	vec3<T> CrossProduct(vec3<T> other)
	{
		return vec3<T>(m_y*other.getZ() - m_z*other.getY()
			          , m_z*other.getX() - m_x*other.getZ()
			          , m_x*other.getY() - m_y*other.getX()
			);
	}
	vec3<T> getNormal()
	{
		return (*this) / sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
	}
	T getX()
	{
		return m_x;
	};
	T getY()
	{
		return m_y;
	}
	T getZ()
	{
		return m_z;
	}
	void SetX(T x)
	{
		m_x = x;
	}
	void SetY(T y)
	{
		m_y = y;
	}
	void SetZ(T z)
	{
		m_z = z;
	}
	double getLength()
	{
		return sqrt((m_x*m_x) + (m_y*m_y) + (m_z*m_z));
	}
private:
	T m_x, m_y,m_z;
};

template<typename T>
std::ostream& operator<< (std::ostream &out, vec3<T> &Vector)
{
	out << Vector.getX() << ", " << Vector.getY() << ", " << Vector.getZ();
	return out;
};

template<typename T>
class vec4
{
#define  vec4s vec4<short>
#define  vec4d vec4<double>
#define  vec4i vec4<int>
#define  vec4f vec4<float>
public:
	vec4(T X, T Y, T Z,T W)
	{
		m_x = X;
		m_y = Y;
		m_z = Z;
		m_w = W;
	};
	vec4()
	{
		m_x = m_y = m_z = m_w = 0;
	}
	~vec4()
	{

	};
	vec4<T> operator +(vec4<T> other)
	{
		return vec4<T>(m_x + other.getX(), m_y + other.getY(), m_z + other.getZ(), m_w + other.getW());
	}
	vec4<T> operator -(vec4<T> other)
	{
		return vec4<T>(m_x - other.getX(), m_y - other.getY(), m_z - other.getZ(), m_w - other.getW());
	}
	vec4<T> operator *(vec4<T> other)
	{
		return vec4<T>(m_x * other.getX(), m_y * other.getY(), m_z * other.getZ(), m_w * other.getW());
	}
	vec4<T> operator *(T other)
	{
		return vec4<T>(m_x * other, m_y * other, m_z * other, m_w * other);
	}
	vec4<T> operator /(vec4<T> other)
	{
		return vec4<T>(m_x / other.getX(), m_y / other.getY(), m_z / other.getZ(), m_w / other.getW());
	}
	vec4<T> operator /(T other)
	{
		return vec4<T>(m_x / other, m_y / other, m_z / other, m_w / other);
	}
	T DotProduct(vec4<T> other)
	{
		return m_x*other.getX() + m_y*other.getY() + m_z*other.getZ() + m_w*other.getW();
	}
	T getX()
	{
		return m_x;
	};
	T getY()
	{
		return m_y;
	}
	T getZ()
	{
		return m_z;
	}
	T getW()
	{
		return m_w;
	}
	void SetX(T x)
	{
		m_x = x;
	}
	void SetY(T y)
	{
		m_y = y;
	}
	void SetZ(T z)
	{
		m_z = z;
	}
	void SetW(T w)
	{
		m_w = w;
	}
	double getLength()
	{
		return sqrt((m_x*m_x) + (m_y*m_y) + (m_z*m_z) + (m_w*m_w));
	}
private:
	T m_x, m_y, m_z,m_w;
};
template<typename T>
std::ostream& operator<< (std::ostream &out, vec4<T> &Vector)
{
	out << Vector.getX() << ", " << Vector.getY() << ", " << Vector.getZ() << ", " << Vector.getW();
	return out;
};