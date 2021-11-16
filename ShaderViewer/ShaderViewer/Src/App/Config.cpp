#include "Config.h"
#include "../Utility/Utility.h"
#include <unordered_map>
#include <cstdio>
#include <sstream>

float ConfigParameter::m_CameraFov;
float ConfigParameter::m_CameraNear;
float ConfigParameter::m_CameraFar;
float ConfigParameter::m_GuiWidth;
float ConfigParameter::m_GuiHeight;
DXVector3 ConfigParameter::m_LightPos;

void ConfigParameter::Load()
{
	// ファイルを開く
	FILE* fp;
	fopen_s(&fp, "Assets/Config/InitData.txt", "r");

	if (!fp) return;

	const int line_buf_len = 1024;
	char line_buf[line_buf_len];

	// 各パラメータのキーとデータを紐づける
	std::unordered_map<std::string, float*> param_map;
	param_map["CameraFov"]  = &m_CameraFov;
	param_map["CameraNear"] = &m_CameraNear;
	param_map["CameraFar"]  = &m_CameraFar;
	param_map["GuiWidth"]   = &m_GuiWidth;
	param_map["GuiHeight"]  = &m_GuiHeight;
	
	// 一行ずつ解析していく
	while (fgets(line_buf, line_buf_len, fp) != nullptr)
	{
		// [#]なら無視
		if (line_buf[0] == '#') continue;

		Replace('\n', '\0', line_buf);
		
		std::vector<std::string> split_str = Split(line_buf, ' ');

		if (split_str[0] == "") continue;
		
		// パラメータのポインタ位置を保存
		char* param_point = strchr(line_buf, '=')+2;

		if (split_str[0] == "LightPos")
		{
			split_str = Split(param_point, ' ');
			m_LightPos.x = static_cast<float>(atof(split_str[0].c_str()));
			m_LightPos.y = static_cast<float>(atof(split_str[1].c_str()));
			m_LightPos.z = static_cast<float>(atof(split_str[2].c_str()));
		}
		else
		{
			if (param_map.find(split_str[0]) == param_map.end()) {
				continue;
			}

			*param_map[split_str[0]] = static_cast<float>(atof(param_point));
		}
	}


	// ファイルを閉じる
	fclose(fp);
}