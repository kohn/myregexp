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

TEST(MixedTest, RegexpTest){
    EXPECT_EQ(1, test("abc", "abc"));
    EXPECT_EQ(1, test("a(b|c)", "ab"));
    EXPECT_EQ(1, test("ab*", "abbbb"));
    EXPECT_EQ(1, test("a?b*", ""));
    EXPECT_EQ(1, test("a?b*", "a"));
    EXPECT_EQ(1, test("a?b*", "bbb"));
    EXPECT_EQ(1, test("a?b*", "abbbb"));
    EXPECT_EQ(0, test("a?b*", "c"));
    EXPECT_EQ(1, test(".",  "a"));
    EXPECT_EQ(0, test(".", "aa"));
    EXPECT_EQ(1, test(".*", "asdsads"));
    EXPECT_EQ(1, test("ab((cd)|e)fg", "abcdfg"));
    EXPECT_EQ(1, test("ab((cd)|e)fg", "abefg"));
    EXPECT_EQ(0, test("ab((cd)|e)fg", "abcfg"));
    EXPECT_EQ(1, test("ab((cd)|e)*fg", "abcdcdcdfg"));
    EXPECT_EQ(1, test("ab((cd)|e)*fg", "abcdcdefg"));
    EXPECT_EQ(0, test("ab((cd)|e)*fg", "abcdcdcefg"));
    EXPECT_EQ(1, test("ab?((cd)|e)?fg*", "abfgggg"));
}

