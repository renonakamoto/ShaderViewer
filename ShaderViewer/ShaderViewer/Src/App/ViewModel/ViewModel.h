#ifndef VIEW_MODEL_H_
#define VIEW_MODEL_H_

#include "../../Utility/Vector/DXVector.h"
#include "../../Engine/Model/ObjModel/ObjModel.h"

/**
* @brief ビューモデルの制御を行うクラス
*/
class ViewModel
{
public:
	/**
	* @brief コンストラクタ
	*/
	ViewModel() :
		ViewModel(
			DXVector3(0.f, 0.f, 0.f),
			DXVector3(1.f, 1.f, 1.f),
			DXVector3(0.f, 0.f, 0.f),
			nullptr)
	{}

	/**
	* @brief コンストラクタ
	*/
	ViewModel(DXVector3 pos_, DXVector3 scale_, DXVector3 rot_, ObjModel* model_):
		m_Pos(pos_),
		m_Scale(scale_),
		m_Rot(rot_),
		m_ObjModel(model_),
		m_Rotate(false)
	{}

	/**
	* @brief デストラクタ
	*/
	~ViewModel(){}
	
	/**
	* @fn void Update()
	* @brief 更新関数
	* @details ビューモデルの更新を行う
	*/
	void Update();

	/**
	* @fn void Render()
	* @brief 描画関数
	*/
	void Render() const;

	/**
	* @fn void DrawGUI()
	* @brief GUI描画
	* @details トランスフォーム情報のGUIを描画する
	*/
	void DrawGUI();

public:
	/**
	* @fn DXVector3 GetPos()
	* @brief 座標情報取得関数
	* @return DXVector3 座標情報
	*/
	DXVector3 GetPos()   { return m_Pos; }

	/**
	* @fn DXVector3 GetScale()
	* @brief スケール情報取得関数
	* @return DXVector3 スケール情報
	*/
	DXVector3 GetScale() { return m_Scale; }

	/**
	* @fn DXVector3 GetPos()
	* @brief 角度情報取得関数
	* @return DXVector3 角度(度数法)
	*/
	DXVector3 GetRot()   { return m_Rot;   }

	/**
	* @fn ObjModel* GetModel()
	* @brief モデルデータ取得関数
	* @return ObjModel* モデルデータのポインタ
	*/
	ObjModel* GetModel() { return m_ObjModel; }


	/**
	* @fn void SetPos(DXVector3 pos_)
	* @brief 座標情報セット関数
	* @param[in] pos_ 座標	  
	*/
	void SetPos(DXVector3 pos_)	 { m_Pos = pos_; }

	/**
	* @fn void SetScale(DXVector3 scale_)
	* @brief スケール情報セット関数
	* @param[in] scale_ スケール
	*/
	void SetScale(DXVector3 scale_) { m_Scale = scale_; }

	/**
	* @fn void SetRot(DXVector3 rot_)
	* @brief 角度情報セット関数
	* @param[in] rot_ 角度
	*/
	void SetRot(DXVector3 rot_)	 { m_Rot = rot_; }

	/**
	* @fn void SetModel(ObjModel* model_)
	* @brief モデル情報セット関数
	* @param[in] model_ モデルデータ
	*/
	void SetModel(ObjModel* model_) { m_ObjModel = model_; }

private:
	DXVector3 m_Pos;		//! 座標
	DXVector3 m_Scale;		//! スケール
	DXVector3 m_Rot;		//! 角度
	
	ObjModel* m_ObjModel;	//! モデル

	bool m_Rotate;			//! 回転させるかどうか
};

#endif