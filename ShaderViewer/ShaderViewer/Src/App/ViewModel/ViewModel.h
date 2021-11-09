#ifndef VIEW_MODEL_H_
#define VIEW_MODEL_H_

#include "../../Utility/Vector/DXVector.h"
#include "../../Engine/Model/ObjModel/ObjModel.h"

/**
* @brief �r���[���f���̐�����s���N���X
*/
class ViewModel
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ViewModel() :
		ViewModel(
			DXVector3(0.f, 0.f, 0.f),
			DXVector3(1.f, 1.f, 1.f),
			DXVector3(0.f, 0.f, 0.f),
			nullptr)
	{}

	/**
	* @brief �R���X�g���N�^
	*/
	ViewModel(DXVector3 pos_, DXVector3 scale_, DXVector3 rot_, ObjModel* model_):
		m_Pos(pos_),
		m_Scale(scale_),
		m_Rot(rot_),
		m_ObjModel(model_),
		m_Rotate(false)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~ViewModel(){}
	
	/**
	* @fn void Update()
	* @brief �X�V�֐�
	* @details �r���[���f���̍X�V���s��
	*/
	void Update();

	/**
	* @fn void Render()
	* @brief �`��֐�
	*/
	void Render() const;

	/**
	* @fn void DrawGUI()
	* @brief GUI�`��
	* @details �g�����X�t�H�[������GUI��`�悷��
	*/
	void DrawGUI();

public:
	/**
	* @fn DXVector3 GetPos()
	* @brief ���W���擾�֐�
	* @return DXVector3 ���W���
	*/
	DXVector3 GetPos()   { return m_Pos; }

	/**
	* @fn DXVector3 GetScale()
	* @brief �X�P�[�����擾�֐�
	* @return DXVector3 �X�P�[�����
	*/
	DXVector3 GetScale() { return m_Scale; }

	/**
	* @fn DXVector3 GetPos()
	* @brief �p�x���擾�֐�
	* @return DXVector3 �p�x(�x���@)
	*/
	DXVector3 GetRot()   { return m_Rot;   }

	/**
	* @fn ObjModel* GetModel()
	* @brief ���f���f�[�^�擾�֐�
	* @return ObjModel* ���f���f�[�^�̃|�C���^
	*/
	ObjModel* GetModel() { return m_ObjModel; }


	/**
	* @fn void SetPos(DXVector3 pos_)
	* @brief ���W���Z�b�g�֐�
	* @param[in] pos_ ���W	  
	*/
	void SetPos(DXVector3 pos_)	 { m_Pos = pos_; }

	/**
	* @fn void SetScale(DXVector3 scale_)
	* @brief �X�P�[�����Z�b�g�֐�
	* @param[in] scale_ �X�P�[��
	*/
	void SetScale(DXVector3 scale_) { m_Scale = scale_; }

	/**
	* @fn void SetRot(DXVector3 rot_)
	* @brief �p�x���Z�b�g�֐�
	* @param[in] rot_ �p�x
	*/
	void SetRot(DXVector3 rot_)	 { m_Rot = rot_; }

	/**
	* @fn void SetModel(ObjModel* model_)
	* @brief ���f�����Z�b�g�֐�
	* @param[in] model_ ���f���f�[�^
	*/
	void SetModel(ObjModel* model_) { m_ObjModel = model_; }

private:
	DXVector3 m_Pos;		//! ���W
	DXVector3 m_Scale;		//! �X�P�[��
	DXVector3 m_Rot;		//! �p�x
	
	ObjModel* m_ObjModel;	//! ���f��

	bool m_Rotate;			//! ��]�����邩�ǂ���
};

#endif