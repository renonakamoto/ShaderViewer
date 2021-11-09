/****************************************
           入力パラメータ
****************************************/

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};


// 定数バッファ
float NegaRate : register(b0);


// テクスチャ情報
Texture2D SceneTexture : register(t0);
SamplerState Sampler : register(s0);


/****************************************
            エントリー関数
****************************************/
// エントリーポイント
float4 ps_main(PS_IN input) : SV_TARGET
{
    // サンプル
    float4 color = SceneTexture.Sample(Sampler, input.texture_pos);
    
    // カラーをネガポジ反転させる
    float3 nega_color;
    nega_color.r = 1.0 - color.r;
    nega_color.g = 1.0 - color.g;
    nega_color.b = 1.0 - color.b;
    
    color.xyz = lerp(color.xyz, nega_color, NegaRate);
    
    // 出力
    return color;
}