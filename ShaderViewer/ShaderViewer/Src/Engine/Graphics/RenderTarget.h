#ifndef RENDER_TARGET_H_
#define RENDER_TARGET_H_

#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

/**
* @brief �����_�[�^�[�Q�b�g�N���X
*/
class RenderTarget
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	RenderTarget():
		m_Width(0),
		m_Height(0),
		m_ClearColor{0.f}
	{}

	/**
	* @fn bool Create(int width_, int height_, DXGI_FORMAT rtFormat_, DXGI_FORMAT dsFormat_, float clearColor_[4])
	* @brief �����_�[�^�[�^�[�Q�b�g�̍쐬���s���֐�
	* @param[in] width_ ����
	* @param[in] height_ �c��
	* @param[in] rtFormat_ �����_�[�o�b�t�@�t�H�[�}�b�g
	* @param[in] dsFormat_ �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g
	* @param[in] clearColor_ �N���A�J���[
	* @return bool �����������ǂ�����^�U�ŕԂ�
	*/
	bool Create(UINT width_, UINT height_, DXGI_FORMAT rtFormat_, DXGI_FORMAT dsFormat_, float clearColor_[4]);
	
	/**
	* @fn bool Create(int width_, int height_, ID3D11Texture2D* resouce_, DXGI_FORMAT dsFormat_, float clearColor_[4])
	* @brief �����_�[�^�[�^�[�Q�b�g�̍쐬���s���֐�
	* @param[in] width_ ����
	* @param[in] height_ �c��
	* @param[in] resouce_ �����_�[�o�b�t�@�e�N�X�`��
	* @param[in] dsFormat_ �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g
	* @param[in] clearColor_ �N���A�J���[
	* @return bool �����������ǂ�����^�U�ŕԂ�
	*/
	bool Create(UINT width_, UINT height_, ID3D11Texture2D* resouce_, DXGI_FORMAT dsFormat_, float clearColor_[4]);

	/**
	* @fn int GetWidth()
	* @brief �o�b�t�@�̉�����Ԃ��֐�
	* @return int ����
	*/
	int GetWidth()  { return m_Width;  }

	/**
	* @fn int GetHeight()
	* @brief �o�b�t�@�̏c����Ԃ��֐�
	* @return int �c��
	*/
	int GetHeight() { return m_Height; }

	/**
	* @fn float* GetClearColor()
	* @brief �o�b�t�@�̃N���A�J���[��Ԃ��֐�
	* @return float* �N���A�J���[
	*/
	float* GetClearColor() { return m_ClearColor; }

	/**
	* @fn ID3D11RenderTargetView* GetRenderTargetView()
	* @brief RenderTargetView��Ԃ��֐�
	* @return ID3D11RenderTargetView* RenderTargetView
	*/
	ID3D11RenderTargetView* GetRenderTargetView() { return m_RenderTargetView.Get(); }

	/**
	* @fn ID3D11DepthStencilView* GetDepthStencilView()
	* @brief DepthStencilView��Ԃ��֐�
	* @return DepthStencilView* DepthStencilView
	*/
	ID3D11DepthStencilView* GetDepthStencilView() { return m_DepthStencilView.Get(); }

	/**
	* @fn ID3D11ShaderResourceView* GetTexture()
	* @brief �o�b�t�@�p�e�N�X�`���擾�֐�
	* @return ID3D11ShaderResourceView* �e�N�X�`��
	*/
	ID3D11ShaderResourceView* GetTexture() { return m_Texture.Get(); }

private:
	/**
	* @fn bool Create(DXGI_FORMAT dsFormat_, float clearColor_[4])
	* @brief �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���o�b�t�@�̍쐬�֐�
	* @param[in] dsFormat_ �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g
	* @param[in] clearColor_ �N���A�J���[
	* @return bool �����������ǂ�����^�U�ŕԂ�
	* @details ���O��RT�p�o�b�t�@(m_RTTexture)���쐬���Ă����K�v������
	*/
	bool CreateRTVandDSV(DXGI_FORMAT dsFormat_, float clearColor_[4]);

private:
	UINT  m_Width;			//! ����
	UINT  m_Height;			//! �c��
	float m_ClearColor[4];	//! �N���A�J���[

	ComPtr<ID3D11RenderTargetView>   m_RenderTargetView; //! �����_�[�^�[�Q�b�g�r���[
	ComPtr<ID3D11Texture2D>		     m_RTTexture;		 //! �����_�[�^�[�Q�b�g�e�N�X�`��
	ComPtr<ID3D11DepthStencilView>   m_DepthStencilView; //! �[�x�X�e���V���r���[
	ComPtr<ID3D11Texture2D>			 m_DSTexture;		 //! �[�x�X�e���V���e�N�X�`��
	
	ComPtr<ID3D11ShaderResourceView> m_Texture;			 //! �V�F�[�_�[�ɑ��邽�ߗp�̃e�N�X�`��
};

#endif