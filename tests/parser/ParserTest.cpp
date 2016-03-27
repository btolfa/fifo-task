#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/command/ParserImpl.hpp"
#include "../../src/command/FailedCommand.hpp"

using ::testing::Pointee;
using ::testing::WhenDynamicCastTo;
using ::testing::Field;

namespace {

namespace cmd = fifoserver::command;

class ParserTest : public ::testing::Test {
protected:
};

///
TEST_F(ParserTest, ShouldParseInvalidCommand) {
    fifoserver::command::ParserImpl parser;
    auto command = parser.parse("invalid-command on");
    ASSERT_TRUE(bool(command));
    EXPECT_THAT(command.get(), WhenDynamicCastTo<cmd::FailedCommand*>(::testing::_));
}

}