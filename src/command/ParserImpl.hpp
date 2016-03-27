/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 27.03.16
 * 
 */

#pragma once

#include "Parser.hpp"

namespace fifoserver {
namespace command {

class ParserImpl : public Parser {
public:
    virtual std::unique_ptr<Command> parse(std::string const &string) const override final;
private:
    std::unique_ptr<Command> parse_set_state(std::string const& line) const;
    std::unique_ptr<Command> parse_set_rate(std::string const& line) const;
    std::unique_ptr<Command> parse_set_color(std::string const& line) const;
};

}
}