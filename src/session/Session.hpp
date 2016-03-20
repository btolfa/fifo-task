/** Session работает с fifo - читает запрос и пишет ответ
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 20.03.16
 * 
 */

#pragma once

#include <boost/filesystem.hpp>
#include "../command/Parser.hpp"

namespace fifoserver {

class Session {
public:

    Session(const boost::filesystem::path &input_, const boost::filesystem::path &output_, command::Parser &parser_,
            LedDriver &ledDriver_);

    void run();

private:
    boost::filesystem::path input_;
    boost::filesystem::path output_;
    command::Parser & parser_;
    LedDriver & ledDriver_;
};

}


