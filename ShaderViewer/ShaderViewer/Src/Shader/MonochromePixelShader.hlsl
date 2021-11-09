/****************************************
           入力パラメータ
****************************************/

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};

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
    
    // カラーをモノクロ化する
    float y = 0.299 * color.r + 0.587 * color.b + 0.114 * color.b;
    color.r = y;
    color.g = y;
    color.b = y;
    
    // 出力
    return color;
}