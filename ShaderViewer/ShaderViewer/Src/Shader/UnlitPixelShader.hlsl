
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
Texture2D TextureDepth : register(t1);
SamplerState ShadowSampler : register(s1);

/****************************************
            �G���g���[�֐�
****************************************/
float4 ps_main(PS_IN input) : SV_Target
{
    float4 d = Texture.Sample(Sampler, input.texture_pos);
        
    // �f�B�t���[�Y�J���[
    float3 diffuse_color = d + MaterialDiffuse;
    
    // �X�N���[���̉���
    float SCREEN_WIDTH = 1280.0;
    // �X�N���[���̏c��
    float SCREEN_HEIGHT = 720.0;
    // ���炷�s�N�Z����
    float OFFSET_PIXEL = 1.0;
    
    // �e
    float2 sm_uv = input.light_tex_coord.xy / input.light_tex_coord.w;
    if (sm_uv.x >= 0.0 && sm_uv.x <= 1.0
        && sm_uv.y >= 0.0 && sm_uv.y <= 1.0)
    {
        // �V���h�E�A�N�l�΍�Ńo�C�A�X���|����
        float bias = 0.0003;
        
        // ����̃��C�g���猩���[�x�l���Z�o
        float z_light_view = input.light_view_pos.z;
        
        // �s�N�Z���̃I�t�Z�b�g�l���v�Z
        float offset_u = OFFSET_PIXEL / SCREEN_WIDTH;
        float offset_v = OFFSET_PIXEL / SCREEN_HEIGHT;
        
        // ��ƂȂ�e�N�Z���܂ދ߂��̃e�N�Z�����T���v�����O����
        float z_shadow_map_0 = TextureDepth.Sample(ShadowSampler, sm_uv).r;
        float z_shadow_map_1 = TextureDepth.Sample(ShadowSampler, sm_uv + float2(offset_u, 0.0)).r;
        float z_shadow_map_2 = TextureDepth.Sample(ShadowSampler, sm_uv + float2(offset_u, offset_v)).r;
        float z_shadow_map_3 = TextureDepth.Sample(ShadowSampler, sm_uv + float2(0.0, offset_v)).r;
        
        // �V���h�E�}�b�v�ɕۑ�����Ă���[�x�l���������ꍇ�A�e�ɂȂ�̂Ŏˉe���� 1 ���Z����        
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
        // �ˉe���̕��ς����߂� 0 �` 1 (0% �` 100%)�ɂȂ�
        shadow_rate /= 4.0;
        
        // ���`��ԂŎˉe���ɉ����ĐF�����炩�ɕω�������
        float3 shadow_color = diffuse_color / 3.0;
        diffuse_color = lerp(diffuse_color, shadow_color, shadow_rate);
    }
   
    // �o��
    return float4(diffuse_color, 1.0f);
}