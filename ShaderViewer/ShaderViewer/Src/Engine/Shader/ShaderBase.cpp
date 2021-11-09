#include <stdio.h>
#include "ShaderBase.h"

// シェーダコンパイル周りの機能をインクルード
#include <d3dcompiler.h>
// シェーダコンパイル用の静的ライブラリをリンク
#pragma comment(lib, "d3dcompiler.lib")

bool ShaderBase::Create(ID3D11Device* device_, const char* fileName_)
{
	m_Size = LoadFile(fileName_);
	if (m_Size == 0)
	{
		return false;
	}

	return true;
}

int ShaderBase::LoadFile(const char* fileName_)
{
	FILE* fp = nullptr;
	// シェーダファイルの読み込み
	fopen_s(&fp, fileName_, "rb");

	if (fp == nullptr)
	{
		return 0;
	}

	// ファイルの終端に移動してサイズを取得
	fseek(fp, 0, SEEK_END);
	m_Size = ftell(fp);
	// ファイルの先頭に移動してデータを格納する
	fseek(fp, 0, SEEK_SET);
	m_Data = new char[m_Size];
	fread_s(m_Data, m_Size, m_Size, 1, fp);
	fclose(fp);

	return m_Size;
}
