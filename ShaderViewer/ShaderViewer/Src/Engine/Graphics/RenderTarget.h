#ifndef RENDER_TARGET_H_
#define RENDER_TARGET_H_

#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

/**
* @brief レンダーターゲットクラス
*/
class RenderTarget
{
public:
	/**
	* @brief コンストラクタ
	*/
	RenderTarget():
		m_Width(0),
		m_Height(0),
		m_ClearColor{0.f}
	{}

	/**
	* @fn bool Create(int width_, int height_, DXGI_FORMAT rtFormat_, DXGI_FORMAT dsFormat_, float clearColor_[4])
	* @brief レンダーターターゲットの作成を行う関数
	* @param[in] width_ 横幅
	* @param[in] height_ 縦幅
	* @param[in] rtFormat_ レンダーバッファフォーマット
	* @param[in] dsFormat_ デプスステンシルバッファのフォーマット
	* @param[in] clearColor_ クリアカラー
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool Create(UINT width_, UINT height_, DXGI_FORMAT rtFormat_, DXGI_FORMAT dsFormat_, float clearColor_[4]);
	
	/**
	* @fn bool Create(int width_, int height_, ID3D11Texture2D* resouce_, DXGI_FORMAT dsFormat_, float clearColor_[4])
	* @brief レンダーターターゲットの作成を行う関数
	* @param[in] width_ 横幅
	* @param[in] height_ 縦幅
	* @param[in] resouce_ レンダーバッファテクスチャ
	* @param[in] dsFormat_ デプスステンシルバッファのフォーマット
	* @param[in] clearColor_ クリアカラー
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool Create(UINT width_, UINT height_, ID3D11Texture2D* resouce_, DXGI_FORMAT dsFormat_, float clearColor_[4]);

	/**
	* @fn int GetWidth()
	* @brief バッファの横幅を返す関数
	* @return int 横幅
	*/
	int GetWidth()  { return m_Width;  }

	/**
	* @fn int GetHeight()
	* @brief バッファの縦幅を返す関数
	* @return int 縦幅
	*/
	int GetHeight() { return m_Height; }

	/**
	* @fn float* GetClearColor()
	* @brief バッファのクリアカラーを返す関数
	* @return float* クリアカラー
	*/
	float* GetClearColor() { return m_ClearColor; }

	/**
	* @fn ID3D11RenderTargetView* GetRenderTargetView()
	* @brief RenderTargetViewを返す関数
	* @return ID3D11RenderTargetView* RenderTargetView
	*/
	ID3D11RenderTargetView* GetRenderTargetView() { return m_RenderTargetView.Get(); }

	/**
	* @fn ID3D11DepthStencilView* GetDepthStencilView()
	* @brief DepthStencilViewを返す関数
	* @return DepthStencilView* DepthStencilView
	*/
	ID3D11DepthStencilView* GetDepthStencilView() { return m_DepthStencilView.Get(); }

	/**
	* @fn ID3D11ShaderResourceView* GetTexture()
	* @brief バッファ用テクスチャ取得関数
	* @return ID3D11ShaderResourceView* テクスチャ
	*/
	ID3D11ShaderResourceView* GetTexture() { return m_Texture.Get(); }

private:
	/**
	* @fn bool Create(DXGI_FORMAT dsFormat_, float clearColor_[4])
	* @brief レンダーターゲットとデプスステンシルバッファの作成関数
	* @param[in] dsFormat_ デプスステンシルバッファのフォーマット
	* @param[in] clearColor_ クリアカラー
	* @return bool 成功したかどうかを真偽で返す
	* @details 事前にRT用バッファ(m_RTTexture)を作成しておく必要がある
	*/
	bool CreateRTVandDSV(DXGI_FORMAT dsFormat_, float clearColor_[4]);

private:
	UINT  m_Width;			//! 横幅
	UINT  m_Height;			//! 縦幅
	float m_ClearColor[4];	//! クリアカラー

	ComPtr<ID3D11RenderTargetView>   m_RenderTargetView; //! レンダーターゲットビュー
	ComPtr<ID3D11Texture2D>		     m_RTTexture;		 //! レンダーターゲットテクスチャ
	ComPtr<ID3D11DepthStencilView>   m_DepthStencilView; //! 深度ステンシルビュー
	ComPtr<ID3D11Texture2D>			 m_DSTexture;		 //! 深度ステンシルテクスチャ
	
	ComPtr<ID3D11ShaderResourceView> m_Texture;			 //! シェーダーに送るため用のテクスチャ
};

#endif