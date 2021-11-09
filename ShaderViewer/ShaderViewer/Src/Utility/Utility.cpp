#include "Utility.h"

std::vector<std::string> Split(std::string str_, char del_)
{
    std::vector<std::string> ret;

    std::string tmp;

    for (size_t i = 0; i < str_.size(); ++i) {

        if (str_[i] == del_) {
            ret.push_back(tmp);
            tmp.clear();
        }
        else {
            tmp.push_back(str_[i]);
        }
    }

    ret.push_back(tmp);

    return ret;
}

void Replace(char searchChar_, char replaceChar_, char* buffer_)
{
    int len = strlen(buffer_);

    for (int i = 0; i < len; ++i)
    {
        if (buffer_[i] == searchChar_)
        {
            buffer_[i] = replaceChar_;
        }
    }
}
