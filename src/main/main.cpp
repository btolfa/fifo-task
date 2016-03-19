/**
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 19.03.16.
 */

#include <cxxopts.hpp>
#include <cstdlib>

int main(int argc, char* argv[]) {
    try {
        cxxopts::Options options(argv[0], " - LED FIFO Server");
        options.add_options()
            ("f,fifo", "input fifo path", cxxopts::value<)
    } catch (const cxxopts::OptionException& e) {
        std::cerr << "error parsing options: " << e.what() << "\n";
        exit(1);
    }

    return 0;
}
