/** Тест проверяющий работу сервера
 *
 * Сервер должен ждать когда, кто-нибудь подключиться к fifo
 * Прочитать из fifo 2 строки, (это пути до fifo через которые будет идти фактическое общение)
 * И вызвать SessionFactory
 *
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 20.03.16.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using ::testing::ContainerEq;
using ::testing::ElementsAre;
using ::testing::StrEq;

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <thread>

#include "../../src/server/Server.hpp"
#include "../../src/session/SessionFactory.hpp"

namespace fs = boost::filesystem;

namespace {

class ServerTest : public ::testing::Test {
public:
    ServerTest() {
     mkfifo(path.c_str(), 0666);
    }

    ~ServerTest() {
     fs::remove(path);
    }
protected:
    fs::path path = "/tmp/fifo";
};

class MockSessionFactory : public fifoserver::SessionFactory {
public:
    MOCK_METHOD2(create_detached, void(boost::filesystem::path const&, boost::filesystem::path const& ));
};

TEST_F(ServerTest, ShouldStopIfReceivedQuit) {
    MockSessionFactory factory;
    fifoserver::Server server{path, factory};

    std::thread writer([this]{
        fs::ofstream ofs{path};
        ofs << "quit" << std::endl;
    });
    server.run();
    writer.join();
}

TEST_F(ServerTest, ShouldCallSessionFactory) {
    MockSessionFactory factory;
    fifoserver::Server server{path, factory};

    EXPECT_CALL(factory, create_detached(Eq(fs::path{"/tmp/1"}), Eq(fs::path{"/tmp/2"})));

    std::thread writer([this]{
        fs::ofstream ofs{path};
        ofs << "/tmp/1 /tmp/2" << std::endl;
        ofs << "quit" << std::endl;
    });
    server.run();
    writer.join();
}

TEST_F(ServerTest, ShouldSplitLineBySpace) {
    EXPECT_THAT(fifoserver::Server::split("/tmp/1 /tmp/2"), ElementsAre(StrEq("/tmp/1"), StrEq("/tmp/2")));
    EXPECT_THAT(fifoserver::Server::split("/tmp/1"), ElementsAre(StrEq("/tmp/1")));
    EXPECT_THAT(fifoserver::Server::split("/tmp/1 1 2 3"),
            ElementsAre(StrEq("/tmp/1"), StrEq("1"), StrEq("2"), StrEq("3")));
}

}