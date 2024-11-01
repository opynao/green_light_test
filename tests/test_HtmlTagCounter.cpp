#include "HtmlTagCounter.h"

#include <gtest/gtest.h>
#include <future>
#include <unordered_map>
#include <string>

TEST(HtmlTagCounterTest, CountAndSortTags)
{
    std::string htmlContent = "<html><body><div></div><div></div><p></p></body></html>";
    std::unordered_map<std::string, int> expected = {{"html", 1}, {"body", 1}, {"div", 2}, {"p", 1}};
    auto result = countAndSortTags(htmlContent);
    EXPECT_EQ(result, expected);
}

TEST(HtmlTagCounterTest, ProcessHtmlContent)
{
    std::string htmlContent = "<html><body><div></div><div></div><p></p></body></html>";
    std::unordered_map<std::string, int> expected = {{"html", 1}, {"body", 1}, {"div", 2}, {"p", 1}};

    std::promise<std::unordered_map<std::string, int>> resultPromise;
    std::future<std::unordered_map<std::string, int>> resultFuture = resultPromise.get_future();

    processHtmlContent(htmlContent, std::move(resultPromise));
    auto result = resultFuture.get();

    EXPECT_EQ(result, expected);
}

TEST(HtmlTagCounterTest, EmptyHtmlContent)
{
    std::string htmlContent = "";
    std::unordered_map<std::string, int> expected = {};
    auto result = countAndSortTags(htmlContent);
    EXPECT_EQ(result, expected);
}

TEST(HtmlTagCounterTest, NoTagsHtmlContent)
{
    std::string htmlContent = "This is a plain text without any HTML tags.";
    std::unordered_map<std::string, int> expected = {};
    auto result = countAndSortTags(htmlContent);
    EXPECT_EQ(result, expected);
}

TEST(HtmlTagCounterTest, NestedTagsHtmlContent)
{
    std::string htmlContent = "<div><span><a></a></span></div>";
    std::unordered_map<std::string, int> expected = {{"div", 1}, {"span", 1}, {"a", 1}};
    auto result = countAndSortTags(htmlContent);
    EXPECT_EQ(result, expected);
}

TEST(HtmlTagCounterTest, SelfClosingTagsHtmlContent)
{
    std::string htmlContent = "<div><img src='image.png'/><br/></div>";
    std::unordered_map<std::string, int> expected = {{"div", 1}, {"img", 1}, {"br", 1}};
    auto result = countAndSortTags(htmlContent);
    EXPECT_EQ(result, expected);
}
