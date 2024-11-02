#include "HtmlTagUtils.h"

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <regex>

void processHtmlContent(const std::string &htmlContent, std::promise<tagCounts_t> resultPromise)
{
    const htmlTagCount_t &tagCounts = countTags(htmlContent);
    tagCounts_t tags(tagCounts.cbegin(), tagCounts.cend());
    sortTagsByCount(tags);
    resultPromise.set_value(tags);
}

void sortTagsByCount(tagCounts_t &tags)
{
    std::sort(tags.begin(), tags.end(), [](const auto &a, const auto &b)
              { return b.second < a.second; });
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

void printTagCounts(const tagCounts_t &sortedTags)
{
    std::cout << "HTML tags and their quantity in file sorted in descending order:\n";
    for (const auto &tag : sortedTags)
        std::cout << "<" << tag.first << "> - " << tag.second << std::endl;
}
