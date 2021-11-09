#include "../DirectXTex/DirectXTex.h"
#include <D3D11.h>
#include <codecvt>
#include "TextureManager.h"
#include "../Engine.h"
#include "../../Utility/Utility.h"


#if _DEBUG
#pragma comment(lib, "Src/Engine/DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "Src/Engine/DirectXTex/x64/Release/DirectXTex.lib")
#endif


bool TextureManager::Init(ID3D11Device* device_)
{
	if (device_ == nullptr) return false;

	// 定数バッファの作成
	if (CreateConstantBuffer(device_) == false)
	{
		return false;
	}

	// サンプラーの作成
	if (CreateSamplerState(device_) == false)
	{
		return false;
	}

	return true;
}

bool TextureManager::Load(const char* fileName_, std::string keyword_)
{
	// すでにキーが存在する場合は読み込みが終わっているので早期リターン
	if (m_Textures.find(keyword_) != m_Textures.end()) return true;

	TextureData* tex_data = &m_Textures[keyword_];

	// ファイル分解
	char buffer[256];
	ZeroMemory(buffer, sizeof(char) * 256);
	memcpy(buffer, fileName_, sizeof(char) * 256);

	Replace('\\', '/', buffer);
	std::string replace_file_name = buffer;

	// 「/」で分解
	std::vector<std::string> split_list = Split(buffer, '/');

	std::string path = fileName_;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring wstr_file_name = cv.from_bytes(path);
	
	const char* extension = "";
	DirectX::TexMetadata  metadata;
	DirectX::ScratchImage image;
	HRESULT hr;

	// 拡張子を保存する
	for (size_t i = strlen(fileName_); i != 0; --i)
	{
		if (fileName_[i - 1] == '.') extension = &fileName_[i];
	}

	// DDSファイルの読み込み
	if (strcmp(extension, "dds") == 0)
	{
		hr = DirectX::LoadFromDDSFile(wstr_file_name.c_str(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, &metadata, image);
	}
	// TGAファイルの読み込み
	else if (strcmp(extension, "tga") == 0)
	{
		hr = DirectX::LoadFromTGAFile(wstr_file_name.c_str(), &metadata, image);
	}
	// WICファイル(bmp,jpg,png)の読み込み
	else
	{
		hr = DirectX::LoadFromWICFile(wstr_file_name.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata, image);
	}

	// 読み込みに失敗したとき
	if (FAILED(hr))
	{
		m_Textures.erase(keyword_);
		return false;
	}

	// デバイスを取得
	ID3D11Device* device = GRAPHICS->GetDevice();

	if (FAILED(DirectX::CreateShaderResourceView(
		device,
		image.GetImages(),
		image.GetImageCount(),
		metadata,
		tex_data->Texture.GetAddressOf())))
	{
		m_Textures.erase(keyword_);
		return false;
	}

	tex_data->Width  = static_cast<UINT>(metadata.width) ;
	tex_data->Height = static_cast<UINT>(metadata.height);

	// 頂点バッファの作成
	if (CreateVertexBuffer(*tex_data, device) == false)
	{
		m_Textures.erase(keyword_);
		return false;
	}
	
	// インデックスバッファの作成
	if (CreateIndexBuffer(*tex_data, device) == false)
	{
		m_Textures.erase(keyword_);
		return false;
	}

	return true;
}

void TextureManager::Render(std::string keyword_, DirectX::XMFLOAT3 pos_)
{
	if (m_Textures.find(keyword_) == m_Textures.end()) return;
	
	ID3D11DeviceContext* context = GRAPHICS->GetContext();

	// 入力レイアウトを設定
	context->IASetInputLayout(m_InputLayout.Get());

	TextureData* texture = &m_Textures[keyword_];
	
	// 頂点バッファの登録
	UINT stride = sizeof(Vertex2D);
	UINT offset = 0;
	context->IASetVertexBuffers(0U, 1U, texture->VertexBuffer.GetAddressOf(), &stride, &offset);
	
	// インデックスバッファの登録
	context->IASetIndexBuffer(texture->IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0U);
	
	// プリミティブタイプの設定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ワールド行列の設定
	int client_width  = WINDOW->GetClientWidth();
	int client_height = WINDOW->GetClientHeight();
	m_ConstantBufferData.World		= DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(1.f - (pos_.x / (client_width/2)), 1.f - (pos_.y / (client_height / 2)), pos_.z));
	
	// 正射影行列の設定
	//m_ConstantBufferData.Projection = DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(0.0f, client_width, client_height, 0.0f, -1.0f, 1.0f));
	context->UpdateSubresource(m_ConstantBuffer.Get(), 0U, nullptr, &m_ConstantBufferData, 0U, 0U);
	
	// 定数バッファの設定
	context->VSSetConstantBuffers(0U, 1U, m_ConstantBuffer.GetAddressOf());

	// シェーダーの設定
	context->VSSetShader(m_VertexShader->GetShaderInterface(), nullptr, 0U);
	context->PSSetShader(m_PixelShader->GetShaderInterface(), nullptr, 0U);

	// テクスチャをシェーダに登録
	context->PSSetSamplers(0U, 1U, m_SamplerState.GetAddressOf());
	context->PSSetShaderResources(0U, 1U, texture->Texture.GetAddressOf());

	// インデックスバッファで描画
	context->DrawIndexed(6U, 0U, 0U);
}

