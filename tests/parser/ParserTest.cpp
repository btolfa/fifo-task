#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/command/ParserImpl.hpp"

using ::testing::StrEq;

namespace {

class ParserTest : public ::testing::Test {
protected:
};

///
TEST_F(ParserTest, ShouldParseStringToCommand) {
    fifoserver::command::ParserImpl parser;
}

}