#include <stdio.h>
#include "DirectGraphics.h"
#include "../Engine.h"
#include "../../App/Lighting/LightingBase.h"
#include "../../App/Config.h"

#pragma comment(lib,"d3d11.lib")

// シャドウマップのサイズ
const int DEPTH_TEXTURE_SIZE = 2048;

bool DirectGraphics::Init()
{
    // デバイスとスワップチェインの作成 
    if (CreateDeviceAndSwapChain() == false)
    {
        return true;
    }

    // レンダーターゲットビューの作成
    if (CreateRenderTargetView() == false)
    {
        return false;
    }

    // コンスタントバッファの作成
    if (CreateConstantBuffer() == false)
    {
        return false;
    }

    // テクスチャサンプラの作成
    if (CreateTextureSampler() == false)
    {
        return false;
    }

    // ラスタライザの作成
    if (CreateRasterizer() == false)
    {
        return false;
    }

    // ライト設定
    SetUpLight();
    
    // シャドウマップをサンプリングする際のUV変換行列の設定
    DirectX::XMMATRIX mat_depth_bias = DirectX::XMMatrixSet
    (
        0.5f, 0.0f, 0.0f, 0.0f,
        0.0f,-0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f
    );

    DirectX::XMStoreFloat4x4(&m_ConstantBufferData.ClipUV, DirectX::XMMatrixTranspose(mat_depth_bias));
    
    return true;
}

void DirectGraphics::Release()
{
}

void DirectGraphics::SetRenderTarget(KindRT rt_)
{
    RenderTarget* rt = &m_RenderTargets[static_cast<int>(rt_)];
    ID3D11RenderTargetView* rtv = rt->GetRenderTargetView();
    ID3D11DepthStencilView* dsv = rt->GetDepthStencilView();

    // レンダーターゲットの設定
    m_Context->OMSetRenderTargets(1U, &rtv, dsv);

    // ビューポートの設定
    D3D11_VIEWPORT vp{ 0 };
    vp.Width    = static_cast<FLOAT>(rt->GetWidth());
    vp.Height   = static_cast<FLOAT>(rt->GetHeight());
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 0.0f;
    m_Context->RSSetViewports(1U, &vp);
}

void DirectGraphics::ClearRenderTarget()
{
    for (int i = 0; i < static_cast<int>(KindRT::RT_NUM); ++i)
    {
        RenderTarget* rt = &m_RenderTargets[i];

        // バッファカラーのクリア
        ID3D11RenderTargetView* rtv = rt->GetRenderTargetView();
        m_Context->ClearRenderTargetView(rtv, rt->GetClearColor());

        // デプスステンシルバッファのクリア
        ID3D11DepthStencilView* dsv = rt->GetDepthStencilView();
        m_Context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }
}

