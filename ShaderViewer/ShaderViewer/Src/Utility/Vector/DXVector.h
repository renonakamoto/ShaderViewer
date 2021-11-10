#ifndef DXVECTOR_H_
#define DXVECTOR_H_

#include <D3DX11.h>
#include <DirectXMath.h>

/**
* @brief Vector3クラス
*/
struct DXVector3 : public DirectX::XMFLOAT3
{
	/**
	* @brief コンストラクタ
	*/
	DXVector3() :DXVector3(0.0f, 0.0f, 0.f) {}

	/**
	* @brief 引数付きコンストラクタ
	*/
	DXVector3(float x_, float y_, float z_) :XMFLOAT3(x_, y_, z_) {}

	/**
	* @brief デストラクタ
	*/
	~DXVector3(){}
	
	/**
	* @fn operator +
	* @brief DXVector3との+演算operator
	*/
	DXVector3 operator + (DXVector3 value) const
	{
		return DXVector3(this->x + value.x, this->y + value.y, this->z + value.z);
	}

	/**
	* @fn operator +
	* @brief floatとの+演算operator
	*/
	DXVector3 operator + (float value) const
	{
		return DXVector3(this->x + value, this->y + value, this->z + value);
	}

	/**
	* @fn operator -
	* @brief DXVector3との-演算operator
	*/
	DXVector3 operator - (DXVector3 value) const
	{
		return DXVector3(this->x - value.x, this->y - value.y, this->z - value.z);
	}

	/**
	* @fn operator -
	* @brief floatとの-演算operator
	*/
	DXVector3 operator - (float value) const
	{
		return DXVector3(this->x - value, this->y - value, this->z - value);
	}

	/**
	* @fn operator *
	* @brief DXVector3との*演算operator
	*/
	DXVector3 operator * (DXVector3 value) const
	{
		return DXVector3(this->x * value.x, this->y * value.y, this->z * value.z);
	}

	/**
	* @fn operator *
	* @brief floatとの*演算operator
	*/
	DXVector3 operator * (float value) const
	{
		return DXVector3(this->x * value, this->y * value, this->z * value);
	}

	/**
	* @fn operator /
	* @brief DXVector3との/演算operator
	*/
	DXVector3 operator / (DXVector3 value) const
	{
		return DXVector3(this->x / value.x, this->y / value.y, this->z / value.z);
	}

	/**
	* @fn operator /
	* @brief floatとの/演算operator
	*/
	DXVector3 operator / (float value) const
	{
		return DXVector3(this->x / value, this->y / value, this->z / value);
	}

};

#endif