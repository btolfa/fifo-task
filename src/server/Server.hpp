/**
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 20.03.16.
 */

#pragma once

#include "../session/SessionFactory.hpp"

namespace fifoserver {

class Server {
public:
    Server(boost::filesystem::path const& fifopath, SessionFactory& factory);

    void run();
private:
    boost::filesystem::path fifopath_;
    SessionFactory & factory_;
};

}


