
/****************************************
           ���̓p�����[�^
****************************************/

struct PS_IN
{
    float4 pos   : SV_POSITION;
    float4 depth : POSITION0;
};

/****************************************
            �G���g���[�֐�
****************************************/

float4 ps_main(PS_IN input) : SV_Target
{
    return float4(input.pos.z, input.pos.z, input.pos.z, 1.0);
}