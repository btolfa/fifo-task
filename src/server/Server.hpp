/**
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 20.03.16.
 */

#pragma once

#include "../session/SessionFactory.hpp"
#include <spdlog/spdlog.h>

namespace fifoserver {

class Server {
public:
    Server(boost::filesystem::path const& fifopath, SessionFactory& factory);

    void run();
    static std::vector<std::string> split(const std::string &line);
private:
    boost::filesystem::path fifopath_;
    SessionFactory & factory_;

    std::shared_ptr<spdlog::logger> lg_;
};

}