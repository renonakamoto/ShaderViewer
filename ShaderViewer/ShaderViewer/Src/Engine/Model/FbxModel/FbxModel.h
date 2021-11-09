#ifndef FBX_MESH_H
#define FBX_MESH_H

#include <d3dx11.h>
#include <Windows.h>
#include <map>
#include <vector>
#include <fbxsdk.h>
#include "../../Graphics/DirectGraphics.h"
#include "../Model.h"


/**
* @brief ボーン情報を保持する構造体
*/
struct Bone
{
	char			  Name[64];		//! ボーン名
	DirectX::XMMATRIX Offset;		//! 初期姿勢行列
	DirectX::XMMATRIX Transform;	//! フレーム時姿勢行列
};

/**
* @brief モーション情報を保持するクラス
*/
struct Motion
{
	UINT FrameNum;								  //! フレーム数
	std::vector<DirectX::XMMATRIX> Key[BONE_MAX]; //! フレーム時姿勢行列
	
	Motion():
		FrameNum(0U)
	{}
};

/**
* @brief Fbxファイルを読み込むクラス
*/
class FbxModel : public Model
{
public:
	/**
	* @brief コンストラクタ
	*/
	FbxModel() :
		m_InputLayout(nullptr),
		m_BoneNum(0),
		m_StartFrame(0),
		m_Bone{ 0 }
	{}

	/**
	* @brief デストラクタ
	*/
	~FbxModel()
	{}

	/**
	* @fn bool LoadModel(const char*　fileName_)
	* @brief FbxFileを読み込む関数
	* @param[in] fileName_ ファイル名(パス付)
	* @return bool 成功したかどうかを真偽で返す
	* @details メッシュ、マテリアル、ボーンの情報を読み込む。モーション情報は読み込まない
	*/
	bool LoadModel(const char* fileName_);
	
	/**
	* @fn bool LoadMaterial(std::string keyword_, const char* fileName_)
	* @brief モーションを読み込む関数
	* @param[in] keyword_ モーションのハンドルとなるキーワード名
	* @param[in] fileName_ ファイル名(パス付)
	* @return bool 成功したかどうかを真偽で返す
	* @details ボーンの名前を検索して一致させて読み込むので、ボーン名が同じでないと読み込めない
	*/
	bool LoadMotion(std::string keyword_, const char* fileName_);

	/**
	* @fn bool AddMesh(const char* fileName_, DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_, const char* boneName_ = nullptr)
	* @brief メッシュを追加する関数
	* @param[in] fileName_ ファイル名(パス付)
	* @param[in] pos_ 座標
	* @param[in] boneName_ 影響を貰うボーンの名前
	* @return bool 成功したかどうかを真偽で返す
	* @details ボーン情報は読み込めない、ボーン名を指定することで、特定のボーンの影響を受けることができる
	*/
	bool AddMesh(const char* fileName_, DirectX::XMFLOAT3 pos_, const char* boneName_ = nullptr);

	/**
	* @fn void Render(DirectGraphics* graphics_, DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_)
	* @brief 描画関数
	* @param[in] graphics_ グラフィック
	* @param[in] pos_ 移動
	* @param[in] scale_ 拡縮
	* @param[in] degree_ 回転(度数)
	* @details ボーンのフレーム時行列、ワールド行列をシェーダに送る
	*/
	void Render(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_, std::string motionName_ = "", float frameNum_ = 0.f);

	/**
	* @fn const Motion* GetMotionData(std::string motionKeyword_)
	* @brief モーションデータ取得関数
	* @param[in] motionKeyword_ モーションに紐づけられているキーワード
	* @return const Motion* モーションのデータ
	*/
	const Motion* GetMotionData(std::string motionKeyword_) { return &m_Motion[motionKeyword_]; }

private:
	/**
	* @fn void LoadMaterial(FbxSurfaceMaterial* material_)
	* @brief マテリアル情報を読み込む関数
	* @param[in] material_ 
	*/
	void LoadMaterial(FbxSurfaceMaterial* material_);

