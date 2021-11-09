#include "App.h"
#include "../Engine/Engine.h"
#include "../Engine/Shader/ShaderManager.h"
#include "Lighting/Phong.h"
#include "Lighting/BlinnPhong.h"
#include "Lighting/ToonShading.h"
#include "PostProcess/MonochromePostEffect.h"
#include "PostProcess/NegaPosiPostEffect.h"
#include "PostProcess/SepiaPostEffect.h"
#include "PostProcess/OutlinePostEffect.h"
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
	if (InitShader() == false) {
		return false;
	}
	// ライティングオブジェクトの初期化
	if (InitLigting() == false) {
		return false;
	}
	// ポストプロセスオブジェクトの初期化
	InitPostProcess();

	return true;
}

void App::Run()
{
	// 更新
	Update();
	
	// 描画
	Render();
}

void App::Update()
{
	m_ModelManager.Update();
	m_Camera.get()->Update();
}

void App::Render()
{
	// レンダーターゲットをクリア
	GRAPHICS->ClearRenderTarget();

	// シーン描画
	{
		// シャドウマップに描画
		DrawDepth();

		// 背景モデルを先に描画
		SetUpUnlitShader();
		m_SkyDome.Render();
		m_Plane.Render();

		// モデルの描画
		std::vector<ViewModel*> models = {
			m_ModelManager.GetModel(),
			m_SkyDome.GetModel(),
			m_Plane.GetModel()
		};
		m_PostProcessManager.Render(*models[0], models[1]);
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
	if (m_ModelManager.CreateModel("Assets/Models/Sphere.obj", "ShpereModel") == false)
	{
		return false;
	}
	if (m_ModelManager.CreateModel("Assets/Models/Cube.obj", "CubeModel") == false)
	{
		return false;
	}

	return true;
}

bool App::InitShader()
{
	if (ShaderManager::GetInstance()->Load("Assets/Shader/SimpleVS.cso", "VS", KindShader::VS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/PhongPS.cso", "PS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/BlinnPhonePS.cso", "BPS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/2DVertexShader.cso", "2DVS", KindShader::VS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/BlurPixelShader.cso", "BlurPS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/DepthVertexShader.cso", "DepthVS", KindShader::VS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/DepthPixelShader.cso", "DepthPS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/MonochromePixelShader.cso", "MonochromePS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/NegaPosiPixelShader.cso", "NegaPosiPS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/SepiaPixelShader.cso", "SepiaPS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/CameraDepthVertexShader.cso", "CameraDepthVS", KindShader::VS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/OutlinePixelShader.cso", "OurlinePS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/UnlitPixelShader.cso", "UnlitPS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/2DPixelShader.cso", "2DPS", KindShader::PS) == false)
	{
		return false;
	}
	if (ShaderManager::GetInstance()->Load("Assets/Shader/ToonPixelShader.cso", "ToonPS", KindShader::PS) == false)
	{
		return false;
	}

	return true;
}

bool App::InitLigting()
{
	auto shader_manager = ShaderManager::GetInstance();
	
	std::unique_ptr<LightingBase> phong = std::make_unique<Phong>();
	bool success = phong.get()->Init(shader_manager->GetVertexShader("VS"), shader_manager->GetPixelShader("PS"));
	if (!success){
		return false;
	}
	LightingManager::GetInstance()->Entry("Phong", std::move(phong));

	std::unique_ptr<LightingBase> blinn = std::make_unique<BlinnPhong>();
	success = blinn.get()->Init(shader_manager->GetVertexShader("VS"), shader_manager->GetPixelShader("BPS"));
	if (!success){
		return false;
	}
	LightingManager::GetInstance()->Entry("BPhong", std::move(blinn));

	std::unique_ptr<LightingBase> toon = std::make_unique<ToonShading>();
	success = toon.get()->Init(shader_manager->GetVertexShader("VS"), shader_manager->GetPixelShader("ToonPS"));
	if (!success) {
		return false;
	}
	LightingManager::GetInstance()->Entry("Toon", std::move(toon));
	

	return true;
}

void App::InitPostProcess()
{
	auto shader_manager = ShaderManager::GetInstance();

	std::unique_ptr<PostEffectBase> normal		= std::make_unique<NormalPostEffect>(shader_manager->GetVertexShader("2DVS"), shader_manager->GetPixelShader("2DPS"));
	m_PostProcessManager.Entry("Normal", std::move(normal));
	
	std::unique_ptr<PostEffectBase> blur		= std::make_unique<BlurPostEffect>(shader_manager->GetVertexShader("2DVS"), shader_manager->GetPixelShader("BlurPS"));
	m_PostProcessManager.Entry("Blur", std::move(blur));

	std::unique_ptr<PostEffectBase> monochrome	= std::make_unique<MonochromePostEffect>(shader_manager->GetVertexShader("2DVS"), shader_manager->GetPixelShader("MonochromePS"));
	m_PostProcessManager.Entry("Monochrome", std::move(monochrome));

	std::unique_ptr<PostEffectBase> negaposi	= std::make_unique<NegaPosiPostEffect>(shader_manager->GetVertexShader("2DVS"), shader_manager->GetPixelShader("NegaPosiPS"));
	m_PostProcessManager.Entry("NegaPosi", std::move(negaposi));

	std::unique_ptr<PostEffectBase> sepia		= std::make_unique<SepiaPostEffect>(shader_manager->GetVertexShader("2DVS"), shader_manager->GetPixelShader("SepiaPS"));
	m_PostProcessManager.Entry("Sepia", std::move(sepia));	
	
	std::unique_ptr<PostEffectBase> outline		= std::make_unique<OutlinePostEffect>(shader_manager->GetVertexShader("2DVS"), shader_manager->GetPixelShader("OurlinePS"));
	m_PostProcessManager.Entry("Outline", std::move(outline));
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
	m_ModelManager.GetModel()->Render();
}