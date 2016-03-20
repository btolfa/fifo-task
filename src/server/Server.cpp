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
    // Пытаемся создать логгер, если уже существует, то берём из готовый
    try {
        lg_ = spdlog::stdout_logger_mt("server");
    } catch (spdlog::spdlog_ex const& exception) {
        lg_ = spdlog::get("server");
    }

}

void Server::run() {
    bool is_quit = false;
    while (! is_quit) {
        // Блокируется, до тех пор пока не подключились с другой стороны
        fs::ifstream fifostream{fifopath_};

        for (std::string line; std::getline(fifostream, line, '\n');) {
            if (line == "quit") {
                is_quit = true;
                lg_->info("Received quit request");
                break;
            } else {
                parse_line(line);
            }
        }
    }
}

void Server::parse_line(const std::string &line) const {
    auto parameters = split(line);
    if (parameters.size() == 2) {
                    lg_->info("Received connecting with input fifo - {} and output fifo - {}",
                              parameters[0], parameters[1]);
                    factory_.create_detached(parameters[0], parameters[1]);
                } else {
                    // Если параметров больше 2х, ничего не делаем
                    // Т.к. такое поведение не определено
                    lg_->warn("Received request with more then 2 parameters, ignoring: {}", line);
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