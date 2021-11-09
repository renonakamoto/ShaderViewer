
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
Texture2D TextureDepth : register(t1);
SamplerState ShadowSampler : register(s1);

/****************************************
            エントリー関数
****************************************/
float4 ps_main(PS_IN input) : SV_Target
{
    float4 d = Texture.Sample(Sampler, input.texture_pos);
        
    // ディフューズカラー
    float3 diffuse_color = d + MaterialDiffuse;
    
    // スクリーンの横幅
    float SCREEN_WIDTH = 1280.0;
    // スクリーンの縦幅
    float SCREEN_HEIGHT = 720.0;
    // ずらすピクセル数
    float OFFSET_PIXEL = 1.0;
    
    // 影
    float2 sm_uv = input.light_tex_coord.xy / input.light_tex_coord.w;
    if (sm_uv.x >= 0.0 && sm_uv.x <= 1.0
        && sm_uv.y >= 0.0 && sm_uv.y <= 1.0)
    {
        // シャドウアクネ対策でバイアスを掛ける
        float bias = 0.0003;
        
        // 今回のライトから見た深度値を算出
        float z_light_view = input.light_view_pos.z;
        
        // ピクセルのオフセット値を計算
        float offset_u = OFFSET_PIXEL / SCREEN_WIDTH;
        float offset_v = OFFSET_PIXEL / SCREEN_HEIGHT;
        
        // 基準となるテクセル含む近くのテクセルをサンプリングする
        float z_shadow_map_0 = TextureDepth.Sample(ShadowSampler, sm_uv).r;
        float z_shadow_map_1 = TextureDepth.Sample(ShadowSampler, sm_uv + float2(offset_u, 0.0)).r;
        float z_shadow_map_2 = TextureDepth.Sample(ShadowSampler, sm_uv + float2(offset_u, offset_v)).r;
        float z_shadow_map_3 = TextureDepth.Sample(ShadowSampler, sm_uv + float2(0.0, offset_v)).r;
        
        // シャドウマップに保存されている深度値よりも長い場合、影になるので射影率を 1 加算する        
        float shadow_rate = 0.0;
        if (z_light_view > z_shadow_map_0 + bias)
        {
            shadow_rate += 1.0;
        }
        if (z_light_view > z_shadow_map_1 + bias)
        {
            shadow_rate += 1.0;
        }
        if (z_light_view > z_shadow_map_2 + bias)
        {
            shadow_rate += 1.0;
        }
        if (z_light_view > z_shadow_map_3 + bias)
        {
            shadow_rate += 1.0;
        }
        // 射影率の平均を求める 0 ～ 1 (0% ～ 100%)になる
        shadow_rate /= 4.0;
        
        // 線形補間で射影率に応じて色を滑らかに変化させる
        float3 shadow_color = diffuse_color / 3.0;
        diffuse_color = lerp(diffuse_color, shadow_color, shadow_rate);
    }
   
    // 出力
    return float4(diffuse_color, 1.0f);
}