#include "App.h"
#include "Lighting/Phong.h"
#include "Lighting/BlinnPhong.h"
#include "Lighting/ToonShading.h"
#include "PostProcess/MonochromePostEffect.h"
#include "PostProcess/NegaPosiPostEffect.h"
#include "PostProcess/SepiaPostEffect.h"
#include "PostProcess/OutlinePostEffect.h"
#include "../Engine/Engine.h"
#include "../Engine/Shader/ShaderManager.h"
#include "../Engine/imGui/imgui_impl_dx11.h"
#include "../Engine/imGui/imgui_impl_win32.h"

bool App::Init()
{
	m_Camera = std::make_unique<Camera>();

	// モデルの初期化
	if (InitModels() == false) {
		return false;
	}
	
	// シェーダーの初期化
	if (InitShaders() == false) {
		return false;
	}
	
	// ライティングオブジェクトの初期化
	InitLigtings();

	// ポストプロセスオブジェクトの初期化
	InitPostProcess();

	return true;
}

void App::Run()
{
	// 更新
	Update();
	
	// 描画
	Draw();
}

void App::Update()
{
	m_ModelManager.Update();
	m_Camera.get()->Update();
}

void App::Draw()
{
	// レンダーターゲットをクリア
	GRAPHICS->ClearRenderTarget();

	// シーン描画
	{
		// シャドウマップに描画
		DrawDepth();

		// 背景モデルを先に描画
		SetUpUnlitShader();
		m_SkyDome.Draw();
		m_Plane.Draw();

		// モデルの描画
		std::vector<ViewModel*> models = {
			m_ModelManager.GetModel(),
			m_SkyDome.GetModel(),
			m_Plane.GetModel()
		};
		m_PostProcessManager.Draw(*models[0], models[1]);
	}

	// GUIの描画
#if 1
	{
		// レンダーターゲットをオンスクリーンに設定
		GRAPHICS->SetRenderTarget(KindRT::RT_ON_SCREEN);

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// モデルGUI
		m_ModelManager.DrawGUI();

		// シェーダーGUI
		LightingManager::GetInstance()->DrawGUI();

		// ポストプロセスGUI
		m_PostProcessManager.DrawGUI();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
#endif
	// 描画終了
	GRAPHICS->FinishRendering();
}

bool App::InitModels()
{
	// モデル作成に必要なパラメーター
	struct LoadParam
	{
		std::string FileName;		// ファイル名(パス無し, Assets/Shader/に入れておく必要がある)
		const char* DisplayName;	// ディスプレイに表示する名前
	};

	LoadParam params[] =
	{
		{"Sphere.obj",	"ShpereModel"},
		{"Cube.obj",	"CubeModel"}
	};
	
	std::string path = "Assets/Models/";
	for (auto param : params)
	{
		if (m_ModelManager.CreateModel((path + param.FileName).c_str(), param.DisplayName) == false)
		{
			return false;
		}
	}
	
	return true;
}

bool App::InitShaders()
{
	// シェーダー作成に必要なパラメーター
	struct LoadParam
	{
		std::string FileName;	// ファイル名(パス無し, Assets/Shader/に入れておく必要がある)
		std::string KeyWord;	// キーワード
		KindShader  Kind;		// シェーダーの種類
	};
	
	// 読み込みリスト
	LoadParam params[]{
		{"SimpleVS.cso",				"VS",			 KindShader::VS},
		{"PhongPS.cso" ,				"PS",			 KindShader::PS},
		{"BlinnPhonePS.cso",			"BPS",			 KindShader::PS},
		{"2DVertexShader.cso",			"2DVS",			 KindShader::VS},
		{"BlurPixelShader.cso",			"BlurPS",		 KindShader::PS},
		{"DepthVertexShader.cso",		"DepthVS",		 KindShader::VS},
		{"DepthPixelShader.cso",		"DepthPS",		 KindShader::PS},
		{"MonochromePixelShader.cso",	"MonochromePS",  KindShader::PS},
		{"NegaPosiPixelShader.cso",		"NegaPosiPS",	 KindShader::PS},
		{"SepiaPixelShader.cso",		"SepiaPS",		 KindShader::PS},
		{"CameraDepthVertexShader.cso",	"CameraDepthVS", KindShader::VS},
		{"OutlinePixelShader.cso",		"OutlinePS",	 KindShader::PS},
		{"UnlitPixelShader.cso",		"UnlitPS",		 KindShader::PS},
		{"2DPixelShader.cso",			"2DPS",			 KindShader::PS},
		{"ToonPixelShader.cso",			"ToonPS",		 KindShader::PS},
	};

	// 読み込み
	std::string path = "Assets/Shader/";
	for (auto& param : params)
	{
		if (ShaderManager::GetInstance()->Load((path + param.FileName).c_str(), param.KeyWord, param.Kind) == false)
		{
			return false;
		}
	}

	return true;
}

void App::InitLigtings()
{
	LightingManager::GetInstance()->Entry<Phong>		("Phong",	"VS", "PS");
	LightingManager::GetInstance()->Entry<BlinnPhong>	("BPhong",	"VS", "BPS");
	LightingManager::GetInstance()->Entry<ToonShading>	("Toon",	"VS", "ToonPS");
}

void App::InitPostProcess()
{
	m_PostProcessManager.Entry<NormalPostEffect>	("Normal",		"2DVS", "2DPS");
	m_PostProcessManager.Entry<BlurPostEffect>		("Blur",		"2DVS", "BlurPS");
	m_PostProcessManager.Entry<MonochromePostEffect>("Monochrome",	"2DVS", "MonochromePS");
	m_PostProcessManager.Entry<NegaPosiPostEffect>	("NegaPosi",	"2DVS", "NegaPosiPS");
	m_PostProcessManager.Entry<SepiaPostEffect>		("Sepia",		"2DVS", "SepiaPS");
	m_PostProcessManager.Entry<OutlinePostEffect>	("Outline",		"2DVS", "OutlinePS");
}

void App::SetUpDepthShader()
{
	// シャドウマップ用のシェーダーをセットする
	ID3D11DeviceContext* context = GRAPHICS->GetContext();
	context->IASetInputLayout(ShaderManager::GetInstance()->GetVertexShader("DepthVS")->GetInputLayout());
	context->VSSetShader(ShaderManager::GetInstance()->GetVertexShader("DepthVS")->GetShaderInterface(), nullptr, 0U);
	context->PSSetShader(ShaderManager::GetInstance()->GetPixelShader("DepthPS")->GetShaderInterface(),  nullptr, 0U);
}

void App::SetUpUnlitShader()
{
	GRAPHICS->SetRenderTarget(KindRT::RT_OFF_SCREEN);

	ID3D11DeviceContext* context = GRAPHICS->GetContext();
	context->IASetInputLayout(ShaderManager::GetInstance()->GetVertexShader("VS")->GetInputLayout());
	context->VSSetShader(ShaderManager::GetInstance()->GetVertexShader("VS")->GetShaderInterface(), nullptr, 0U);
	context->PSSetShader(ShaderManager::GetInstance()->GetPixelShader("UnlitPS")->GetShaderInterface(), nullptr, 0U);

	RenderTarget* rt = GRAPHICS->GetRenderTarget(KindRT::RT_SHADOWMAP);
	ID3D11ShaderResourceView* shadow_map = rt->GetTexture();
	GRAPHICS->GetContext()->PSSetShaderResources(1U, 1U, &shadow_map);
	ID3D11SamplerState* shadow_state = GRAPHICS->GetShadowMapSamplerState();
	GRAPHICS->GetContext()->PSSetSamplers(1U, 1U, &shadow_state);
}

void App::DrawDepth()
{
	// レンダーターゲットをシャドウマップにする
	GRAPHICS->SetRenderTarget(KindRT::RT_SHADOWMAP);
	SetUpDepthShader();
	
	//  描画
	m_ModelManager.GetModel()->Draw();
}