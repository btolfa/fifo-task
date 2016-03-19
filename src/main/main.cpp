/**
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 19.03.16.
 */

#include <cstdlib>

#include <boost/filesystem.hpp>
#include <spdlog/spdlog.h>
#include <cxxopts.hpp>

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


    return 0;
}
