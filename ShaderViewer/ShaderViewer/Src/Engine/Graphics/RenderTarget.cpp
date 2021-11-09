#include "RenderTarget.h"
#include "../Engine.h"

bool RenderTarget::Create(int width_, int height_, DXGI_FORMAT rtFormat_, DXGI_FORMAT dsFormat_, float clearColor_[4])
{
    m_Width  = width_;
    m_Height = height_;

    ID3D11Device* ref_device = GRAPHICS->GetDevice();

    D3D11_TEXTURE2D_DESC texture_desc;
    ZeroMemory(&texture_desc, sizeof(texture_desc));
    texture_desc.Width              = static_cast<UINT>(m_Width);
    texture_desc.Height             = static_cast<UINT>(m_Height);
    texture_desc.MipLevels          = 1U;
    texture_desc.ArraySize          = 1U;
    texture_desc.MiscFlags          = 0U;
    texture_desc.Format             = rtFormat_;
    texture_desc.SampleDesc.Count   = 1U;
    texture_desc.SampleDesc.Quality = 0U;
    texture_desc.Usage              = D3D11_USAGE_DEFAULT;
    texture_desc.BindFlags          = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    texture_desc.CPUAccessFlags     = 0U;

    if (FAILED(ref_device->CreateTexture2D(&texture_desc, nullptr, m_RTTexture.GetAddressOf())))
    {
        return false;
    }

    // レンダーターゲットの作成
    D3D11_RENDER_TARGET_VIEW_DESC rtv_desc;
    ZeroMemory(&rtv_desc, sizeof(rtv_desc));
    rtv_desc.Format             = texture_desc.Format;
    rtv_desc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
    rtv_desc.Texture2D.MipSlice = 0U;

    if (FAILED(ref_device->CreateRenderTargetView(m_RTTexture.Get(), &rtv_desc, m_RenderTargetView.GetAddressOf())))
    {
        return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
    ZeroMemory(&srv_desc, sizeof(srv_desc));
    srv_desc.Format              = texture_desc.Format;
    srv_desc.ViewDimension       = D3D11_SRV_DIMENSION_TEXTURE2D;
    srv_desc.Texture2D.MipLevels = 1U;

    if (FAILED(ref_device->CreateShaderResourceView(m_RTTexture.Get(), &srv_desc, m_Texture.GetAddressOf())))
    {
        return false;
    }

    texture_desc.Format    = dsFormat_;
    texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    if (FAILED(ref_device->CreateTexture2D(&texture_desc, nullptr, m_DSTexture.GetAddressOf())))
    {
        return false;
    }
    if (FAILED(ref_device->CreateDepthStencilView(m_DSTexture.Get(), nullptr, m_DepthStencilView.GetAddressOf())))
    {
        return false;
    }

    if (clearColor_ != nullptr)
    {
        memcpy_s(m_ClearColor, sizeof(float) * 4, clearColor_, sizeof(float) * 4);
    }

    return true;
}

bool RenderTarget::Create(int width_, int height_, ID3D11Texture2D* resouce_, DXGI_FORMAT dsFormat_, float clearColor_[4])
{
    m_Width = width_;
    m_Height = height_;

    ID3D11Device* ref_device = GRAPHICS->GetDevice();
    
    // レンダーターゲットの作成
    if (FAILED(ref_device->CreateRenderTargetView(resouce_, nullptr, m_RenderTargetView.GetAddressOf())))
    {
        return false;
    }

    D3D11_TEXTURE2D_DESC texture_desc;
    resouce_->GetDesc(&texture_desc);
    texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

    if (FAILED(ref_device->CreateTexture2D(&texture_desc, nullptr, m_RTTexture.GetAddressOf())))
    {
        return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
    ZeroMemory(&srv_desc, sizeof(srv_desc));
    srv_desc.Format = texture_desc.Format;
    srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srv_desc.Texture2D.MipLevels = 1U;

    if (FAILED(ref_device->CreateShaderResourceView(m_RTTexture.Get(), &srv_desc, m_Texture.GetAddressOf())))
    {
        return false;
    }

    texture_desc.Format = dsFormat_;
    texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    if (FAILED(ref_device->CreateTexture2D(&texture_desc, nullptr, m_DSTexture.GetAddressOf())))
    {
        return false;
    }
    if (FAILED(ref_device->CreateDepthStencilView(m_DSTexture.Get(), nullptr, m_DepthStencilView.GetAddressOf())))
    {
        return false;
    }

    if (clearColor_ != nullptr)
    {
        memcpy_s(m_ClearColor, sizeof(float) * 4, clearColor_, sizeof(float) * 4);
    }

    return true;
}
