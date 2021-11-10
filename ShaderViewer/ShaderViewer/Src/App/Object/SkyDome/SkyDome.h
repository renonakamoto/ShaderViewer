#ifndef SKY_DOME_H_
#define SKY_DOME_H_

#include "../../ViewModel/ViewModel.h"

/**
* @brief スカイドームクラス
*/
class SkyDome
{
public:
	/**
	* @brief コンストラクタ
	*/
	SkyDome();

	/**
	* @brief デストラクタ
	*/
	~SkyDome()
	{}

	/**
	* @fn void Render()
	* @brief 描画関数
	*/
	void Render();

	/**
	* @fn ViewModel* GetModel()
	* @brief ビューモデル取得関数
	* @return ViewModel* ビューモデルのポインタ
	*/
	ViewModel* GetModel() { return &m_ViewModel; }

private:
	ViewModel m_ViewModel;	//! モデル情報
	ObjModel  m_Model;		//! モデルデータ
	
};

#endif