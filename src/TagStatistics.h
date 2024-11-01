#ifndef TAG_STATISTICS_H
#define TAG_STATISTICS_H

#include <vector>
#include <string>
#include <utility>

void sortTagsByCount(std::vector<std::pair<std::string, int>> &tags);
void printTagCounts(const std::vector<std::pair<std::string, int>> &sortedTags);

#endif // TAG_STATISTICS_H
