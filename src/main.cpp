#include "HtmlTagUtils.h"
#include "FileUtils.h"

#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Specify the path to the HTML file as an argument." << std::endl;
        return 1;
    }

    std::string htmlContent = readFile(argv[1]);
    if (htmlContent.empty())
    {
        std::cerr << "Failed to open the file or file content is empty." << std::endl;
        return 1;
    }

    std::promise<tagCounts_t> resultPromise;
    std::future<tagCounts_t> resultFuture = resultPromise.get_future();

    std::thread childThread(processHtmlContent, htmlContent, std::move(resultPromise));

    const tagCounts_t tagCounts = resultFuture.get();
    childThread.join();

    printTagCounts(tagCounts);

    return 0;
}
