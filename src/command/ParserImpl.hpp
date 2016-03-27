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
};

}
}