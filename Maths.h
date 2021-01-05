#pragma once
#include <algorithm>
#include <iostream>

# define PI 3.14159265358979323846

//My custom maths library
class Maths
{
public:
	struct vec3
	{
		float values[3] = { 0.0f, 0.0f, 0.0f };
		vec3(){}
		vec3(float a, float b, float c)
		{
			values[0] = a;
			values[1] = b;
			values[2] = c;
		}
		vec3(float a)
		{
			values[0] = a;
			values[1] = a;
			values[2] = a;
		}
		vec3 operator+(const vec3& other) const
		{
			return vec3(values[0] + other.values[0], values[1] + other.values[1], values[2] + other.values[2]);
		}
		void operator+=(const vec3& other)
		{
			values[0] += other.values[0];
			values[1] += other.values[1];
			values[2] += other.values[2];
		}
		vec3 operator*(const vec3& other) const
		{
			return vec3(values[0] * other.values[0], values[1] * other.values[1], values[2] * other.values[2]);
		}
		vec3 operator*(const float& other) const
		{
			return vec3(values[0] * other, values[1] * other, values[2] * other);
		}
		void operator*=(const vec3& other)
		{
			values[0] *= other.values[0];
			values[1] *= other.values[1];
			values[2] *= other.values[2];
		}
		vec3 operator-(const vec3& other) const
		{
			return vec3(values[0] - other.values[0], values[1] - other.values[1], values[2] - other.values[2]);
		}
		void operator-=(const vec3& other)
		{
			values[0] -= other.values[0];
			values[1] -= other.values[1];
			values[2] -= other.values[2];
		}
		vec3 operator/(const vec3& other) const
		{
			return vec3(values[0] / other.values[0], values[1] / other.values[1], values[2] / other.values[2]);
		}
		void operator/=(const vec3& other)
		{
			values[0] /= other.values[0];
			values[1] /= other.values[1];
			values[2] /= other.values[2];
		}
		float dot(const vec3& other) const
		{
			return values[0] * other.values[0] + values[1] * other.values[1] + values[2] * other.values[2];
		}
		vec3 cross(const vec3& other) const
		{
			return vec3(
				values[1] * other.values[2] - values[2] * other.values[1],
				values[2] * other.values[0] - values[0] * other.values[2],
				values[0] * other.values[1] - values[1] * other.values[0]
			);
		}
		vec3 normalize() const
		{
			float factor = (float)sqrt(((double)values[0] * (double)values[0]) + ((double)values[1] * (double)values[1]) + ((double)values[2] * (double)values[2]));
			return vec3(values[0] / factor, values[1] / factor, values[2] / factor);
		}
		void print() const
		{
			std::cout << values[0] << ", " << values[0] << ", " << values[0] << std::endl;
		}
	};

