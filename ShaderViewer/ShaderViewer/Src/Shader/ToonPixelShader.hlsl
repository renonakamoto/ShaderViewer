
/****************************************
           ���̓p�����[�^
****************************************/

// PixelShader�ɑ����Ă���f�[�^�\��
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
          �e�N�X�`��
****************************************/

Texture2D Texture : register(t0); // Texture���X���b�g0��0�Ԗڂ̃e�N�X�`�����W�X�^�ɐݒ�
SamplerState Sampler : register(s0); // Sampler���X���b�g0��0�Ԗڂ̃T���v�����W�X�^�ɐݒ�
Texture2D RampTexture : register(t1);

/****************************************
          ���ʊ֐�
****************************************/

float HalfLambert(float3 lig_dir, float3 normal)
{
    // �@���ƃ��C�g�̃x�N�g���̓��ς��v�Z��0�`1�ɕ␳���� -> ���˗�
    float ndl = saturate(dot(normal, lig_dir));
    // 0.0�`1.0��1/2����Z��1/2�����Z���邱�Ƃ�0.5�`1.0�ɒl��␳����
    float half_ndl = ndl * 0.5 + 0.5;
    // ��悷�邱�ƂŁA0.5�`1.0�̊��炩�ȃJ�[�u�ɂȂ�
    float square_ndl = half_ndl * half_ndl;
	
    return square_ndl;
}

/****************************************
            �G���g���[�֐�
****************************************/
float4 ps_main(PS_IN input) : SV_Target
{
    // �f�B�t���[�Y�J���[
    float d = HalfLambert(input.light, input.norw);
    
    float3 color = RampTexture.Sample(Sampler, float2(d, d));

    // �o��
    return float4(color, 1.0);
}