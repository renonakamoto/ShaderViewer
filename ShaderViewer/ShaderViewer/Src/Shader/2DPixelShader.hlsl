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
Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);


/****************************************
            エントリー関数
****************************************/
// エントリーポイント
float4 ps_main(PS_IN input) : SV_TARGET
{
    // クセルをサンプル
    float4 color = Texture.Sample(Sampler, input.texture_pos);

    // 出力
    return color;
}