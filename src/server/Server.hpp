/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#pragma once

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace fifoserver {

class Server {
public:
    Server(fs::path const& fifopath);
private:
    fs::path fifopath_;
};

}