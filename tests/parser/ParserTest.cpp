#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/command/ParserImpl.hpp"
#include "../../src/command/FailedCommand.hpp"
#include "../../src/command/GetLedState.hpp"
#include "../../src/command/GetLedColor.hpp"
#include "../../src/command/GetLedRate.hpp"
#include "../../src/command/SetLedState.hpp"
#include "../../src/command/SetLedColor.hpp"
#include "../../src/command/SetLedRate.hpp"

using ::testing::Pointee;
using ::testing::WhenDynamicCastTo;
using ::testing::Field;
using ::testing::Eq;

namespace {

namespace cmd = fifoserver::command;
using LedColor = ::fifoserver::LedColor;
using LedState = ::fifoserver::LedState;

class ParserTest : public ::testing::Test {
protected:
    fifoserver::command::ParserImpl parser;
};

TEST_F(ParserTest, ShouldParseInvalidCommand) {
    auto command = parser.parse("invalid-command on");
    ASSERT_TRUE(bool(command));
    EXPECT_THAT(*command, WhenDynamicCastTo<cmd::FailedCommand const&>(::testing::_));
}

TEST_F(ParserTest, ShouldParseGetCommands) {
    {
        auto command = parser.parse("get-led-state");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::GetLedState const&>(::testing::_));
    }

    {
        auto command = parser.parse("get-led-color");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::GetLedColor const&>(::testing::_));
    }

    {
        auto command = parser.parse("get-led-rate");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::GetLedRate const&>(::testing::_));
    }
}

TEST_F(ParserTest, ShouldParseSetState) {
    {
        auto command = parser.parse("set-led-state on");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::SetLedState const &>(
                Field(&cmd::SetLedState::state_, Eq(LedState::On))
        ));
    }

    {
        auto command = parser.parse("set-led-state off");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::SetLedState const &>(
                Field(&cmd::SetLedState::state_, Eq(LedState::Off))
        ));
    }

    {
        auto command = parser.parse("set-led-state invalid");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::FailedCommand const &>(::testing::_));
    }

    {
        auto command = parser.parse("set-led-state");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::FailedCommand const &>(::testing::_));
    }
}

TEST_F(ParserTest, ShouldParseSetColor) {
    {
        auto command = parser.parse("set-led-color red");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::SetLedColor const &>(
                Field(&cmd::SetLedColor::color_, Eq(LedColor::red))
        ));
    }

    {
        auto command = parser.parse("set-led-color green");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::SetLedColor const &>(
                Field(&cmd::SetLedColor::color_, Eq(LedColor::red))
        ));
    }

    {
        auto command = parser.parse("set-led-color blue");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::SetLedColor const &>(
                Field(&cmd::SetLedColor::color_, Eq(LedColor::red))
        ));
    }

    {
        auto command = parser.parse("set-led-color invalid");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::FailedCommand const &>(::testing::_));
    }

    {
        auto command = parser.parse("set-led-color");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::FailedCommand const &>(::testing::_));
    }
}

TEST_F(ParserTest, ShouldParseSetRate) {
    for (uint32_t rate = 0; rate <= 5; ++rate) {
        auto command = parser.parse(std::string("set-led-rate ") + std::to_string(rate));
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::SetLedRate const&>(
                Field(&cmd::SetLedRate::rate_, Eq(rate))
        ));
    }

    {
        auto command = parser.parse("set-led-rate -1");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::FailedCommand const&>(::testing::_));
    }

    {
        auto command = parser.parse("set-led-rate 100");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::FailedCommand const&>(::testing::_));
    }

    {
        auto command = parser.parse("set-led-rate invalid");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::FailedCommand const&>(::testing::_));
    }

    {
        auto command = parser.parse("set-led-rate");
        ASSERT_TRUE(bool(command));
        EXPECT_THAT(*command, WhenDynamicCastTo<cmd::FailedCommand const&>(::testing::_));
    }
}

}