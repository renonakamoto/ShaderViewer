﻿#include "Camera.h"
#include "../../Engine/Engine.h"
#include "../../App/Config.h"

void Camera::Update()
{
	// カメラ座標の設定
	ConstantBuffer* cb = GRAPHICS->GetConstantBufferData();
	cb->CameraPos = DirectX::XMFLOAT4(m_Pos.x, m_Pos.y, m_Pos.z, 1.0f);

	// View行列の設定
	DirectX::XMVECTOR pos   = DirectX::XMVectorSet(m_Pos.x, m_Pos.y, m_Pos.z, 0.0f);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet(m_FocusPos.x, m_FocusPos.y, m_FocusPos.z, 0.0f);
	DirectX::XMVECTOR up	= DirectX::XMVectorSet(m_Up.x, m_Up.y, m_Up.z, 0.0f);
	DirectX::XMMATRIX view_matrix = DirectX::XMMatrixLookAtLH(pos, focus, up);
	
	DirectX::XMStoreFloat4x4(&cb->View, DirectX::XMMatrixTranspose(view_matrix));

	// Projection行列の設定
	float fov = DirectX::XMConvertToRadians(ConfigParameter::m_CameraFov);
	float aspect = static_cast<float>(WINDOW->GetClientWidth()) / static_cast<float>(WINDOW->GetClientHeight());
	float near_z = ConfigParameter::m_CameraNear;
	float far_z  = ConfigParameter::m_CameraFar;
	DirectX::XMMATRIX proj_matrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, near_z, far_z);

	DirectX::XMStoreFloat4x4(&cb->Projection, DirectX::XMMatrixTranspose(proj_matrix));
}