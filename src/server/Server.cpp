/**
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 20.03.16.
 */

#include "Server.hpp"

#include <boost/filesystem/fstream.hpp>
#include <linux/limits.h>
#include <sstream>

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
            } else {
                auto parameters = split(line);
                factory_.create_and_detach("/tmp/1", "/tmp/2");
            }
        }
    }
}

// TODO: Реальные пути могут содержать пробелы, нужно парсить пришедшие строки
// TODO: учитываю такую возможность. Наверняка есть готовая читалка строки из путей
std::vector<std::string> Server::split(const std::string &line) {
    using namespace std;
    istringstream iss{line};

    vector<string> results;
    results.reserve(2);

    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(results));
    return results;
}

}

