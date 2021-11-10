#include "Config.h"
#include "../Utility/Utility.h"
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
	
	while (fgets(line_buf, line_buf_len, fp) != nullptr)
	{
		// [#]なら無視
		if (line_buf[0] == '#') continue;

		Replace('\n', '\0', line_buf);

		std::vector<std::string> split_str = Split(line_buf, ' ');

		if (split_str[0] == "") continue;
		// パラメータの位置までポインタを移動
		char* point = strchr(line_buf, '=')+2;


		// 各パラメータを取得していく
		if (split_str[0] == "CameraFov")
		{
			m_CameraFov = static_cast<float>(atof(point));
		}
		else if (split_str[0] == "CameraNear")
		{
			m_CameraNear = static_cast<float>(atof(point));
		}
		else if (split_str[0] == "CameraFar")
		{
			m_CameraFar = static_cast<float>(atof(point));
		}
		else if (split_str[0] == "GuiWidth")
		{
			m_GuiWidth = static_cast<float>(atof(point));
		}
		else if (split_str[0] == "GuiHeight")
		{
			m_GuiHeight = static_cast<float>(atof(point));
		}
		else if (split_str[0] == "LightPos")
		{
			split_str = Split(point, ' ');
			m_LightPos.x = static_cast<float>(atof(split_str[0].c_str()));
			m_LightPos.y = static_cast<float>(atof(split_str[1].c_str()));
			m_LightPos.z = static_cast<float>(atof(split_str[2].c_str()));
		}
	}


	// ファイルを閉じる
	fclose(fp);
}