#include "HtmlTagUtils.h"

#include <iostream>
#include <thread>
#include <future>
#include <fstream>

void printTagCounts(const tagsCount_t &sortedTags)
{
    std::cout << "HTML tags and their quantity in file sorted in descending order:\n";
    for (const auto &[tag, count] : sortedTags)
        std::cout << "<" << tag << "> - " << count << std::endl;
}

std::string readFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        return "";
    std::string htmlContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return htmlContent;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Specify the path to the HTML file as an argument." << std::endl;
        return 1;
    }

    const std::string htmlContent = readFile(argv[1]);
    if (htmlContent.empty())
    {
        std::cerr << "Failed to open the file or file content is empty." << std::endl;
        return 1;
    }

    std::promise<tagsCount_t> resultPromise;
    std::future<tagsCount_t> resultFuture = resultPromise.get_future();

    std::thread childThread(countAndSortTags, htmlContent, std::move(resultPromise));

    const tagsCount_t tagCounts = resultFuture.get();
    childThread.join();

    printTagCounts(tagCounts);

    return 0;
}
