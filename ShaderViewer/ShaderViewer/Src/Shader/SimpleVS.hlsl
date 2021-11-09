/****************************************
           ���̓p�����[�^
****************************************/
struct VS_IN
{
    float4 pos         : POSITION0; // ���W
    float4 nor         : NORMAL0;   // �@��
    float2 texture_pos : TEXTURE0;  // �e�N�X�`�����W
};
 
/****************************************
           �o�̓p�����[�^
****************************************/
struct VS_OUT
{
    float4 pos             : SV_POSITION;       // ���W      
    float4 posw            : POSITION0;         // ���[���h��ԍ��W
    float3 norw            : NORMAL0;           // ���[���h��Ԗ@��
    float2 texture_pos     : TEXCOORD0;         // �e�N�X�`�����W
    float3 light           : LIGHT0;            // ���C�g�̈ʒu
    float3 eye_vec         : EYE0;              // �����x�N�g��
    float4 light_tex_coord : TEXCOORD1;         // �V���h�E�}�b�v�p�e�N�X�`�����W
    float4 light_view_pos  : LIGHT_VIEW_POS0;   // ���C�g�n�_����̒��_���W
};

/****************************************
          �萔�o�b�t�@
****************************************/
 
cbuffer ConstantBuffer : register(b0)
{
    float4x4 World;            //! ���[���h�s��
    float4x4 View;             //! �r���[�s��
    float4x4 Projection;       //! �v���W�F�N�V�����s��
    float4x4 LightView;        //! ���C�g���猩���r���[�s��
    float4x4 LightProjection;  //! ���C�g���猩���v���W�F�N�V�����s��
    float4x4 ClipUV;           //! UV�ϊ��p�s��
    float4   CameraPos;        //! �J�������W
    float4   Light;            //! ���C�g�̕���
    float4   MaterialAmbient;  //! �A���r�G���g��
    float4   MaterialDiffuse;  //! �f�B�q���[�Y��
    float4   MaterialSpecular; //! �X�y�L�����[��
};

/****************************************
            �G���g���[�֐�
****************************************/ 

VS_OUT vs_main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;
        
    // ���[�J�����W * ���[���h���W�ϊ��s��
    output.posw = mul(input.pos, World);
    // ���[���h���W * �r���[���W�ϊ��s��
    output.pos  = mul(output.posw, View);
    // �r���[���W * �v���W�F�N�V�������W�ϊ��s��
    output.pos  = mul(output.pos, Projection);
    // �@���x�N�g��
    output.norw = normalize(mul(input.nor, (float3x3) World));
    // �e�N�X�`�����W
    output.texture_pos = input.texture_pos;
    // �����x�N�g��
    output.eye_vec     = normalize(CameraPos - output.posw);
    // ���C�g�̕����x�N�g��
    output.light       = normalize(Light);
    
    // �V���h�E�}�b�v�p
    output.light_view_pos = mul(output.posw, LightView);
    output.light_view_pos = mul(output.light_view_pos, LightProjection);
    output.light_tex_coord = mul(output.light_view_pos, ClipUV);

    return output;
}