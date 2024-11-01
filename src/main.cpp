#include "HtmlTagCounter.h"
#include "FileUtils.h"
#include "TagStatistics.h"

#include <iostream>
#include <vector>
#include <thread>
#include <future>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Укажите путь к файлу HTML в качестве аргумента." << std::endl;
        return 1;
    }

    std::string htmlContent = readFile(argv[1]);
    if (htmlContent.empty())
    {
        std::cerr << "Не удалось открыть файл: " << argv[1] << std::endl;
        return 1;
    }

    std::promise<std::unordered_map<std::string, int>> resultPromise;
    std::future<std::unordered_map<std::string, int>> resultFuture = resultPromise.get_future();

    std::thread childThread(processHtmlContent, htmlContent, std::move(resultPromise));

    std::unordered_map<std::string, int> tagCounts = resultFuture.get();
    childThread.join();

    std::vector<std::pair<std::string, int>> sortedTags(tagCounts.begin(), tagCounts.end());
    sortTagsByCount(sortedTags);
    printTagCounts(sortedTags);

    return 0;
}
