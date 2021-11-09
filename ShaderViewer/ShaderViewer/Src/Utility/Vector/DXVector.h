#ifndef DXVECTOR_H_
#define DXVECTOR_H_

#include <D3DX11.h>
#include <DirectXMath.h>

struct DXVector3 : public DirectX::XMFLOAT3
{
	DXVector3() :DXVector3(0.0f, 0.0f, 0.f) {}
	DXVector3(float x_, float y_, float z_) :XMFLOAT3(x_, y_, z_) {}
	~DXVector3(){}

	float* GetData() { return &x; }
	
	DXVector3 operator + (DXVector3 value) const
	{
		return DXVector3(this->x + value.x, this->y + value.y, this->z + value.z);
	}
	DXVector3 operator + (float value) const
	{
		return DXVector3(this->x + value, this->y + value, this->z + value);
	}
	DXVector3 operator - (DXVector3 value) const
	{
		return DXVector3(this->x - value.x, this->y - value.y, this->z - value.z);
	}
	DXVector3 operator - (float value) const
	{
		return DXVector3(this->x - value, this->y - value, this->z - value);
	}
	DXVector3 operator * (DXVector3 value) const
	{
		return DXVector3(this->x * value.x, this->y * value.y, this->z * value.z);
	}
	DXVector3 operator * (float value) const
	{
		return DXVector3(this->x * value, this->y * value, this->z * value);
	}
	DXVector3 operator / (DXVector3 value) const
	{
		return DXVector3(this->x / value.x, this->y / value.y, this->z / value.z);
	}
	DXVector3 operator / (float value) const
	{
		return DXVector3(this->x / value, this->y / value, this->z / value);
	}

};

#endif