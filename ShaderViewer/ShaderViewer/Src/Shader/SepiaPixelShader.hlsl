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
float SepiaRate : register(b0);


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
    
    // カラーをセピア調に変化させる
    float y = 0.299 * color.r + 0.587 * color.b + 0.114 * color.b;
    float3 sepia_color;
    sepia_color.r = y * 0.9;
    sepia_color.g = y * 0.7;
    sepia_color.b = y * 0.4;
    
    color.xyz = lerp(color.xyz, sepia_color, SepiaRate);
    
    // 出力
    return color;
}