/**
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 20.03.16.
 */

#include "Server.hpp"

#include <boost/filesystem/fstream.hpp>
#include <linux/limits.h>

namespace fs = boost::filesystem;

namespace fifoserver {

Server::Server(boost::filesystem::path const &fifopath, fifoserver::SessionFactory &factory)
: fifopath_{fifopath}, factory_{factory}
{
}

void Server::run() {
    bool is_quit = false;
    while (! is_quit) {
        // Блокируется, до тех пор пока не подключились с другой стороны
        fs::ifstream fifostream{fifopath_};

        for (std::string line; std::getline(fifostream, line, '\n');) {
            if (line == "quit") {
                is_quit = true;
                break;
            }
        }
    }
}


}