void DirectGraphics::ClearRenderTarget(KindRT rt_)
{
    RenderTarget* rt = &m_RenderTargets[static_cast<int>(rt_)];

    // バッファカラーのクリア
    ID3D11RenderTargetView* rtv = rt->GetRenderTargetView();
    m_Context->ClearRenderTargetView(rtv, rt->GetClearColor());

    // デプスステンシルバッファのクリア
    ID3D11DepthStencilView* dsv = rt->GetDepthStencilView();
    m_Context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DirectGraphics::FinishRendering()
{
    // バックバッファをフロントバッファに送信する   
    m_SwapChain->Present(1U, 0U);
}

void DirectGraphics::SetRasterizerMode(RasterizerMode mode_)
{
    m_Context->RSSetState(m_RasterizerState->GetAddressOf()[static_cast<int>(mode_)]);
}

void DirectGraphics::SetTexture(ID3D11ShaderResourceView* texture_)
{
    m_Context->PSSetSamplers(
        0U,
        1U,
        m_SamplerState.GetAddressOf());

    m_Context->PSSetShaderResources(
        0U,
        1U,
        &texture_);
    
}

void DirectGraphics::SetMaterial(ObjMaterial* material_)
{
    // nullptrなら黒にする
    if (!material_) {
        m_ConstantBufferData.MaterialAmbient  = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
        m_ConstantBufferData.MaterialDiffuse  = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
        m_ConstantBufferData.MaterialSpecular = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
        return;
    }

    // アンビエント
    m_ConstantBufferData.MaterialAmbient  = DirectX::XMFLOAT4(material_->Ambient[0], material_->Ambient[1],
                                                              material_->Ambient[2], material_->Ambient[3]);
    // ディヒューズ
    m_ConstantBufferData.MaterialDiffuse  = DirectX::XMFLOAT4(material_->Diffuse[0],  material_->Diffuse[1],
                                                              material_->Diffuse[2],  material_->Diffuse[3]);
    // スペキュラ
    m_ConstantBufferData.MaterialSpecular = DirectX::XMFLOAT4(material_->Specular[0], material_->Specular[1], 
                                                              material_->Specular[2], material_->Specular[3]);
}

void DirectGraphics::SetUpDxgiSwapChanDesc(DXGI_SWAP_CHAIN_DESC* dxgi_)
{
    // スワップチェイン作成時に必要な設定
    ZeroMemory(dxgi_, sizeof(DXGI_SWAP_CHAIN_DESC));
    
    // バッファの数
    dxgi_->BufferCount = 1U;
    // バッファの横幅
    dxgi_->BufferDesc.Width  = static_cast<UINT>(WINDOW->GetClientWidth());
    // バッファの縦幅
    dxgi_->BufferDesc.Height = static_cast<UINT>(WINDOW->GetClientHeight());
    // バッファのカラーフォーマット
    dxgi_->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // リフレッシュレートの分子
    dxgi_->BufferDesc.RefreshRate.Numerator   = 60U;
    // リフレッシュレートの分母
    dxgi_->BufferDesc.RefreshRate.Denominator = 1U;
    // スキャンラインの方法
    // バックバッファをフリップしたときにハードウェアがパソコンのモニターに
    // 点をどう描くかを設定する
    // 特に理由がなければデフォルト値であるDXGI_MODE_SCANLINE_ORDER_UNSPECIFIEDでOK
    dxgi_->BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    // ウィンドウのサイズに応じてスケーリングするかどうかの設定
    // スケーリングする場合   DXGI_MODE_SCALING_STRETCHED 
    // スケーリングしない場合 DXGI_MODE_SCALING_CENTERED
    dxgi_->BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
    // バッファの使用方法
    // レンダーターゲットとして使用する場合は、DXGI_USAGE_RENDER_TARGET_OUTPUT 
    // シェーダー入力用として使用する場合はDXGI_USAGE_SHADER_INPUT
    dxgi_->BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    // 出力対象のウィンドウハンドル
    dxgi_->OutputWindow = WINDOW->GetWindowHandle();
    // マルチサンプリングのサンプル数(未使用は1)
    dxgi_->SampleDesc.Count = 1U;
    // マルチサンプリングの品質(未使用は0)
    dxgi_->SampleDesc.Quality = 0U;
    // ウィンドウモード指定
    dxgi_->Windowed = true;
    // スワップチェインの動作オプション
    // DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCHを指定した場合
    // フルスクリーンとウィンドウモードの切り替えが可能
    dxgi_->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
}

bool DirectGraphics::CreateDeviceAndSwapChain()
{
    DXGI_SWAP_CHAIN_DESC swap_chain_desc;
    SetUpDxgiSwapChanDesc(&swap_chain_desc);
    
    // 適応されたFutureレベルも取得できる
    if (FAILED(D3D11CreateDeviceAndSwapChain(
        // デバイス作成時に使用するビデオアダプタの指定
        // nullptrで既定のアダプタを使用する
        nullptr,
        // ドライバのタイプ
        // D3D_DRIVER_TYPEのいずれかを指定
        // 通常はD3D_DRIVER_TYPE_HARDWAREで問題ない
        D3D_DRIVER_TYPE_HARDWARE,
        // D3D_DRIVER_TYPE_SOFTWARE指定時に使用
        nullptr,
        // ランタイムレイヤーのフラグ指定
        0,
        // D3D_FEATURE_LEVEL指定で自分で定義した配列を指定可能
        nullptr,
        // 上のD3D_FEATURE_LEVEL配列の要素数
        0,
        // SDKバージョン
        D3D11_SDK_VERSION,
        // 設定済みのDXGI_SWAP_CHAIN_DESC
        &swap_chain_desc,
        // 初期化が完了したSwapChainの出力先 
        &m_SwapChain,
        // 初期化が完了したDeviceの出力先 
        &m_Device,
        // 最終的に決定したFutureレベルの出力先
        &m_FeatureLevel,
        // 作成されたコンテキストを受け取るためのID3D11DeviceContextポインタアドレス
        &m_Context)))
    {
        return false;
    }
    
    return true;
}

bool DirectGraphics::CreateRenderTargetView()
{
    /*
        RenderTargetViewはレンダリングパイプラインからアウトプットされる
        ピクセル情報を保存するViewのことで、このViewの内容をゲーム画面に反映させる。
    */

    // RenderViewはSwapChainがもつバッファを使用して作成するので
    // GetBufferを使用してバッファを取得する
    ID3D11Texture2D* back_buffer = nullptr;
    if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer)))
    {
        return false;
    }

    float color[4]{ 0.f,0.f,1.f,1.f };
    m_RenderTargets[static_cast<int>(KindRT::RT_ON_SCREEN)].Create(
        WINDOW->GetClientWidth(),
        WINDOW->GetClientHeight(),
        back_buffer,
        DXGI_FORMAT_D32_FLOAT,
        color
    );

    // これ以降バッファを使用しないので、解放しておく
    back_buffer->Release();

    m_RenderTargets[static_cast<int>(KindRT::RT_OFF_SCREEN)].Create(
        WINDOW->GetClientWidth(), 
        WINDOW->GetClientHeight(), 
        DXGI_FORMAT_R8G8B8A8_UNORM, 
        DXGI_FORMAT_D32_FLOAT, 
        color
    );

    color[0] = color[1] = color[2] = 1.0f;
    m_RenderTargets[static_cast<int>(KindRT::RT_SHADOWMAP)].Create(
        DEPTH_TEXTURE_SIZE,
        DEPTH_TEXTURE_SIZE,
        DXGI_FORMAT_R32_FLOAT,
        DXGI_FORMAT_D32_FLOAT,
        color
    );

    return true;
}

