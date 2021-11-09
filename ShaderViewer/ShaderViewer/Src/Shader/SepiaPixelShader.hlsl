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
float SepiaRate : register(b0);


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
    
    // �J���[���Z�s�A���ɕω�������
    float y = 0.299 * color.r + 0.587 * color.b + 0.114 * color.b;
    float3 sepia_color;
    sepia_color.r = y * 0.9;
    sepia_color.g = y * 0.7;
    sepia_color.b = y * 0.4;
    
    color.xyz = lerp(color.xyz, sepia_color, SepiaRate);
    
    // �o��
    return color;
}