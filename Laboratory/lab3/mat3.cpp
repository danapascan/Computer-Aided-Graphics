#include "mat3.h"

namespace egc {
	
	float& mat3::at(int i, int j)
	{
		return matrixData[i + j * 3];
	}

	const float& mat3::at(int i, int j) const
	{
		return matrixData[i + j * 3];
	}
	mat3& mat3::operator =(const mat3& srcMatrix)
	{
		for (int i = 0; i < 9; i++)
		{
			this->matrixData[i] = srcMatrix.matrixData[i];
		}
		return *this;
	}

	mat3 mat3::operator +(const mat3& srcMatrix) const
	{
		mat3 result;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				result.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
			}
		}

		return result;
	}

	mat3 mat3::operator *(float scalarValue) const
	{
		mat3 result;
		for (int i = 0; i < 9; i++)
		{
			result.matrixData[i] = this->matrixData[i] * scalarValue;
		}
		return result;
	}

	mat3 mat3::operator *(const mat3& srcMatrix) const
	{
		mat3 result;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				result.at(i, j) = 0;
				for (int k = 0; k < 3; k++)
				{
					result.at(i, j) = result.at(i, j) + this->at(i, k) * srcMatrix.at(k, j);
				}
			}
		}
		return result;
	}
	
	vec3 mat3::operator *(const vec3& srcVector) const
	{
		vec3 result;
		
					result.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z;
					result.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z;
					result.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z;
				
		return result;
	}
	float mat3::determinant() const
	{
		float result;
		result = this->at(0, 0) * this->at(1, 1) * this->at(2, 2) + this->at(0, 1) * this->at(1, 2) * this->at(2, 0) + this->at(1, 0) * this->at(2, 1) * this->at(0, 2) - this->at(0, 2) * this->at(1, 1) * this->at(2, 0) - this->at(0, 0) * this->at(2, 1) * this->at(1, 2) - this->at(2, 2) * this->at(1, 0) * this->at(0, 1);
		return result;
	}

	mat3 mat3::transpose() const
	{
		mat3 result;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				result.at(j, i) = this->at(i, j);
			}
		}
		return result;
	}

	mat3 mat3::inverse() const
	{
		mat3 result;
		float determinant;
		determinant=this->determinant();
		if (determinant != 0)
		{
			mat3 transpusa;
			transpusa = this->transpose();
			result.at(0, 0) = 1 / determinant * (transpusa.at(1, 1) * transpusa.at(2, 2) - transpusa.at(1, 2) * transpusa.at(2, 1));
			result.at(0, 1) = ( - 1) / determinant * (transpusa.at(1, 0) * transpusa.at(2, 2) - transpusa.at(1, 2) * transpusa.at(2, 0));
			result.at(0, 2) = 1 / determinant * (transpusa.at(1, 0) * transpusa.at(2, 1) - transpusa.at(1, 1) * transpusa.at(2, 0));
			result.at(1, 0) = ( - 1) / determinant * (transpusa.at(0, 1) * transpusa.at(2, 2) - transpusa.at(0, 2) * transpusa.at(2, 1));
			result.at(1, 1) = 1 / determinant * (transpusa.at(0,0)* transpusa.at(2,2)- transpusa.at(0,2)* transpusa.at(2,0));
			result.at(1, 2) = ( - 1) / determinant * (transpusa.at(0, 0) * transpusa.at(2, 1) - transpusa.at(0, 1) * transpusa.at(2, 0));
			result.at(2, 0) = 1 / determinant * (transpusa.at(0,1)* transpusa.at(1,2)- transpusa.at(0,2)* transpusa.at(1,1));
			result.at(2, 1) = (-1) / determinant *(transpusa.at(0,0)* transpusa.at(1,2)- transpusa.at(0,2)* transpusa.at(1,0));
			result.at(2,2) = 1 / determinant * (transpusa.at(0,0)* transpusa.at(1,1)- transpusa.at(0,1)* transpusa.at(1,0));
		}
		return result;
		
	}
}
