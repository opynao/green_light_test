#include "HtmlTagUtils.h"

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <regex>

void sortTagsByCount(tagsCount_t &tags)
{
    std::ranges::sort(tags, [](const auto &a, const auto &b)
                      { return b.second < a.second; });
}

void countAndSortTags(const std::string &htmlContent, std::promise<tagsCount_t> &&resultPromise)
{
    const htmlTagCount_t &tagCounts = countTags(htmlContent);
    tagsCount_t tags(tagCounts.cbegin(), tagCounts.cend());
    sortTagsByCount(tags);
    resultPromise.set_value(tags);
}

htmlTagCount_t countTags(const std::string &htmlContent)
{
    htmlTagCount_t tagCounts;
    std::regex tagRegex("<\\s*([a-zA-Z0-9]+)([^>]*)(/?)>");
    std::smatch match;

    auto searchStart = htmlContent.cbegin();
    while (std::regex_search(searchStart, htmlContent.cend(), match, tagRegex))
    {
        std::string tagName = match[1].str();

        // Преобразование имени тега в нижний регистр
        std::transform(tagName.begin(), tagName.end(), tagName.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });

        tagCounts[tagName]++;
        searchStart = match.suffix().first;
    }

    return tagCounts;
}