	struct mat3
	{
		float values[9] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};
	};


	struct vec4
	{
		float values[4] = { 0.0f,0.0f,0.0f,0.0f };
		vec4() {}
		vec4(float a, float b, float c, float d)
		{
			values[0] = a;
			values[1] = b;
			values[2] = c;
			values[3] = d;
		}
		vec4(vec3 v, float a)
		{
			values[0] = v.values[0];
			values[1] = v.values[1];
			values[2] = v.values[2];
			values[3] = a;
		}
	};
	/*
	OPENGL VALUES ORDER:
		0 4 8  12
		1 5 9  13
		2 6 10 14
		3 7 11 15
	*/
	struct mat4
	{
		float values[16] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		mat4(){}
		mat4(float a1, float b1, float c1, float d1,
			float a2, float b2, float c2, float d2,
			float a3, float b3, float c3, float d3,
			float a4, float b4, float c4, float d4)
		{
			values[0] = a1; values[4] = b1; values[8] = c1; values[12] = d1;
			values[1] = a2; values[5] = b2; values[9] = c2; values[13] = d2;
			values[2] = a3; values[6] = b3; values[10] = c3; values[14] = d3;
			values[3] = a4; values[7] = b4; values[11] = c4; values[15] = d4;
		}
		mat4(float a)
		{
			values[0] = a; values[4] = 0; values[8] = 0; values[12] = 0;
			values[1] = 0; values[5] = a; values[9] = 0; values[13] = 0;
			values[2] = 0; values[6] = 0; values[10] = a; values[11] = 0;
			values[3] = 0; values[7] = 0; values[11] = 0; values[15] = a;
		}
		mat4 copy() const
		{
			return mat4(
				values[0], values[1], values[2], values[3],
				values[4], values[5], values[6], values[7],
				values[8], values[9], values[10], values[11],
				values[12], values[13], values[14], values[15]
			);
		}
		mat4 operator*(const mat4& other) const
		{
			return mat4(
				values[0] * other.values[0] + values[4] * other.values[1] + values[8] * other.values[2] + values[12] * other.values[3],
				values[0] * other.values[4] + values[4] * other.values[5] + values[8] * other.values[6] + values[12] * other.values[7],
				values[0] * other.values[8] + values[4] * other.values[9] + values[8] * other.values[10] + values[12] * other.values[11],
				values[0] * other.values[12] + values[4] * other.values[13] + values[8] * other.values[14] + values[12] * other.values[15],

				values[1] * other.values[0] + values[5] * other.values[1] + values[9] * other.values[2] + values[13] * other.values[3],
				values[1] * other.values[4] + values[5] * other.values[5] + values[9] * other.values[6] + values[13] * other.values[7],
				values[1] * other.values[8] + values[5] * other.values[9] + values[9] * other.values[10] + values[13] * other.values[11],
				values[1] * other.values[12] + values[5] * other.values[13] + values[9] * other.values[14] + values[13] * other.values[15],

				values[2] * other.values[0] + values[6] * other.values[1] + values[10] * other.values[2] + values[14] * other.values[3],
				values[2] * other.values[4] + values[6] * other.values[5] + values[10] * other.values[6] + values[14] * other.values[7],
				values[2] * other.values[8] + values[6] * other.values[9] + values[10] * other.values[10] + values[14] * other.values[11],
				values[2] * other.values[12] + values[6] * other.values[13] + values[10] * other.values[14] + values[14] * other.values[15],

				values[3] * other.values[0] + values[7] * other.values[1] + values[11] * other.values[2] + values[15] * other.values[3],
				values[3] * other.values[4] + values[7] * other.values[5] + values[11] * other.values[6] + values[15] * other.values[7],
				values[3] * other.values[8] + values[7] * other.values[9] + values[11] * other.values[10] + values[15] * other.values[11],
				values[3] * other.values[12] + values[7] * other.values[13] + values[11] * other.values[14] + values[15] * other.values[15]
			);	 
		}
		void operator*=(const mat4& other)
		{
			mat4 copy;
			copy.values[0] = values[0] * other.values[0] + values[4] * other.values[1] + values[8] * other.values[2] + values[12] * other.values[3];
			copy.values[1] = values[1] * other.values[0] + values[5] * other.values[1] + values[9] * other.values[2] + values[13] * other.values[3];
			copy.values[2] = values[2] * other.values[0] + values[6] * other.values[1] + values[10] * other.values[2] + values[14] * other.values[3];
			copy.values[3] = values[3] * other.values[0] + values[7] * other.values[1] + values[11] * other.values[2] + values[15] * other.values[3];

			copy.values[4] = values[0] * other.values[4] + values[4] * other.values[5] + values[8] * other.values[6] + values[12] * other.values[7];
			copy.values[5] = values[1] * other.values[4] + values[5] * other.values[5] + values[9] * other.values[6] + values[13] * other.values[7];
			copy.values[6] = values[2] * other.values[4] + values[6] * other.values[5] + values[10] * other.values[6] + values[14] * other.values[7];
			copy.values[7] = values[3] * other.values[4] + values[7] * other.values[5] + values[11] * other.values[6] + values[15] * other.values[7];

			copy.values[8] = values[0] * other.values[8] + values[4] * other.values[9] + values[8] * other.values[10] + values[12] * other.values[11];
			copy.values[9] = values[1] * other.values[8] + values[5] * other.values[9] + values[9] * other.values[10] + values[13] * other.values[11];
			copy.values[10] = values[2] * other.values[8] + values[6] * other.values[9] + values[10] * other.values[10] + values[14] * other.values[11];
			copy.values[11] = values[3] * other.values[8] + values[7] * other.values[9] + values[11] * other.values[10] + values[15] * other.values[11];

			copy.values[12] = values[0] * other.values[12] + values[4] * other.values[13] + values[8] * other.values[14] + values[12] * other.values[15];
			copy.values[13] = values[1] * other.values[12] + values[5] * other.values[13] + values[9] * other.values[14] + values[13] * other.values[15];
			copy.values[14] = values[2] * other.values[12] + values[6] * other.values[13] + values[10] * other.values[14] + values[14] * other.values[15];
			copy.values[15] = values[3] * other.values[12] + values[7] * other.values[13] + values[11] * other.values[14] + values[15] * other.values[15];

			*this = copy;
		}
		vec4 operator*(const vec4& vec) const
		{
			return vec4(
				values[0] * vec.values[0] + values[4] * vec.values[1] + values[8] * vec.values[2] + values[12] * vec.values[3],
				values[1] * vec.values[0] + values[5] * vec.values[1] + values[9] * vec.values[2] + values[13] * vec.values[3],
				values[2] * vec.values[0] + values[6] * vec.values[1] + values[10] * vec.values[2] + values[14] * vec.values[3],
				values[3] * vec.values[0] + values[7] * vec.values[1] + values[11] * vec.values[2] + values[15] * vec.values[3]
			);
		}
		//creates translation matrix
		static mat4 translation(const vec3 trans)
		{
			return mat4(
				1.0f, 0.0f, 0.0f, trans.values[0],
				0.0f, 1.0f, 0.0f, trans.values[1],
				0.0f, 0.0f, 1.0f, trans.values[2],
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
		//creates scale matrix
		static mat4 scale(const vec3 scale)
		{
			return mat4(
				scale.values[0], 0.0f, 0.0f, 0.0f,
				0.0f, scale.values[1], 0.0f, 0.0f,
				0.0f, 0.0f, scale.values[2], 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
		static mat4 rotation(const float angleRads, vec3 rotationAxis)
		{
			rotationAxis = rotationAxis.normalize();
			float c = cos(angleRads);
			float s = sin(angleRads);
			vec3 temp = rotationAxis * (1.0f - c);
			return mat4(
				c + rotationAxis.values[0] * temp.values[0],
				rotationAxis.values[0] * temp.values[1] - rotationAxis.values[2] * s,
				rotationAxis.values[0] * temp.values[2] + rotationAxis.values[1] * s,
				0.0f,

				rotationAxis.values[1] * temp.values[0] + rotationAxis.values[2] * s,
				c + rotationAxis.values[1] * temp.values[1],
				rotationAxis.values[1] * temp.values[2] - rotationAxis.values[0] * s,
				0.0f,

				rotationAxis.values[2] * temp.values[0] - rotationAxis.values[1] * s,
				rotationAxis.values[2] * temp.values[1] + rotationAxis.values[0] * s,
				c + rotationAxis.values[2] * temp.values[2],
				0.0f,

				0.0f,
				0.0f,
				0.0f,
				1.0f
			);
		}
		static mat4 lookat(const vec3 position, vec3 front, vec3 up)
		{
			const vec3 right = (front.cross(up)).normalize();
			front = front.normalize();
			up = up.normalize();
			return mat4(
				right.values[0],
				right.values[1],
				right.values[2],
				right.values[0] * (-(position.values[0])) + right.values[1] * (-(position.values[1])) + right.values[2] * (-(position.values[2])),

				up.values[0],
				up.values[1],
				up.values[2],
				up.values[0] * (-(position.values[0])) + up.values[1] * (-(position.values[1])) + up.values[2] * (-(position.values[2])),


				front.values[0],
				front.values[1],
				front.values[2],
				front.values[0] * (-(position.values[0])) + front.values[1] * (-(position.values[1])) + front.values[2] * (-(position.values[2])),

				0.0f,
				0.0f,
				0.0f,
				1.0f
			);
		}
		static mat4 perspective(float fovRads, float aspect, float near, float far)
		{
			float halfTan = tan(fovRads / 2);
			return mat4(
				1 / (aspect*halfTan), 0.0f, 0.0f, 0.0f,
				0.0f, 1/halfTan, 0.0f, 0.0f,
				0.0f, 0.0f, -(far+near)/(far-near), -(2*far*near)/(far-near),
				0.0f, 0.0f, -1.0f, 0.0f
			);
		}
		void print() const
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					std::cout << values[j * 4 + i] << ", ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	};

};

