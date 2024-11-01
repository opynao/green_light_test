#include "TagStatistics.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void sortTagsByCount(std::vector<std::pair<std::string, int>> &tags)
{
    std::sort(tags.begin(), tags.end(), [](const auto &a, const auto &b)
              { return b.second < a.second; });
}

void printTagCounts(const std::vector<std::pair<std::string, int>> &sortedTags)
{
    std::cout << "HTML теги и их количество:\n";
    for (const auto &tag : sortedTags)
    {
        std::cout << "<" << tag.first << "> - " << tag.second << std::endl;
    }
}
