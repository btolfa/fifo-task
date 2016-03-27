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
    MOCK_CONST_METHOD1(parse_tp, void(std::string const &));

    std::unique_ptr<fifoserver::command::Command> parse(std::string const & line) const override final {
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

/// Пишем один запрос и читаем один ответ
TEST_F(SessionTest, ShouldReadOneCommandFromInputAndWriteResponseToOutput) {
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

/// Пишем несколько запросов сразу и читаем все ответы
TEST_F(SessionTest, ShouldReadSeveralCommandsFromInputAndWriteResponsesToOutput) {
    fifoserver::Session session{input, output, parser, ledDriver};

    std::thread client([this]{
        // Пишем запрос
        {
            fs::ofstream ofstream{input};
            ofstream << "first\n" << "second \n" << "third 3" << std::endl;
        }

        std::vector<std::string> responses;
        responses.reserve(3);
        // Читаем ответ
        {
            fs::ifstream ifstream{output};

            std::copy(std::istream_iterator<std::string>(ifstream),
                      std::istream_iterator<std::string>(),
                      std::back_inserter(responses));
        }
        EXPECT_EQ(responses.size(), 3);
        EXPECT_THAT(responses, Each(StrEq("OK")));
    });

    EXPECT_CALL(parser, parse_tp(::testing::_)).Times(3);
    session.run();
    client.join();
}

}