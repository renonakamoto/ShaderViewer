#include <vector>
#include <d3dcompiler.h>
#include "VertexShader.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")


bool VertexShader::Create(ID3D11Device* device_, const char* fileName_)
{
	if (ShaderBase::Create(device_, fileName_) == false)
	{
		return false;
	}

	
	if (FAILED(device_->CreateVertexShader(m_Data, m_Size, nullptr, m_Interface.GetAddressOf())))
	{
		return false;
	}

    if (CreateInputLayout(device_) == false) {
        return false;
    }

	return true;
}

bool VertexShader::CreateInputLayout(ID3D11Device* device_)
{
    if (!m_Interface) {
        return false;
    }

    // ShaderReflectionの作成
    ID3D11ShaderReflection* reflector;
    if (FAILED(D3DReflect(m_Data, m_Size, IID_ID3D11ShaderReflection, (void**)&reflector))) {
        return false;
    }

    D3D11_SHADER_DESC shader_desc;
    reflector->GetDesc(&shader_desc);

    // 
    std::vector<D3D11_INPUT_ELEMENT_DESC> elements;
    for (int i = 0; i < shader_desc.InputParameters; ++i)
    {
        D3D11_SIGNATURE_PARAMETER_DESC sig_desc;
        reflector->GetInputParameterDesc(i, &sig_desc);

        DXGI_FORMAT format = this->GetDxgiFormat(sig_desc.ComponentType, sig_desc.Mask);
        D3D11_INPUT_ELEMENT_DESC element = {
            sig_desc.SemanticName,          // セマンティック名
            sig_desc.SemanticIndex,         // セマンティック番号
            format,                         // フォーマット
            0,                              // スロット番号
            D3D11_APPEND_ALIGNED_ELEMENT,   // 先頭までのオフセット値
            D3D11_INPUT_PER_VERTEX_DATA,    // 入力データクラス
            0                               // インスタンスの数
        };

        elements.push_back(element);
    }

    if (elements.empty()) {
        return false;
    }

    ID3D11Device* device = device_;
    if (FAILED(device->CreateInputLayout(
        &elements[0],                    // 入力データ配列
        elements.size(),                 // 入力データ数
        m_Data,                          // 頂点シェーダー
        m_Size,                          // 頂点シェーダーのサイズ
        m_InputLayout.GetAddressOf()     // 作成された入力レイアウトへのポインタ
    )))
    {
        return false;
    }

    return true;
}

DXGI_FORMAT VertexShader::GetDxgiFormat(D3D10_REGISTER_COMPONENT_TYPE type_, BYTE mask_)
{
    /*
            各成分が使われているかをビットで判定し、
            フォーマットを返す
    */
    if (mask_ & 0x0f)
    {
        switch (type_)
        {
        case D3D10_REGISTER_COMPONENT_FLOAT32:
            return DXGI_FORMAT_R32G32B32_FLOAT;
            break;
        }
    }

    if (mask_ & 0x07)
    {
        switch (type_)
        {
        case D3D10_REGISTER_COMPONENT_FLOAT32:
            return DXGI_FORMAT_R32G32B32_FLOAT;
            break;
        }
    }

    if (mask_ & 0x03)
    {
        switch (type_)
        {
        case D3D10_REGISTER_COMPONENT_FLOAT32:
            return DXGI_FORMAT_R32G32_FLOAT;
            break;

        case D3D10_REGISTER_COMPONENT_UINT32:
            return DXGI_FORMAT_R32G32_UINT;
            break;
        }
    }

    if (mask_ & 0x01)
    {
        switch (type_)
        {
        case D3D10_REGISTER_COMPONENT_FLOAT32:
            return DXGI_FORMAT_R32_FLOAT;
            break;
        }
    }

    return DXGI_FORMAT_UNKNOWN;
}
