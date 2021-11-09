#ifndef MODEL_H_
#define MODEL_H_

#include "../../Utility/Utility.h"
#include "../Graphics/GraphicsUtility.h"

/**
* @brief モデルデータの基底クラス
*/
class Model
{
public:
	/**
	* @brief コンストラクタ
	*/
	Model()
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~Model()
	{
		m_MeshList.clear();
		m_MeshList.shrink_to_fit();
	}
	
	/**
	* @fn std::vector<MeshData>* GetMeshData()
	* @brief モデルのデータを返す関数
	* @return std::vector<MeshData>* メッシュデータのポインタ
	*/
	std::vector<MeshData>* GetMeshData() { return &m_MeshList; }

protected:
	std::vector<MeshData> m_MeshList;	//! メッシュリスト
	
};

#endif