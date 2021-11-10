#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../Utility/Vector/DXVector.h"

/**
* @brief レンダーターゲットの種類
*/
class Camera
{
public:
	/**
	* @brief コンストラクタ
	*/
	Camera() :
		Camera({ 0.f, 2.f, -12.f }, { 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f })
	{}

	/**
	* @brief コンストラクタ
	*/
	Camera(DXVector3 pos_, DXVector3 forcus_, DXVector3 up_) :
		m_Pos(pos_),
		m_FocusPos(forcus_),
		m_Up(up_)
	{}

	/**
	* @brief デストラクタ
	*/
	~Camera() {}

	/**
	* @fn void Update()
	* @brief 更新関数
	* @details View行列Projection行列の作成を行い定数バッファに設定する
	*/
	void Update();

private:
	DXVector3 m_Pos;		//! 座標
	DXVector3 m_FocusPos;	//! 注視点
	DXVector3 m_Up;			//! 上向きベクトル

};

#endif