
/****************************************
           入力パラメータ
****************************************/

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 posw : POSITION0;
    float3 norw : NORMAL0;
    float2 texture_pos : TEXCOORD0;
    float3 light : LIGHT0;
    float3 eye_vec : EYE0;
    float4 light_tex_coord : TEXCOORD1;
    float4 light_view_pos : LIGHT_VIEW_POS0;
};

/****************************************
          定数バッファ
****************************************/
 
cbuffer ConstantBuffer : register(b0)
{
    float4x4 World; //! ワールド行列
    float4x4 View; //! ビュー行列
    float4x4 Projection; //! プロジェクション行列
    float4x4 LightView; //! ライトから見たビュー行列
    float4x4 LightProjection; //! ライトから見たプロジェクション行列
    float4x4 ClipUV; //! UV変換用行列
    float4 CameraPos; //! カメラ座標
    float4 Light; //! ライトの方向
    float4 MaterialAmbient; //! アンビエント光
    float4 MaterialDiffuse; //! ディヒューズ光
    float4 MaterialSpecular; //! スペキュラー光
};


/****************************************
          テクスチャ
****************************************/

Texture2D Texture : register(t0); // Textureをスロット0の0番目のテクスチャレジスタに設定
SamplerState Sampler : register(s0); // Samplerをスロット0の0番目のサンプラレジスタに設定
Texture2D RampTexture : register(t1);

/****************************************
          共通関数
****************************************/

float HalfLambert(float3 lig_dir, float3 normal)
{
    // 法線とライトのベクトルの内積を計算し0～1に補正する -> 反射率
    float ndl = saturate(dot(normal, lig_dir));
    // 0.0～1.0に1/2を乗算し1/2を加算することで0.5～1.0に値を補正する
    float half_ndl = ndl * 0.5 + 0.5;
    // 二乗することで、0.5～1.0の滑らかなカーブになる
    float square_ndl = half_ndl * half_ndl;
	
    return square_ndl;
}

/****************************************
            エントリー関数
****************************************/
float4 ps_main(PS_IN input) : SV_Target
{
    // ディフューズカラー
    float d = HalfLambert(input.light, input.norw);
    
    float3 color = RampTexture.Sample(Sampler, float2(d, d));

    // 出力
    return float4(color, 1.0);
}