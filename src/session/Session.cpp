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
    std::vector<std::string> commands;
    {
        fs::ifstream ifstream{input_};

        for (std::string line; std::getline(ifstream, line);) {
            commands.push_back(line);
        }
    }

    std::vector<std::string> results;
    results.reserve(commands.size());
    std::transform(commands.begin(), commands.end(), std::back_inserter(results),
                   [this](const std::string & line){
                       return parser_.parse(line)->execute(ledDriver_);
                   });

    {
        fs::ofstream ofstream{output_};
        std::copy(results.begin(), results.end(), std::ostream_iterator<std::string>(ofstream, "\n"));
    }
}


}

