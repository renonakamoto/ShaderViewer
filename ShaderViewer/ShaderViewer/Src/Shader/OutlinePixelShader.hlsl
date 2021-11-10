/****************************************
           入力パラメータ
****************************************/

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};

float3 Color : register(b0);

// テクスチャ情報
Texture2D SceneTexture : register(t0);
SamplerState Sampler : register(s0);
Texture2D DepthTexture: register(t1);

/****************************************
            エントリー関数
****************************************/
// エントリーポイント
float4 ps_main(PS_IN input) : SV_TARGET
{
    // スクリーンの横幅
    float SCREEN_WIDTH = 1280.0;
    // スクリーンの縦幅
    float SCREEN_HEIGHT = 720.0;
    // ずらすピクセル数
    float OFFSET_PIXEL = 1;
    
    // ピクセルのオフセット値を計算
    float offset_u = OFFSET_PIXEL / SCREEN_WIDTH;
    float offset_v = OFFSET_PIXEL / SCREEN_HEIGHT;
    
    // 基準となるテクセルをサンプル
    float4 color = SceneTexture.Sample(Sampler, input.texture_pos);
    
    float depth = DepthTexture.Sample(Sampler, input.texture_pos).r;
    
    float offset_depth = 0.0;
    // 右にオフセット値分ずらしたテクセルをサンプル
    offset_depth += DepthTexture.Sample(Sampler, input.texture_pos + float2(offset_u, 0.0));
    // 左にオフセット値分ずらしたテクセルをサンプル                                 
    offset_depth += DepthTexture.Sample(Sampler, input.texture_pos + float2(-offset_u, 0.0));
    // 下にオフセット値分ずらしたテクセルをサンプル
    offset_depth += DepthTexture.Sample(Sampler, input.texture_pos + float2(0.0, offset_v));
    // 上にオフセット値分ずらしたテクセルをサンプル                      
    offset_depth += DepthTexture.Sample(Sampler, input.texture_pos + float2(0.0, -offset_v));
    // 右下にオフセット値分ずらしたテクセルをサンプル
    offset_depth += DepthTexture.Sample(Sampler, input.texture_pos + float2(offset_u, offset_v));
    // 右上にオフセット値分ずらしたテクセルをサンプル                     
    offset_depth += DepthTexture.Sample(Sampler, input.texture_pos + float2(offset_u, -offset_v));
    // 左下にオフセット値分ずらしたテクセルをサンプル
    offset_depth += DepthTexture.Sample(Sampler, input.texture_pos + float2(-offset_u, offset_v));
    // 左上にオフセット値分ずらしたテクセルをサンプル
    offset_depth += DepthTexture.Sample(Sampler, input.texture_pos + float2(-offset_u, -offset_v));
    
    // 平均を求める
    offset_depth /= 8.0;
    
    // 深度値の差が大きければラインの色にする
    if (abs(depth - offset_depth) > 0.00005)
    {
        color.xyz = Color;
    }
    
    // 出力
    return color;
}