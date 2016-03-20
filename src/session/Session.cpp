/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 20.03.16
 * 
 */

#include "Session.hpp"

namespace fifoserver {

Session::Session(const boost::filesystem::path &input_, const boost::filesystem::path &output_, command::Parser &parser_,
        LedDriver &ledDriver_) : input_(input_), output_(output_), parser_(parser_), ledDriver_(ledDriver_) {

}

void Session::run() {

}


}

