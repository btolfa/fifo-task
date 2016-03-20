/**
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 20.03.16.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <thread>

namespace fs = boost::filesystem;

namespace {

class FifoTest : public ::testing::Test {
public:
    FifoTest() {
        mkfifo(path.c_str(), 0666);
    }

    ~FifoTest() {
        fs::remove(path);
    }
protected:
    fs::path path = "/tmp/fifo";
};

TEST_F(FifoTest, Should) {
    // Сначала создаём писателя в отдельном потоке
    std::thread writer([this]{
        fs::ofstream os{path};
        // Тут заблокируется
        os << "/tmp/1 /tmp/2" << std::endl;
    });
    std::cout << "\n";
    std::string first, second, third;
    {
        fs::ifstream is{path};
        std::cout << is.eof() << "\n";
        is >> first >> second;
        std::cout << is.eof() << "\n";
        is >> third;
        std::cout << is.eof() << "\n";

    }
    std::cout << first << " " << second << "\n";
    writer.join();
}


}