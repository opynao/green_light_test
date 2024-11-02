#include "HtmlTagUtils.h"

#include <gtest/gtest.h>

TEST(HtmlTagCounterTest, EmptyHtmlContent)
{
    const std::string htmlContent = "";
    const htmlTagCount_t expected = {};
    const auto &result = countTags(htmlContent);
    EXPECT_EQ(result, expected);
}

TEST(HtmlTagCounterTest, SingleTag)
{
    std::string htmlContent = "<div></div>";
    htmlTagCount_t result = countTags(htmlContent);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result["div"], 1);
}

TEST(HtmlTagCounterTest, MultipleSameTags)
{
    std::string htmlContent = "<div></div><div></div>";
    htmlTagCount_t result = countTags(htmlContent);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result["div"], 2);
}

TEST(HtmlTagCounterTest, MultipleDifferentTags)
{
    std::string htmlContent = "<div></div><p></p><span></span>";
    htmlTagCount_t result = countTags(htmlContent);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result["div"], 1);
    EXPECT_EQ(result["p"], 1);
    EXPECT_EQ(result["span"], 1);
}

TEST(HtmlTagCounterTest, NoTagsHtmlContent)
{
    const std::string htmlContent = "This is a plain text without any HTML tags.";
    const htmlTagCount_t expected = {};
    const auto &result = countTags(htmlContent);
    EXPECT_EQ(result, expected);
}

TEST(HtmlTagCounterTest, NestedTagsHtmlContent)
{
    const std::string htmlContent = "<div><span><a></a></span></div>";
    const htmlTagCount_t expected = {{"div", 1}, {"span", 1}, {"a", 1}};
    const auto &result = countTags(htmlContent);
    EXPECT_EQ(result, expected);
}

TEST(HtmlTagCounterTest, SelfClosingTags)
{
    const std::string htmlContent = "<div><img src='image.png'/><br/></div>";
    const htmlTagCount_t expected = {{"div", 1}, {"img", 1}, {"br", 1}};
    const auto &result = countTags(htmlContent);
    EXPECT_EQ(result, expected);
}

TEST(HtmlTagCounterTest, TagsWithAttributes)
{
    std::string htmlContent = "<div class=\"container\"></div><p id=\"para\"></p>";
    htmlTagCount_t result = countTags(htmlContent);
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result["div"], 1);
    EXPECT_EQ(result["p"], 1);
}

TEST(HtmlTagCounterTest, TagsWithMixedCase)
{
    std::string htmlContent = "<DIV></DIV><div></div>";
    htmlTagCount_t result = countTags(htmlContent);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result["DIV"], 0);
    EXPECT_EQ(result["div"], 2);
}