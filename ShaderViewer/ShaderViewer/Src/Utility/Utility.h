#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>
#include <vector>


/**
* @fn std::vector<std::string> Split(std::string str_, char del_)
* @brief 文字列を特定の文字で分割する関数
* @param[in] str_ 分割する文字列
* @param[in] del_ 分割する文字
* @return std::vector<std::string> 分割された文字列
*/
std::vector<std::string> Split(std::string str_, char del_);

/**
* @fn void Replace(char searchChar_, char replaceChar_, char* buffer_)
* @brief 文字列のなかにある特定の文字を特定の文字で置き換える関数
* @param[in] searchChar_ 置き換えたい文字
* @param[in] replaceChar_ 置き換える文字
* @param[out] buffer_ 文字列
*/
void Replace(char searchChar_, char replaceChar_, char* buffer_);

#endif