void TextureManager::Release(std::string keyword_)
{
	auto itr = m_Textures.find(keyword_);
	
	if (itr != m_Textures.end())
	{
		m_Textures.erase(itr);
	}
}

void TextureManager::AllRelease()
{
	if (m_Textures.empty()) return;
	m_Textures.clear();
}

bool TextureManager::CreateVertexBuffer(TextureData& data_, ID3D11Device* device_)
{
	if (device_ == nullptr) return false;

	float tex_width  = static_cast<float>(data_.Width);
	float tex_height = static_cast<float>(data_.Height);

	// 四角形ポリゴンの頂点を定義
	Vertex2D vertices[4]{
		{{0.0f,		 0.0f,		 0.0f}, {0.0f, 0.0f}},	// 左上頂点
		{{tex_width, 0.0f,		 0.0f}, {1.0f, 0.0f}},	// 右上頂点
		{{0.0f,		 tex_height, 0.0f}, {0.0f, 1.0f}},	// 左下頂点
		{{tex_width, tex_height, 0.0f}, {1.0f, 1.0f}}	// 右下頂点
	};

	// バッファの設定
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth	    = sizeof(Vertex2D) * 4;
	buffer_desc.Usage			= D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags  = 0;
	
	// リソースの設定
	D3D11_SUBRESOURCE_DATA init_data;
	ZeroMemory(&init_data, sizeof(init_data));
	init_data.pSysMem = vertices;

	// 頂点バッファの作成
	if (FAILED(device_->CreateBuffer(
		&buffer_desc,										// バッファ情報
		&init_data,										    // リソース情報
		data_.VertexBuffer.GetAddressOf())))				// 作成されたバッファの格納先
	{
		return false;
	}

	return true;
}

bool TextureManager::CreateIndexBuffer(TextureData& data_, ID3D11Device* device_)
{
	if (device_ == nullptr) return false;

	WORD index[]{
		0, 1, 2,
		2, 1, 3
	};

	//頂点バッファ作成
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth		= sizeof(WORD) * 6;	// バッファのサイズ
	buffer_desc.Usage			= D3D11_USAGE_DEFAULT;				// 使用方法
	buffer_desc.BindFlags		= D3D11_BIND_INDEX_BUFFER;			// BIND設定
	buffer_desc.CPUAccessFlags  = 0;								// リソースへのCPUのアクセス権限についての設定

	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = index;	// バッファの中身の設定
	
	// バッファ作成
	if (FAILED(device_->CreateBuffer(
		&buffer_desc,			// バッファ情報
		&init_data,			// リソース情報
		data_.IndexBuffer.GetAddressOf())))	// 作成されたバッファの格納先
	{
		return false;
	}

	return true;
}

bool TextureManager::CreateConstantBuffer(ID3D11Device* device_)
{
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth			= sizeof(ConstantBuffer2D);
	buffer_desc.Usage				= D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags		= 0;
	buffer_desc.MiscFlags			= 0;
	buffer_desc.StructureByteStride = 0;

	if (FAILED(device_->CreateBuffer(&buffer_desc, nullptr, m_ConstantBuffer.GetAddressOf())))
	{
		return false;
	}

	return true;
}

bool TextureManager::CreateSamplerState(ID3D11Device* device_)
{
	// サンプラの設定
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter			= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU		= D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressV		= D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressW		= D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler_desc.BorderColor[0] = 1.0f;
	sampler_desc.BorderColor[1] = 1.0f;
	sampler_desc.BorderColor[2] = 1.0f;
	sampler_desc.BorderColor[3] = 1.0f;
	sampler_desc.MinLOD		    = 0.0f;
	sampler_desc.MaxLOD		    = D3D11_FLOAT32_MAX;

	// サンプラの作成
	if (FAILED(device_->CreateSamplerState(&sampler_desc, m_SamplerState.GetAddressOf())))
	{
		return false;
	}

	return true;
}
