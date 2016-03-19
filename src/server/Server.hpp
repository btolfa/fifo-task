/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#pragma once

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

namespace asio = boost::asio;
namespace fs = boost::filesystem;

namespace fifoserver {

class LedDriver;

class Server {
public:
    Server(fs::path const& fifopath, asio::io_service & io_service, LedDriver & led);
private:
    fs::path fifopath_;
    asio::io_service & io_service_;
    LedDriver & led_;
};

}