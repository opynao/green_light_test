#ifndef HTML_TAG_UTILS_H
#define HTML_TAG_UTILS_H

#include <unordered_map>
#include <string>
#include <future>
#include <vector>

using htmlTagCount_t = std::unordered_map<std::string, int>;
using tagsCount_t = std::vector<std::pair<std::string, int>>;

void countAndSortTags(const std::string &htmlContent, std::promise<tagsCount_t> &&resultPromise);
htmlTagCount_t countTags(const std::string &);

#endif // HTML_TAG_UTILS_H
