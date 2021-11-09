#ifndef SPRITE_H_
#define SPRITE_H_

#include "../../../Engine/Graphics/GraphicsUtility.h"
#include "../../../Engine/Shader/VertexShader.h"
#include "../../../Engine/Shader/PixelShader.h"
#include "../../../Utility/Vector/DXVector.h"

class Sprite
{
public:
	Sprite():
		m_VertexShader(nullptr),
		m_PixelShader(nullptr)
	{}

	~Sprite()
	{}

	bool Init(ID3D11ShaderResourceView* tex_, UINT width_, UINT height_, VertexShader* vs_, PixelShader* ps_);
	
	void Draw(DXVector3 pos_);

private:
	bool CreateVertexBuffer();
	bool CreateIndexBuffer();

	bool CreateInoutLayout();
private:
	TextureData   m_TextureData;
	VertexShader* m_VertexShader;
	PixelShader*  m_PixelShader;
	ComPtr<ID3D11InputLayout> m_InputLayout;
};

#endif