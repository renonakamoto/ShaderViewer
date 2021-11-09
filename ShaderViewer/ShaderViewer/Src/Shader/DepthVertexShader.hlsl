/****************************************
           ���̓p�����[�^
****************************************/

// VertexShader�ɑ����Ă���f�[�^�\��
struct VS_IN
{
    float4 pos         : POSITION0;
    float4 nor         : NORMAL0;
    float2 texture_pos : TEXTURE0;
};

/****************************************
           �o�̓p�����[�^
****************************************/

// VertexShader����o�͂���f�[�^�\��
struct VS_OUT
{
    float4 pos   : SV_POSITION;
    float4 depth : POSITION0;
};

/****************************************
          �萔�o�b�t�@
****************************************/

cbuffer ConstantBuffer : register(b0)
{
    float4x4 World; //! ���[���h�s��
    float4x4 View; //! �r���[�s��
    float4x4 Projection; //! �v���W�F�N�V�����s��
    float4x4 LightView; //! ���C�g���猩���r���[�s��
    float4x4 LightProjection; //! ���C�g���猩���v���W�F�N�V�����s��
    float4x4 ClipUV; //! UV�ϊ��p�s��
    float4 CameraPos; //! �J�������W
    float4 Light; //! ���C�g�̕���
    float4 MaterialAmbient; //! �A���r�G���g��
    float4 MaterialDiffuse; //! �f�B�q���[�Y��
    float4 MaterialSpecular; //! �X�y�L�����[��
};

/****************************************
            �G���g���[�֐�
****************************************/

VS_OUT vs_main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

    output.pos = mul(input.pos,  World);
    output.pos = mul(output.pos, LightView);
    output.pos = mul(output.pos, LightProjection);
    output.depth = output.pos;

    return output;
}