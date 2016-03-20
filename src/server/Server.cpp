/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#include "Server.hpp"
#include "../led/LedDriver.hpp"

namespace fifoserver {

Server::Server(fs::path const &fifopath)
    : fifopath_{fifopath} {

}

}