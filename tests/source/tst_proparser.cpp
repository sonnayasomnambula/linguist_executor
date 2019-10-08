#include <gtest/gtest.h>

#include "printto.h"
#include "proparser.h"

class ProParserTest : public ::testing::Test
{
public:
    static QStringList joinBackslashed(const QStringList& source) {
        return ProParser::joinBackslashed(source);
    }

    static QString trimAndRemoveComment(const QString& s) {
        return ProParser::trimAndRemoveComment(s);
    }
};


TEST_F(ProParserTest, trimAndRemoveComment)
{
    EXPECT_EQ("test", trimAndRemoveComment("test"));
    EXPECT_EQ("test", trimAndRemoveComment(" test"));
    EXPECT_EQ("test", trimAndRemoveComment("test "));
    EXPECT_EQ("test", trimAndRemoveComment(" test "));
    EXPECT_EQ("test", trimAndRemoveComment("   test # comment"));
    EXPECT_EQ("test", trimAndRemoveComment("\ttest # comment"));
    EXPECT_EQ("test", trimAndRemoveComment("test#"));
    EXPECT_EQ("", trimAndRemoveComment("#test"));
    EXPECT_EQ("", trimAndRemoveComment("#"));
    EXPECT_EQ("", trimAndRemoveComment(" #"));
    EXPECT_EQ("", trimAndRemoveComment("# "));
    EXPECT_EQ("", trimAndRemoveComment(" # "));
}

TEST_F(ProParserTest, joinBackslashed)
{
    const QStringList backslashed = {
        R"(First line)",
        R"( DEFINES += \)",
        R"(     ONE \)",
        R"(     TWO \)",
        R"()",
        R"( INCLUDES = one \)",
        R"(     two)",
        R"(Last line)"
    };

    const QStringList oneline = {
        R"(First line)",
        R"(DEFINES += ONE TWO)",
        R"(INCLUDES = one two)",
        R"(Last line)"
    };

    EXPECT_EQ(oneline, joinBackslashed(backslashed));
}