	/**
	* @fn void LoadIndices(MeshData& meshData_, FbxMesh* mesh_)
	* @brief 頂点番号を読み込む作成関数
	* @param[out] meshData_ 取得した頂点番号を保存する変数
	* @param[in] mesh_ ノードから取得したメッシュデータ
	*/
	void LoadIndices(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void LoadVertices(MeshData& meshData_, FbxMesh* mesh_)
	* @brief 頂点座標を読み込む作成関数
	* @param[out] meshData_ 取得した頂点座標を保存する変数
	* @param[in] mesh_ ノードから取得したメッシュデータ
	*/
	void LoadVertices(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void LoadNormals(MeshData& meshData_, FbxMesh* mesh_)
	* @brief 法線を読み込む関数
	* @param[out] meshData_ 取得した法線を保存する変数
	* @param[in] mesh_ ノードから取得したメッシュデータ
	*/
	void LoadNormals(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void LoadVertexColors(MeshData& meshData_, FbxMesh* mesh_)
	* @brief 頂点カラーを読み込む作成関数
	* @param[out] meshData_ 取得した頂点カラーを保存する変数
	* @param[in] mesh_ ノードから取得したメッシュデータ
	*/
	void LoadVertexColors(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void LoadMaterialNames(MeshData& meshData_, FbxMesh* mesh_)
	* @brief マテリアル名を読み込む作成関数
	* @param[out] meshData_ 取得したマテリアル名を保存する変数
	* @param[in] mesh_ ノードから取得したメッシュデータ
	*/
	void LoadMaterialNames(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void LoadUV(MeshData& meshData_, FbxMesh* mesh_)
	* @brief テクスチャ座標を読み込む作成関数
	* @param[out] meshData_ 取得したテクスチャ座標を保存する変数
	* @param[in] mesh_ ノードから取得したメッシュデータ
	*/
	void LoadUV(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void CreateTangentAndBinormal(MeshData& meshData_)
	* @brief 接空間ベクトル作成関数
	* @param[inout] meshData_ メッシュデータ
	*/
	void CreateTangentAndBinormal(MeshData& meshData_);
	
	/**
	* @fn void LoadBones(MeshData& meshData_, FbxMesh* mesh_)
	* @brief テクスチャ座標を読み込む作成関数
	* @param[out] meshData_ 取得したテクスチャ座標を保存する変数
	* @param[in] mesh_ ノードから取得したメッシュデータ
	*/
	void LoadBones(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void LoadKeyFrame(std::string keyword_, int bone, FbxNode* boneNode_)
	* @brief ボーンのフレーム時行列を読み込む作成関数
	* @param[in] keyword_ モーション名
	* @param[in] bone_ ボーン番号
	* @param[in] boneNode_ ボーンノード
	*/
	void LoadKeyFrame(std::string keyword_, UINT bone_, FbxNode* boneNode_);

	/**
	* @fn bool LoadTexute(ID3D11Device* device_, FbxFileTexture* texture_, std::string& keyword_)
	* @brief テクスチャ読み込み関数
	* @param[in] device_ デバイス
	* @param[in] texture_ テクスチャ情報
	* @param[out] keyword_ 保存したテクスチャのキーワード
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool LoadTexute(ID3D11Device* device_, FbxFileTexture* texture_, std::string& keyword_);

	/**
	* @fn int FindBoone(const char* boneName_)
	* @brief ボーンを検索する関数
	* @param[in] boneName_ ボーンの名前
	* @return int 見つかった場合ボーンの配列番号を返す、見つからなかったら-1を返す
	*/
	int FindBoone(const char* boneName_);

	/**
	* @fn bool CreateVertexBuffer(ID3D11Device* device_)
	* @brief 頂点バッファの作成関数
	* @param[in] device_ デバイス
	* @return bool 成功したかどうかを真偽で返す
	* @details シェーダに送るための頂点バッファを作成する
	*/
	bool CreateVertexBuffer(ID3D11Device* device_);

	/**
	* @fn bool CreateIndexBuffer(ID3D11Device* device_)
	* @brief インデックスバッファの作成関数
	* @param[in] device_ デバイス
	* @return bool 成功したかどうかを真偽で返す
	* @details シェーダに送るためのインデックスバッファを作成する
	*/
	bool CreateIndexBuffer(ID3D11Device* device_);

	/**
	* @fn bool CreateInputLayout(ID3D11Device* device_, VertexShader* vertexShader_)
	* @brief 入力レイアウトの作成関数
	* @param[in] device_ デバイス
	* @param[in] vertexShader_ バーテックスシェーダ
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateInputLayout(ID3D11Device* device_, VertexShader* vertexShader_);

private:
	std::map<std::string, ObjMaterial>						m_Materials;		//! マテリアル
	std::map<std::string, ComPtr<ID3D11ShaderResourceView>> m_MaterialLinks;	//!	マテリアル名で紐づけるテクスチャ
	std::map<std::string, ComPtr<ID3D11ShaderResourceView>>	m_Textures;			//! テクスチャ
	std::map<std::string, Motion>							m_Motion;			//! モーション
	
	Bone  m_Bone[BONE_MAX];														//! ボーンの姿勢行列を保存する変数
	UINT  m_BoneNum;															//! ボーンの数
	int   m_StartFrame;															//! モーションの開始フレームを保存する変数

	ComPtr<ID3D11InputLayout> m_InputLayout;									//! 入力レイアウト
};

#endif