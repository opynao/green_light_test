#include "HtmlTagCounter.h"

#include <regex>

std::unordered_map<std::string, int> countAndSortTags(const std::string &htmlContent)
{
    std::unordered_map<std::string, int> tagCounts;
    std::regex tagRegex("<\\s*([a-zA-Z0-9]+)([^>]*)(/?)>");
    std::smatch match;

    auto searchStart = htmlContent.cbegin();
    while (std::regex_search(searchStart, htmlContent.cend(), match, tagRegex))
    {
        tagCounts[match[1]]++;
        searchStart = match.suffix().first;
    }

    return tagCounts;
}

void processHtmlContent(const std::string &htmlContent, std::promise<std::unordered_map<std::string, int>> resultPromise)
{
    auto tagCounts = countAndSortTags(htmlContent);
    resultPromise.set_value(tagCounts);
}
