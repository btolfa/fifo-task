/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 20.03.16
 * 
 */

#pragma once

#include <memory>
#include "Command.hpp"

namespace fifoserver {
namespace command {

class Parser {
public:
    virtual ~Parser() = default;

    virtual std::unique_ptr<Command> parse() = 0;
};

}
}

