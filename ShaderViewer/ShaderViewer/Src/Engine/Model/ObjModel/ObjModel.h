#ifndef OBJ_MODEL_H_
#define OBJ_MODEL_H_

#include <d3d11.h>
#include <vector>
#include <map>
#include "../../Graphics/DirectGraphics.h"
#include "../../Graphics/GraphicsUtility.h"
#include "../Model.h"

/**
* @brief オブジェファイルの読み込み描画を行うクラス
*/
class ObjModel : public Model
{
public:
	/**
	* @brief コンストラクタ
	*/
	ObjModel() :
		m_InputLayout(nullptr)	
	{}

	/**
	* @brief デストラクタ
	*/
	~ObjModel()
	{}

	/**
	* @fn bool Load(const char* fileName_)
	* @brief モデル読み込み関数
	* @param[in] fileName_ ファイルパス
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool Load(const char* fileName_);

	/**
	* @fn void Render(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree)
	* @brief 描画関数
	* @param[in] pos_ 座標
	* @param[in] scale_ 拡縮
	* @param[out] degree 回転(度数)
	*/
	void Render(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree);

private:
	/**
	* @fn void ParseVertex(std::vector<DirectX::XMFLOAT3>& data_, char* buff_)
	* @brief Objファイルの頂点のデータを解析する関数
	* @param[out] data_ 頂点データを格納する変数
	* @param[in] buff_ Objファイルで取得した頂点データの1行
	*/
	void ParseVertex(std::vector<DirectX::XMFLOAT3>& data_, char* buff_);

	/**
	* @fn void ParseFKeywordTag(std::vector<DirectX::XMFLOAT3>& data_, char* buff_)
	* @brief Objファイルの面のデータを解析する関数
	* @param[out] meshData_ 面の頂点データを格納する変数
	* @param[in] vertices_ 頂点座標リスト
	* @param[in] textures_ テクスチャ座標リスト
	* @param[in] normals_ 法線ベクトルリスト
	* @param[in] buffer_ Objファイルで取得した面データの1行
	*/
	void ParseFKeywordTag(MeshData& meshData_, std::vector<DirectX::XMFLOAT3>& vertices_, std::vector<DirectX::XMFLOAT3>& textures_, std::vector<DirectX::XMFLOAT3>& normals_, char* buffer_);

	/**
	* @fn void ParseSlashKeywordTag(int* list_, char* buffer_)
	* @brief 面データの[/]を区切ってint型に変換し返す関数
	* @param[out] list_ /で区切ったint変数
	* @param[in] buffer_ /で区切る文字列
	*/
	void ParseSlashKeywordTag(int* list_, char* buffer_);

	/**
	* @fn bool LoadMaterialFile(const char* fileName_)
	* @brief モデル読み込み関数
	* @param[in] fileList_ マテリアルリスト
	* @param[in] filePath_ マテリアルが保存されているフォルダのパス
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool LoadMaterialFile(std::vector<std::string> fileList_, std::string filePath_);

	/**
	* @fn bool LoadTexture(std::string keyWord_, std::string fileName_, ID3D11Device* device_)
	* @brief テクスチャ読み込み関数
	* @param[in] keyWord_ テクスチャに紐づける
	* @param[in] fileName_ ファイルパス
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool LoadTexture(std::string keyWord_, std::string fileName_);

	/**
	* @fn bool CreateVertexBuffer()
	* @brief 頂点バッファ作成関数
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateVertexBuffer();
	
	/**
	* @fn bool CreateIndexBuffer()
	* @brief インデックスバッファ作成関数
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateIndexBuffer();
	
	/**
	* @fn bool CreateInputLayout(VertexShader* vertexShader_)
	* @brief 入力レイアウト作成関数
	* @param[in] vertexShader_ バーテックスシェーダー
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateInputLayout(VertexShader* vertexShader_);

private:
	ComPtr<ID3D11InputLayout>								m_InputLayout;	//! 入力レイアウト
	std::map <std::string, ObjMaterial>						m_Materials;	//! マテリアル
	std::map<std::string, ComPtr<ID3D11ShaderResourceView>> m_Textures;		//! テクスチャ
};

#endif