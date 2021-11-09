/****************************************
           ���̓p�����[�^
****************************************/

// PixelShader�ɑ����Ă���f�[�^�\��
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};


// �萔�o�b�t�@
float NegaRate : register(b0);


// �e�N�X�`�����
Texture2D SceneTexture : register(t0);
SamplerState Sampler : register(s0);


/****************************************
            �G���g���[�֐�
****************************************/
// �G���g���[�|�C���g
float4 ps_main(PS_IN input) : SV_TARGET
{
    // �T���v��
    float4 color = SceneTexture.Sample(Sampler, input.texture_pos);
    
    // �J���[���l�K�|�W���]������
    float3 nega_color;
    nega_color.r = 1.0 - color.r;
    nega_color.g = 1.0 - color.g;
    nega_color.b = 1.0 - color.b;
    
    color.xyz = lerp(color.xyz, nega_color, NegaRate);
    
    // �o��
    return color;
}