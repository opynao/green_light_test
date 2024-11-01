#include "FileUtils.h"

#include <fstream>
#include <iostream>

std::string readFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        return "";
    std::string htmlContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return htmlContent;
}
