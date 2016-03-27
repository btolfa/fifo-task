/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 20.03.16
 * 
 */

#pragma once

#include "SessionFactory.hpp"
#include "../command/Parser.hpp"

namespace fifoserver {

class SessionFactoryImpl : public SessionFactory {
public:
    SessionFactoryImpl(command::Parser & parser, LedDriver & ledDriver);
    virtual void create_detached(boost::filesystem::path const &input, boost::filesystem::path const &output) override;
private:
    command::Parser & parser_;
    LedDriver & ledDriver_;
};

}


