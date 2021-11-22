#ifndef SHADER_MANAGER_H_
#define SHADER_MANAGER_H_

#include <unordered_map>
#include <string>
#include <memory>
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"

enum class KindShader
{
	VS,	//! �o�[�e�b�N�X�V�F�[�_�[
	PS,	//! �s�N�Z���V�F�[�_
	GS,	//! �W�I���g���[�V�F�[�_�[
};

/**
* @brief �V�F�[�_�[���Ǘ�����N���X
*/
class ShaderManager
{
public:
	/**
	* @fn static ShaderManager* GetInstance()
	* @brief �C���X�^���X��Ԃ��֐�
	* @return ShaderManager* �C���X�^���X�̃|�C���^
	*/
	static ShaderManager* GetInstance()
	{
		static ShaderManager instance;
		return &instance;
	}

	bool Load(const char* fileName_, std::string keyWord_, KindShader kindShader_);

	inline VertexShader* GetVertexShader(std::string keyWord_) 
	{
		if (m_VertexShaders.find(keyWord_) == m_VertexShaders.end()) {
			return nullptr;
		}
		return m_VertexShaders[keyWord_].get();
	}
	
	inline PixelShader*  GetPixelShader(std::string keyWord_)
	{
		if (m_PixelShaders.find(keyWord_) == m_PixelShaders.end()) {
			return nullptr;
		}
		return m_PixelShaders[keyWord_].get();
	}


private:
	/**
	* @brief �R���X�g���N�^
	*/
	ShaderManager() {}

	/**
	* @brief �f�X�g���N�^
	*/
	~ShaderManager() {}

private:
	std::unique_ptr<VertexShader> LoadVS(const char* fileName_);
	std::unique_ptr<PixelShader>  LoadPS(const char* fileName_);
	std::unique_ptr<GeometryShader>  LoadGS(const char* fileName_);

private:
	std::unordered_map<std::string, std::unique_ptr<VertexShader>>	  m_VertexShaders;		//! ���_�V�F�[�_�[
	std::unordered_map<std::string, std::unique_ptr<PixelShader>>	  m_PixelShaders;		//! �s�N�Z���V�F�[�_�[
	std::unordered_map<std::string, std::unique_ptr<GeometryShader>>  m_GeometryShaders;	//! �W�I���g���[�V�F�[�_�[
	
};

#endif