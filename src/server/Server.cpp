/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#include "Server.hpp"
#include "../led/LedDriver.hpp"

namespace fifoserver {

Server::Server(fs::path const &fifopath, asio::io_service &io_service, LedDriver & led)
    : fifopath_{fifopath}, io_service_{io_service}, led_{led} {

}

}