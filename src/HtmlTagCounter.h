#ifndef HTMLTAGCOUNTER_H
#define HTMLTAGCOUNTER_H

#include <string>
#include <map>
#include <future>
#include <unordered_map>

std::unordered_map<std::string, int> countAndSortTags(const std::string &htmlContent);
void processHtmlContent(const std::string &htmlContent, std::promise<std::unordered_map<std::string, int>> resultPromise);

#endif // HTMLTAGCOUNTER_H
