/****************************************
           ���̓p�����[�^
****************************************/

// PixelShader�ɑ����Ă���f�[�^�\��
struct PS_IN
{
    float4 pos         : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};

float BlurStrength : register(b0);

// �e�N�X�`�����
Texture2D SceneTexture : register(t0);
SamplerState Sampler   : register(s0);


/****************************************
            �G���g���[�֐�
****************************************/
// �G���g���[�|�C���g
float4 ps_main(PS_IN input) : SV_TARGET
{
    // �X�N���[���̉���
    float SCREEN_WIDTH = 1280.0;
    // �X�N���[���̏c��
    float SCREEN_HEIGHT = 720.0;
    // ���炷�s�N�Z����
    float OFFSET_PIXEL = BlurStrength;
    
    // �s�N�Z���̃I�t�Z�b�g�l���v�Z
    float offset_u = OFFSET_PIXEL / SCREEN_WIDTH;
    float offset_v = OFFSET_PIXEL / SCREEN_HEIGHT;
    
    // ��ƂȂ�e�N�Z�����T���v��
    float4 color = SceneTexture.Sample(Sampler, input.texture_pos);
    
    // �E�ɃI�t�Z�b�g�l�����炵���e�N�Z�����T���v��
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(offset_u, 0.0));
    // ���ɃI�t�Z�b�g�l�����炵���e�N�Z�����T���v��                                 
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(-offset_u, 0.0));
    // ���ɃI�t�Z�b�g�l�����炵���e�N�Z�����T���v��
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(0.0, offset_v));
    // ��ɃI�t�Z�b�g�l�����炵���e�N�Z�����T���v��                      
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(0.0, -offset_v));
    // �E���ɃI�t�Z�b�g�l�����炵���e�N�Z�����T���v��
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(offset_u, offset_v));
    // �E��ɃI�t�Z�b�g�l�����炵���e�N�Z�����T���v��                     
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(offset_u, -offset_v));
    // �����ɃI�t�Z�b�g�l�����炵���e�N�Z�����T���v��
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(-offset_u, offset_v));
    // ����ɃI�t�Z�b�g�l�����炵���e�N�Z�����T���v��
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(-offset_u, -offset_v));
    
    // �T���v�������F�̕��ς̂��v�Z
    color /= 9.0;
    
    // �o��
    return color;
}