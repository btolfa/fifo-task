/**
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 19.03.16.
 */

#include <cstdlib>

#include <boost/filesystem.hpp>
#include <spdlog/spdlog.h>
#include <cxxopts.hpp>
#include "../command/ParserImpl.hpp"
#include "../led/LedDriverImpl.hpp"
#include "../session/SessionFactoryImpl.hpp"
#include "../server/Server.hpp"

namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {
    fs::path fifopath;

    try {
        cxxopts::Options options(argv[0], " - LED FIFO Server");
        options.add_options()
            ("f,fifo", "path to fifo (will be created)", cxxopts::value<fs::path>(fifopath), "/tmp/fifo")
            ("h,help", "Print help");
        options.parse_positional("fifo");

        options.parse(argc, argv);

        if (options.count("help")) {
            std::cout << options.help() << "\n";
            exit(0);
        }

        if (! options.count("fifo")) {
            fifopath = "/tmp/fifo";
        }
    } catch (const cxxopts::OptionException& e) {
        std::cerr << "error parsing options: " << e.what() << "\n";
        exit(1);
    }

    if (fs::exists(fifopath)) {
        // Если файл существует проверяем, что это fifo
        struct ::stat fifostat;
        ::stat(fifopath.c_str(), &fifostat);
        if (! S_ISFIFO(fifostat.st_mode)) {
            std::cerr << "File " << fifopath.string() << " already exist and it isn't fifo\n";
            exit(1);
        }
    } else if (mkfifo(fifopath.c_str(), 0666) != 0) {
        std::cerr << "mkfifo(" << fifopath.string() << ") failed: " << std::strerror(errno) << "\n";
        exit(1);
    }

    // fifo либо был создан, либо уже существует

    // Создаю зависимости и связываю их между собой
    fifoserver::command::ParserImpl parser;
    fifoserver::LedDriverImpl ledDriver(false, fifoserver::LedColor::red, 0);
    fifoserver::SessionFactoryImpl sessionFactory(parser, ledDriver);
    fifoserver::Server server(fifopath, sessionFactory);
    server.run();

    return 0;
}