bool DirectGraphics::CreateConstantBuffer()
{
    D3D11_BUFFER_DESC buffer_desc{ 0 };
    buffer_desc.ByteWidth           = sizeof(ConstantBuffer);
    buffer_desc.Usage               = D3D11_USAGE_DEFAULT;
    buffer_desc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
    buffer_desc.CPUAccessFlags      = 0U;
    buffer_desc.MiscFlags           = 0U;
    buffer_desc.StructureByteStride = 0U;

    if (FAILED(m_Device->CreateBuffer(&buffer_desc, nullptr, m_ConstantBuffer.GetAddressOf())))
    {
        return false;
    }

    buffer_desc.ByteWidth = sizeof(ConstBoneBuffer);
    if (FAILED(m_Device->CreateBuffer(&buffer_desc, nullptr, m_ConstBoneBuffer.GetAddressOf())))
    {
        return false;
    }

    buffer_desc.ByteWidth = sizeof(ConstantBuffer2D);
    if (FAILED(m_Device->CreateBuffer(&buffer_desc, nullptr, m_ConstantBuffer2D.GetAddressOf())))
    {
        return false;
    }

    return true;
}

bool DirectGraphics::CreateTextureSampler()
{
    D3D11_SAMPLER_DESC sampler_desc;

    ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));

    sampler_desc.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;


    if (FAILED(m_Device->CreateSamplerState(&sampler_desc, m_SamplerState.GetAddressOf())))
    {
        return false;
    }

    sampler_desc.Filter         = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
    sampler_desc.ComparisonFunc = D3D11_COMPARISON_GREATER;
    sampler_desc.MaxAnisotropy  = 1;
    sampler_desc.AddressU       = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampler_desc.AddressV       = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampler_desc.AddressW       = D3D11_TEXTURE_ADDRESS_CLAMP;

    if (FAILED(m_Device->CreateSamplerState(&sampler_desc, m_ShadowSamplerState.GetAddressOf())))
    {
        return false;
    }

    return true;
}

bool DirectGraphics::CreateRasterizer()
{
    /*
        カリングなし
    */
    // ラスタライザ
    D3D11_RASTERIZER_DESC ras_desc;
    ID3D11RasterizerState* RasBackCulling = nullptr;
    ZeroMemory(&ras_desc, sizeof(ras_desc));
    ras_desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;  //! レンダリングするポリゴンを塗りつぶす
    ras_desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;   //! カリングなし
    ras_desc.FrontCounterClockwise = FALSE;                 //! 時計周りが表、反時計回りが裏
    if (FAILED(m_Device->CreateRasterizerState(&ras_desc, &m_RasterizerState->GetAddressOf()[static_cast<int>(RasterizerMode::MODE_CULL_NONE)])))
    {
        return false;
    }

    /*
        背面カリング
    */
    ras_desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;   //! 背面カリング
    if (FAILED(m_Device->CreateRasterizerState(&ras_desc, &m_RasterizerState->GetAddressOf()[static_cast<int>(RasterizerMode::MODE_CULL_BACK)])))
    {
        return false;
    }

    /*
     背面カリング
    */
    ras_desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;   //! 背面カリング
    if (FAILED(m_Device->CreateRasterizerState(&ras_desc, &m_RasterizerState->GetAddressOf()[static_cast<int>(RasterizerMode::MODE_CULL_FRONT)])))
    {
        return false;
    }

    /*
        ワイヤーフレーム
    */
    ras_desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;  //! ポリゴンを塗りつぶさない
    if (FAILED(m_Device->CreateRasterizerState(&ras_desc, &m_RasterizerState->GetAddressOf()[static_cast<int>(RasterizerMode::MODE_WIREFRAME)])))
    {
        return false;
    }

    // デフォルトは背面カリング
    SetRasterizerMode(RasterizerMode::MODE_CULL_BACK);
    return true;
}

void DirectGraphics::SetUpLight()
{
    //ライトの位置
    m_LightPos = ConfigParameter::m_LightPos;
    DirectX::XMStoreFloat4(&m_ConstantBufferData.Light, DirectX::XMVector3Normalize(DirectX::XMVectorSet(m_LightPos.x, m_LightPos.y, m_LightPos.z, 0.0f)));

    // View行列
    DirectX::XMMATRIX light_view = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(m_LightPos.x, m_LightPos.y, m_LightPos.z, 0.0f),
        DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
        DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f));

    DirectX::XMStoreFloat4x4(&m_ConstantBufferData.LightView, DirectX::XMMatrixTranspose(light_view));

    // Projection行列
    DirectX::XMMATRIX proj_mat = DirectX::XMMatrixOrthographicLH(DepthViewSize, DepthViewSize, -1, 1000.f);
    DirectX::XMStoreFloat4x4(&GRAPHICS->GetConstantBufferData()->LightProjection, DirectX::XMMatrixTranspose(proj_mat));

}