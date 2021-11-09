/****************************************
           入力パラメータ
****************************************/
struct VS_IN
{
    float4 pos         : POSITION0; // 座標
    float4 nor         : NORMAL0;   // 法線
    float2 texture_pos : TEXTURE0;  // テクスチャ座標
};
 
/****************************************
           出力パラメータ
****************************************/
struct VS_OUT
{
    float4 pos             : SV_POSITION;       // 座標      
    float4 posw            : POSITION0;         // ワールド空間座標
    float3 norw            : NORMAL0;           // ワールド空間法線
    float2 texture_pos     : TEXCOORD0;         // テクスチャ座標
    float3 light           : LIGHT0;            // ライトの位置
    float3 eye_vec         : EYE0;              // 視線ベクトル
    float4 light_tex_coord : TEXCOORD1;         // シャドウマップ用テクスチャ座標
    float4 light_view_pos  : LIGHT_VIEW_POS0;   // ライト始点からの頂点座標
};

/****************************************
          定数バッファ
****************************************/
 
cbuffer ConstantBuffer : register(b0)
{
    float4x4 World;            //! ワールド行列
    float4x4 View;             //! ビュー行列
    float4x4 Projection;       //! プロジェクション行列
    float4x4 LightView;        //! ライトから見たビュー行列
    float4x4 LightProjection;  //! ライトから見たプロジェクション行列
    float4x4 ClipUV;           //! UV変換用行列
    float4   CameraPos;        //! カメラ座標
    float4   Light;            //! ライトの方向
    float4   MaterialAmbient;  //! アンビエント光
    float4   MaterialDiffuse;  //! ディヒューズ光
    float4   MaterialSpecular; //! スペキュラー光
};

/****************************************
            エントリー関数
****************************************/ 

VS_OUT vs_main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;
        
    // ローカル座標 * ワールド座標変換行列
    output.posw = mul(input.pos, World);
    // ワールド座標 * ビュー座標変換行列
    output.pos  = mul(output.posw, View);
    // ビュー座標 * プロジェクション座標変換行列
    output.pos  = mul(output.pos, Projection);
    // 法線ベクトル
    output.norw = normalize(mul(input.nor, (float3x3) World));
    // テクスチャ座標
    output.texture_pos = input.texture_pos;
    // 視線ベクトル
    output.eye_vec     = normalize(CameraPos - output.posw);
    // ライトの方向ベクトル
    output.light       = normalize(Light);
    
    // シャドウマップ用
    output.light_view_pos = mul(output.posw, LightView);
    output.light_view_pos = mul(output.light_view_pos, LightProjection);
    output.light_tex_coord = mul(output.light_view_pos, ClipUV);

    return output;
}