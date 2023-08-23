#include "mat4.h"

namespace egc {

	float& mat4::at(int i, int j)
	{
		return matrixData[i + j * 4];
	}
	const float& mat4::at(int i, int j) const
	{
		return matrixData[i + j * 4];
	}

	
	mat4& mat4::operator =(const mat4& srcMatrix)
	{
		for (int i = 0; i < 16; i++)
		{
			this->matrixData[i] = srcMatrix.matrixData[i];
		}
		return *this;
	}
	
	mat4 mat4::operator *(float scalarValue) const
	{
		mat4 result;
		for (int i = 0; i < 16; i++)
		{
			result.matrixData[i] = this->matrixData[i] * scalarValue;
		}
		return result;
	}

	mat4 mat4::operator *(const mat4& srcMatrix) const
	{
		mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.at(i, j) = 0;
				for (int k = 0; k < 4; k++)
				{
					result.at(i, j) = result.at(i, j) + this->at(i, k) * srcMatrix.at(k, j);
				}
			}
		}
		return result;
	}

	vec4 mat4::operator *(const vec4& srcVector) const
	{
		vec4 result;

		result.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z+ this->at(0,3)* srcVector.w;
		result.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z+ this->at(1, 3) * srcVector.w;
		result.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z+ this->at(2, 3) * srcVector.w;
		result.w = this->at(3, 0) * srcVector.x + this->at(3, 1) * srcVector.y + this->at(3, 2) * srcVector.z + this->at(3, 3) * srcVector.w;

		return result;
	}
	
	mat4 mat4::operator +(const mat4& srcMatrix) const
	{
		mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
			}
		}

		return result;
	}

	float mat4::determinant() const
	{
		float result;
		float det1, det2, det3, det4;
		det1= this->at(0,0)*(this->at(1,1) * this->at(2, 2) * this->at(3, 3) + this->at(1, 2) * this->at(2, 3) * this->at(3, 1) + this->at(2, 1) * this->at(3, 2) * this->at(1, 3) - this->at(1, 3) * this->at(2, 2) * this->at(3, 1) - this->at(3, 2) * this->at(2, 3) * this->at(1, 1) - this->at(2, 1) * this->at(1, 2) * this->at(3, 3));
		det2 =(-1)* this->at(0, 1) * (this->at(1, 0) * this->at(2, 2) * this->at(3, 3) + this->at(1, 2) * this->at(2, 3) * this->at(3, 0) + this->at(2, 0) * this->at(3, 2) * this->at(1, 3) - this->at(1, 3) * this->at(2, 2) * this->at(3, 0) - this->at(3, 2) * this->at(2, 3) * this->at(1, 0) - this->at(2, 0) * this->at(1, 2) * this->at(3, 3));
		det3 = this->at(0, 2) * (this->at(1, 0) * this->at(2, 1) * this->at(3, 3) + this->at(1, 1) * this->at(2, 3) * this->at(3, 0) + this->at(2, 0) * this->at(3, 1) * this->at(1, 3) - this->at(1, 3) * this->at(2, 1) * this->at(3, 0) - this->at(3, 1) * this->at(2, 3) * this->at(1, 0) - this->at(2, 0) * this->at(1, 1) * this->at(3, 3));
		det4 = (-1)*this->at(0, 3) * (this->at(1, 0) * this->at(2, 1) * this->at(3, 2) + this->at(1, 1) * this->at(2, 2) * this->at(3, 0) + this->at(2, 0) * this->at(3, 1) * this->at(1, 2) - this->at(1, 2) * this->at(2, 1) * this->at(3, 0) - this->at(3, 1) * this->at(2, 2) * this->at(1, 0) - this->at(2, 0) * this->at(1, 1) * this->at(3, 2));
		result = det1 + det2 + det3 + det4;
		return result;
	}
	
	mat4 mat4::transpose() const
	{
		mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.at(j, i) = this->at(i, j);
			}
		}
		return result;

	}

	mat4 mat4::inverse() const
	{
		mat4 result;
		float determinant;
		determinant = this->determinant();
		if (determinant != 0)
		{
			mat4 transpusa;
			transpusa = this->transpose();
			result.at(0, 0) = 1 / determinant * (transpusa.at(1, 1) * transpusa.at(2, 2) * transpusa.at(3, 3) + transpusa.at(1, 2) * transpusa.at(2, 3) * transpusa.at(3, 1) + transpusa.at(2, 1) * transpusa.at(3, 2) * transpusa.at(1, 3) - transpusa.at(1, 3) * transpusa.at(2, 2) * transpusa.at(3, 1) - transpusa.at(3, 2) * transpusa.at(2, 3) * transpusa.at(1, 1) - transpusa.at(2, 1) * transpusa.at(1, 2) * transpusa.at(3, 3));
			result.at(0, 1) = (-1) / determinant * (transpusa.at(1, 0) * transpusa.at(2, 2) * transpusa.at(3, 3) + transpusa.at(1, 2) * transpusa.at(2, 3) * transpusa.at(3, 0) + transpusa.at(2, 0) * transpusa.at(3, 2) * transpusa.at(1, 3) - transpusa.at(1, 3) * transpusa.at(2, 2) * transpusa.at(3, 0) - transpusa.at(3, 2) * transpusa.at(2, 3) * transpusa.at(1, 0) - transpusa.at(2, 0) * transpusa.at(1, 2) * transpusa.at(3, 3));
			result.at(0, 2) = 1 / determinant * (transpusa.at(1, 0) * transpusa.at(2, 1) * transpusa.at(3, 3) + transpusa.at(1, 1) * transpusa.at(2, 3) * transpusa.at(3, 0) + transpusa.at(2, 0) * transpusa.at(3, 1) * transpusa.at(1, 3) - transpusa.at(1, 3) * transpusa.at(2, 1) * transpusa.at(3, 0) - transpusa.at(3, 1) * transpusa.at(2, 3) * transpusa.at(1, 0) - transpusa.at(2, 0) * transpusa.at(1, 1) * transpusa.at(3, 3));
			result.at(0, 3) = (-1) / determinant * (transpusa.at(1, 0) * transpusa.at(2, 1) * transpusa.at(3, 2) + transpusa.at(1, 1) * transpusa.at(2, 2) * transpusa.at(3, 0) + transpusa.at(2, 0) * transpusa.at(3, 1) * transpusa.at(1, 2) - transpusa.at(1, 2) * transpusa.at(2, 1) * transpusa.at(3, 0) - transpusa.at(3, 1) * transpusa.at(2, 2) * transpusa.at(1, 0) - transpusa.at(2, 0) * transpusa.at(1, 1) * transpusa.at(3, 2));
			result.at(1, 0) = (-1) / determinant * (transpusa.at(0, 1) * transpusa.at(2, 2) * transpusa.at(3, 3) + transpusa.at(0, 2) * transpusa.at(2, 3) * transpusa.at(3, 1) + transpusa.at(2, 1) * transpusa.at(3, 2) * transpusa.at(0, 3) - transpusa.at(0, 3) * transpusa.at(2, 2) * transpusa.at(3, 1) - transpusa.at(3, 2) * transpusa.at(2, 3) * transpusa.at(0, 1) - transpusa.at(2, 1) * transpusa.at(0, 2) * transpusa.at(3, 3));
			result.at(1, 1) = 1 / determinant * (transpusa.at(0, 0) * transpusa.at(2, 2) * transpusa.at(3, 3) + transpusa.at(0, 2) * transpusa.at(2, 3) * transpusa.at(3, 0) + transpusa.at(2, 0) * transpusa.at(3, 2) * transpusa.at(0, 3) - transpusa.at(0, 3) * transpusa.at(2, 2) * transpusa.at(3, 0) - transpusa.at(3, 2) * transpusa.at(2, 3) * transpusa.at(0, 0) - transpusa.at(2, 0) * transpusa.at(0, 2) * transpusa.at(3, 3));
			result.at(1, 2) = (-1) / determinant * (transpusa.at(0, 0) * transpusa.at(2, 1) * transpusa.at(3, 3) + transpusa.at(2, 0) * transpusa.at(3, 1) * transpusa.at(0, 3) + transpusa.at(0, 1) * transpusa.at(2, 3) * transpusa.at(3, 0) - transpusa.at(0, 3) * transpusa.at(2, 1) * transpusa.at(3, 0) - transpusa.at(3, 1) * transpusa.at(2, 3) * transpusa.at(0, 0) - transpusa.at(2, 0) * transpusa.at(0, 1) * transpusa.at(3, 3));
			result.at(1, 3) = 1 / determinant * (transpusa.at(0, 0) * transpusa.at(2, 1) * transpusa.at(3, 2) + transpusa.at(0, 1) * transpusa.at(2, 2) * transpusa.at(3, 0) + transpusa.at(2, 0) * transpusa.at(3, 1) * transpusa.at(0, 2) - transpusa.at(0, 2) * transpusa.at(2, 1) * transpusa.at(3, 0) - transpusa.at(3, 1) * transpusa.at(2, 2) * transpusa.at(0, 0) - transpusa.at(2, 0) * transpusa.at(0, 1) * transpusa.at(3, 2));
			result.at(2, 0) = 1 / determinant * (transpusa.at(0, 1) * transpusa.at(1, 2) * transpusa.at(3, 3) + transpusa.at(0, 2) * transpusa.at(1, 3) * transpusa.at(3, 1) + transpusa.at(1, 1) * transpusa.at(3, 2) * transpusa.at(0, 3) - transpusa.at(0, 3) * transpusa.at(1, 2) * transpusa.at(3, 1) - transpusa.at(3, 2) * transpusa.at(1, 3) * transpusa.at(0, 1) - transpusa.at(1, 1) * transpusa.at(0, 2) * transpusa.at(3, 3));
			result.at(2, 1) = (-1) / determinant * (transpusa.at(0, 0) * transpusa.at(1, 2) * transpusa.at(3, 3) + transpusa.at(0, 2) * transpusa.at(1, 3) * transpusa.at(3, 0) + transpusa.at(1, 0) * transpusa.at(3, 2) * transpusa.at(0, 3) - transpusa.at(0, 3) * transpusa.at(1, 2) * transpusa.at(3, 0) - transpusa.at(3, 2) * transpusa.at(1, 3) * transpusa.at(0, 0) - transpusa.at(1, 0) * transpusa.at(0, 2) * transpusa.at(3, 3));
			result.at(2, 2) = 1 / determinant * (transpusa.at(0, 0) * transpusa.at(1, 1) * transpusa.at(3, 3) + transpusa.at(1, 0) * transpusa.at(3, 1) * transpusa.at(0, 3) + transpusa.at(0, 1) * transpusa.at(1, 3) * transpusa.at(3, 0) - transpusa.at(0, 3) * transpusa.at(1, 1) * transpusa.at(3, 0) - transpusa.at(3, 1) * transpusa.at(1, 3) * transpusa.at(0, 0) - transpusa.at(1, 0) * transpusa.at(0, 1) * transpusa.at(3, 3));
			result.at(2, 3) = (-1)/ determinant * (transpusa.at(0, 0) * transpusa.at(1, 1) * transpusa.at(3, 2) + transpusa.at(0, 1) * transpusa.at(1, 2) * transpusa.at(3, 0) + transpusa.at(1, 0) * transpusa.at(3, 1) * transpusa.at(0, 2) - transpusa.at(0, 2) * transpusa.at(1, 1) * transpusa.at(3, 0) - transpusa.at(3, 1) * transpusa.at(1, 2) * transpusa.at(0, 0) - transpusa.at(1, 0) * transpusa.at(0, 1) * transpusa.at(3, 2));
			result.at(3, 0) = (-1) / determinant * (transpusa.at(0, 1) * transpusa.at(1, 2) * transpusa.at(2, 3) + transpusa.at(0, 2) * transpusa.at(1, 3) * transpusa.at(2, 1) + transpusa.at(1, 1) * transpusa.at(2, 2) * transpusa.at(0, 3) - transpusa.at(0, 3) * transpusa.at(1, 2) * transpusa.at(2, 1) - transpusa.at(2, 2) * transpusa.at(1, 3) * transpusa.at(0, 1) - transpusa.at(1, 1) * transpusa.at(0, 2) * transpusa.at(2, 3));
			result.at(3, 1) = 1 / determinant * (transpusa.at(0, 0) * transpusa.at(1, 2) * transpusa.at(2, 3) + transpusa.at(0, 2) * transpusa.at(1, 3) * transpusa.at(2, 0) + transpusa.at(1, 0) * transpusa.at(2, 2) * transpusa.at(0, 3) - transpusa.at(0, 3) * transpusa.at(1, 2) * transpusa.at(2, 0) - transpusa.at(2, 2) * transpusa.at(1, 3) * transpusa.at(0, 0) - transpusa.at(1, 0) * transpusa.at(0, 2) * transpusa.at(2, 3));
			result.at(3, 2) = (-1) / determinant * (transpusa.at(0, 0) * transpusa.at(1, 1) * transpusa.at(2, 3) + transpusa.at(0, 1) * transpusa.at(1, 3) * transpusa.at(2, 0) + transpusa.at(1, 0) * transpusa.at(2, 1) * transpusa.at(0, 3) - transpusa.at(0, 3) * transpusa.at(1, 1) * transpusa.at(2, 0) - transpusa.at(2, 1) * transpusa.at(1, 3) * transpusa.at(0, 0) - transpusa.at(1, 0) * transpusa.at(0, 1) * transpusa.at(2, 3));
			result.at(3, 3) = 1 / determinant * (transpusa.at(0, 0) * transpusa.at(1, 1) * transpusa.at(2, 2) + transpusa.at(0, 1) * transpusa.at(1, 2) * transpusa.at(2, 0) + transpusa.at(1, 0) * transpusa.at(2, 1) * transpusa.at(0, 2) - transpusa.at(0, 2) * transpusa.at(1, 1) * transpusa.at(2, 0) - transpusa.at(2, 1) * transpusa.at(1, 2) * transpusa.at(0, 0) - transpusa.at(1, 0) * transpusa.at(0, 1) * transpusa.at(2, 2));

		}
		return result;
	}
	
	
}