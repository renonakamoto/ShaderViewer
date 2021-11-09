#ifndef ViewModelManager_H_
#define ViewModelManager_H_

#include <vector>
#include <memory>
#include "ViewModel.h"

/**
* @brief ビューモデルの管理を行うクラス
*/
class ViewModelManager
{
public:
	/**
	* @brief コンストラクタ
	*/
	ViewModelManager():
		m_Model(nullptr),
		m_CurrentModelID(0)
	{
		m_Model = std::make_unique<ViewModel>();
	}
	
	/**
	* @brief デストラクタ
	*/
	~ViewModelManager()
	{}
	
	/**
	* @fn void Update()
	* @brief 更新関数
	*/
	void Update();

	/**
	* @fn void Render()
	* @brief 描画関数
	*/
	void Render();

	/**
	* @fn void Update()
	* @brief GUI描画関数
	*/
	void DrawGUI();

	/**
	* @fn bool CreateModel(const char* fileName, const char* displayName_)
	* @brief モデル作成関数
	* @param[in] fileName	　モデルデータのファイル名(Objファイル, パス付き)
	* @param[in] displayName_ ディスプレイに表示させる時の名前
	* @return bool 成功したかどうか
	* @details モデルの読み込みとビューモデル作成を行う
	*/
	bool CreateModel(const char* fileName, const char* displayName_);

	/**
	* @fn ViewModel* GetModel()
	* @brief 選択されているモデルデータを取得する関数
	* @return ViewModel* ビューモデルのポインタ
	*/
	ViewModel* GetModel() { return m_Model.get(); }

private:
	std::unique_ptr<ViewModel>				m_Model;			//! ビューモデル
	std::vector<std::unique_ptr<ObjModel>>  m_ObjModels;		//! 3Dモデル用
	std::vector<const char*>		        m_ModelsNameList;	//! モデルのディスプレイ名リスト
	int m_CurrentModelID;										//! 現在選択されてるモデルのID

};

#endif