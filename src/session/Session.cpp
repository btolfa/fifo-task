/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 20.03.16
 * 
 */

#include "Session.hpp"

#include <boost/filesystem/fstream.hpp>

namespace fs = boost::filesystem;

namespace fifoserver {

Session::Session(const boost::filesystem::path &input_, const boost::filesystem::path &output_, command::Parser &parser_,
        LedDriver &ledDriver_) : input_(input_), output_(output_), parser_(parser_), ledDriver_(ledDriver_) {

}

void Session::run() {
    fs::ifstream ifstream{input_};

    std::string line;
    std::getline(ifstream, line);
    auto p_command = parser_.parse(line);

    fs::ofstream ofstream{output_};
    ofstream << p_command->execute(ledDriver_) << std::endl;
}


}

