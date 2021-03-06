#include "gtest/gtest.h"
#include "Parser.h"
#include "regexp.h"
#include <string>
#include <iostream>
using namespace std;

int test(string pattern, string case_str){
    regexp reg(pattern);
    return reg.accept(case_str);
}

TEST(MixedTest, ConcatTest){
    EXPECT_EQ(1, test("abc", "abc"));
}

TEST(MixedTest, UnionTest){
    EXPECT_EQ(1, test("a(b|c)", "ab"));
    EXPECT_EQ(1, test("abcd|efg", "abcd"));
    EXPECT_EQ(0, test("cd|e", "c"));
    EXPECT_EQ(1, test("abcd|efgh|hijk", "efgh"));
}

TEST(MixedTest, StarTest){
    EXPECT_EQ(1, test("ab*", "abbbb"));
    EXPECT_EQ(1, test("a?b*", ""));
    EXPECT_EQ(1, test("a?b*", "a"));
    EXPECT_EQ(1, test("a?b*", "bbb"));
    EXPECT_EQ(1, test("a?b*", "abbbb"));
    EXPECT_EQ(0, test("a?b*", "c"));
}

TEST(MixedTest, DotTest){
    EXPECT_EQ(1, test(".",  "a"));
    EXPECT_EQ(0, test(".", "aa"));
    EXPECT_EQ(1, test(".*", "asdsads"));
}

TEST(MixedTest, MixTest){
    EXPECT_EQ(1, test("ab(cd|e)fg", "abcdfg"));
    EXPECT_EQ(1, test("ab(cd|e)fg", "abefg"));
    EXPECT_EQ(0, test("ab((cd)|e)fg", "abcfg"));
    EXPECT_EQ(1, test("ab((cd)|e)*fg", "abcdcdcdfg"));
    EXPECT_EQ(1, test("ab((cd)|e)*fg", "abcdcdefg"));
    EXPECT_EQ(0, test("ab((cd)|e)*fg", "abcdcdcefg"));
    EXPECT_EQ(1, test("ab?((cd)|e)?fg*", "abfgggg"));
}
TEST(MixedTest, PlusTest){
    EXPECT_EQ(1, test("ab+", "ab"));
    EXPECT_EQ(0, test("ab+", "a"));
}

TEST(BracketTest, PositiveTest){
    EXPECT_EQ(1, test("a[abc]", "ab"));
    EXPECT_EQ(1, test("a[b|d]e", "a|e"));
}

TEST(BracketTest, NegativeTest){
    EXPECT_EQ(0, test("a[abc]", "ad"));
    EXPECT_EQ(0, test("[abc]", "d"));
}

TEST(BracketTest, ComplexTest){
    EXPECT_EQ(1, test("a[bc]*", "abbbc"));
    EXPECT_EQ(0, test("a[bc]+", "a"));
}
