#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::StrEq;

#include <boost/make_unique.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <thread>

#include "../../src/command/Parser.hpp"
#include "../led/MockLedDriver.hpp"
#include "../../src/session/Session.hpp"

namespace fs = boost::filesystem;

namespace {

class CommandOk : public fifoserver::command::Command {
public:
    virtual std::string execute(fifoserver::LedDriver &ledDriver) const override {
        return "OK";
    }
};

class MockParser : public fifoserver::command::Parser {
public:
    MOCK_METHOD1(parse_tp, void(std::string const &));

    std::unique_ptr<fifoserver::command::Command> parse(std::string const & line) override final {
        parse_tp(line);
        // because std::make_unique only in c++14
        return boost::make_unique<CommandOk>();
    }
};

class SessionTest : public ::testing::Test {
public:
    SessionTest() {
        mkfifo(input.c_str(), 0666);
        mkfifo(output.c_str(), 0666);
    }

    ~SessionTest() {
        fs::remove(input);
        fs::remove(output);
    }
protected:
    fs::path input {"/tmp/input_fifo"};
    fs::path output {"/tmp/output_fifo"};
    MockParser parser;
    MockLedDriver ledDriver;
};

///
TEST_F(SessionTest, ShouldReadCommandFromInputAndWriteResponseToOutput) {
    fifoserver::Session session{input, output, parser, ledDriver};

    std::thread client([this]{
        // Пишем запрос
        {
            fs::ofstream ofstream{input};
            ofstream << "nothing" << std::endl;
        }

        std::string response;
        // Читаем ответ
        {
            fs::ifstream ifstream{output};
            ifstream >> response;
        }
        EXPECT_THAT(response, StrEq("OK"));
    });

    EXPECT_CALL(parser, parse_tp(StrEq("nothing")));
    session.run();
    client.join();
}

}