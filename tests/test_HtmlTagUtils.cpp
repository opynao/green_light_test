#include "HtmlTagUtils.h"

#include <gtest/gtest.h>

TEST(HtmlTagCounterTest, EmptyHtmlContent)
{
    const std::string htmlContent = "";
    const htmlTagCount_t expected{};
    EXPECT_EQ(countTags(htmlContent), expected);
}

TEST(HtmlTagCounterTest, SingleTag)
{
    const std::string htmlContent = "<div></div>";
    const htmlTagCount_t expected = {{"div", 1}};
    EXPECT_EQ(countTags(htmlContent), expected);
}

TEST(HtmlTagCounterTest, MultipleSameTags)
{
    const std::string htmlContent = "<div></div><div></div>";
    const htmlTagCount_t expected = {{"div", 2}};
    EXPECT_EQ(countTags(htmlContent), expected);
}

TEST(HtmlTagCounterTest, MultipleDifferentTags)
{
    const std::string htmlContent = "<div></div><p></p><span></span>";
    const htmlTagCount_t expected = {{"div", 1}, {"p", 1}, {"span", 1}};
    EXPECT_EQ(countTags(htmlContent), expected);
}

TEST(HtmlTagCounterTest, NoTagsHtmlContent)
{
    const std::string htmlContent = "This is a plain text without any HTML tags.";
    const htmlTagCount_t expected{};
    EXPECT_EQ(countTags(htmlContent), expected);
}

TEST(HtmlTagCounterTest, NestedTagsHtmlContent)
{
    const std::string htmlContent = "<div><span><a></a></span></div>";
    const htmlTagCount_t expected = {{"div", 1}, {"span", 1}, {"a", 1}};
    EXPECT_EQ(countTags(htmlContent), expected);
}

TEST(HtmlTagCounterTest, SelfClosingTags)
{
    const std::string htmlContent = "<div><img src='image.png'/><br/></div>";
    const htmlTagCount_t expected = {{"div", 1}, {"img", 1}, {"br", 1}};
    EXPECT_EQ(countTags(htmlContent), expected);
}

TEST(HtmlTagCounterTest, TagsWithAttributes)
{
    const std::string htmlContent = "<div class=\"container\"></div><p id=\"para\"></p>";
    const htmlTagCount_t expected = {{"div", 1}, {"p", 1}};
    EXPECT_EQ(countTags(htmlContent), expected);
}

TEST(HtmlTagCounterTest, TagsWithMixedCase)
{
    const std::string htmlContent = "<DIV></DIV><div></div>";
    const htmlTagCount_t expected = {{"div", 2}};
    EXPECT_EQ(countTags(htmlContent), expected);
}