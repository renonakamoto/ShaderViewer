#ifndef GRAPHICS_UTILITY_H_
#define GRAPHICS_UTILITY_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <wrl.h>

using namespace Microsoft::WRL;

static const int BONE_MAX = 255;

/**
* @brief 通常のコンスタントバッファ
*/
struct ConstantBuffer
{
    DirectX::XMFLOAT4X4 World;              //! ワールド行列
    DirectX::XMFLOAT4X4 View;               //! ビュー行列
    DirectX::XMFLOAT4X4 Projection;         //! プロジェクション行列
    DirectX::XMFLOAT4X4 LightView;          //! ライト行列
    DirectX::XMFLOAT4X4 LightProjection;    //! ライトプロジェクション行列
    DirectX::XMFLOAT4X4 ClipUV;             //! UV変換用行列
    DirectX::XMFLOAT4   CameraPos;          //! カメラ座標
    DirectX::XMFLOAT4   Light;              //! ライトの方向ベクトル
    DirectX::XMFLOAT4   MaterialAmbient;    //! アンビエント光
    DirectX::XMFLOAT4   MaterialDiffuse;    //! ディヒューズ光
    DirectX::XMFLOAT4   MaterialSpecular;   //! スペキュラー光
    
    /**
    * @brief コンストラクタ
    */
    ConstantBuffer()
    {
        ZeroMemory(this, sizeof(ConstantBuffer));
    }
};

/**
* @brief スキンメッシュ用のボーンコンスタントバッファ
*/
struct ConstBoneBuffer
{
    DirectX::XMMATRIX Bone[BONE_MAX];  //! ボーンの姿勢行列

    /**
    * @brief コンストラクタ
    */
    ConstBoneBuffer()
    {
        ZeroMemory(this, sizeof(ConstBoneBuffer));
    }
};

/**
* @brief 2D描画用のコンスタントバッファ
*/
struct ConstantBuffer2D
{
    DirectX::XMMATRIX World;        //! ワールド行列
    DirectX::XMMATRIX Projection;   //! プロジェクション行列

    /**
    * @brief コンストラクタ
    */
    ConstantBuffer2D()
    {
        ZeroMemory(this, sizeof(ConstantBuffer2D));
    }
};

/**
* @brief 2D描画用の頂点データ
*/
struct Vertex2D {
    DirectX::XMFLOAT3 Pos;          //! 頂点座標
    DirectX::XMFLOAT2 TexturePos;   //! テクスチャ座標

    /**
    * @brief コンストラクタ
    */
    Vertex2D() :
        Vertex2D({ 0.f,0.f,0.f }, { 0.f,0.f })
    {}
    
    /**
    * @brief コンストラクタ
    * @param[in] pos_ 頂点座標
    * @param[in] texPos_ テクスチャ座標
    */
    Vertex2D(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT2 texPos_):
        Pos(pos_),
        TexturePos(texPos_)
    {}
};

/**
* @brief 3D用の頂点データ
*/
struct CVertex {
    DirectX::XMFLOAT3 Pos;          //! 頂点座標
    DirectX::XMFLOAT3 Normal;       //! 法線ベクトル
    DirectX::XMFLOAT2 TexturePos;   //! テクスチャ座標

    /**
    * @brief コンストラクタ
    */
    CVertex()
    {
        ZeroMemory(this, sizeof(CVertex));
    }
};

/**
* @brief 3D用の頂点データ
*/
struct SkinCVertex {
    DirectX::XMFLOAT3 Pos;          //! 頂点座標
    DirectX::XMFLOAT3 Normal;       //! 法線ベクトル
    DirectX::XMFLOAT4 Color;        //! 頂点カラー
    DirectX::XMFLOAT2 TexturePos;   //! テクスチャ座標

    UINT              Index[4];     //! ボーンのインデックス番号
    float             Weight[4];    //! ボーンの影響度

    DirectX::XMFLOAT3 Tangent;      //! 頂点座標
    DirectX::XMFLOAT3 Binormal;     //! 頂点座標

    /**
    * @brief コンストラクタ
    */
    SkinCVertex()
    {
        ZeroMemory(this, sizeof(SkinCVertex));
    }
};

/**
* @brief 3D用のマテリアルデータ
*/
struct ObjMaterial
{
    float       Ambient[4];        //! アンビエント光
    float       Diffuse[4];        //! ディヒューズ光
    float       Specular[4];       //! スペキュラー光
    std::string TextureKeyWord;    //! テクスチャキーワード
    std::string TextureName;       //! テクスチャのパス

    /**
    * @brief コンストラクタ
    */
    ObjMaterial() :
        Ambient { 0.0f, 0.0f ,0.0f ,1.0f },
        Diffuse { 0.0f, 0.0f ,0.0f ,1.0f },
        Specular{ 0.0f, 0.0f ,0.0f ,1.0f }
    {}
};

/**
* @brief 3Dモデルのメッシュデータ
*/
struct MeshData
{
    ComPtr<ID3D11Buffer> VertexBuffer;  //! バーテックスバッファ(シェーダーに送る用)
    ComPtr<ID3D11Buffer> IndexBuffer;   //! インデックスバッファ(シェーダーに送る用)
    std::vector<CVertex> Vertices;      //! バーテックスバッファ
    std::vector<UINT>	 Indices;       //! インデックスバッファ
    std::string			 MaterialName;  //! マテリアル名

    /**
    * @brief コンストラクタ
    */
    MeshData() :
        VertexBuffer(nullptr),
        IndexBuffer(nullptr)
    {
    }

    /**
    * @brief デストラクタ
    */
    ~MeshData()
    {}
};

/**
* @brief テクスチャ情報構造体
*/
struct TextureData
{
    ComPtr<ID3D11Buffer>             VertexBuffer; //! 頂点バッファ
    ComPtr<ID3D11Buffer>             IndexBuffer;  //! インデックスバッファ
    ComPtr<ID3D11ShaderResourceView> Texture;      //! テクスチャデータ
    UINT                             Width;        //! 横幅
    UINT                             Height;       //! 縦幅

    /**
    * @brief コンストラクタ
    */
    TextureData()
    {
        ZeroMemory(this, sizeof(TextureData));
    }

    /**
    * @brief デストラクタ
    */
    ~TextureData()
    {}
};

#endif