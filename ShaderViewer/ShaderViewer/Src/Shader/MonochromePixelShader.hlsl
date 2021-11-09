/****************************************
           ���̓p�����[�^
****************************************/

// PixelShader�ɑ����Ă���f�[�^�\��
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};

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
    
    // �J���[�����m�N��������
    float y = 0.299 * color.r + 0.587 * color.b + 0.114 * color.b;
    color.r = y;
    color.g = y;
    color.b = y;
    
    // �o��
    return color;
}