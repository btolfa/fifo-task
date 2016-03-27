/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 20.03.16
 * 
 */

#include <thread>
#include "SessionFactoryImpl.hpp"
#include "Session.hpp"

namespace fs = boost::filesystem;

namespace fifoserver {

void SessionFactoryImpl::create_detached(fs::path const &input, fs::path const &output) {

    std::thread thread([this, input, output]{
        Session session(input, output, parser_, ledDriver_);
        session.run();
    });

    // С потоками надо работать аккуратнее и по-другому, но это как-то слишком сложно для тестового задания
    thread.detach();
}

SessionFactoryImpl::SessionFactoryImpl(command::Parser &parser, LedDriver &ledDriver)
: parser_{parser}, ledDriver_{ledDriver}
{
}


}

