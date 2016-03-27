/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 27.03.16
 * 
 */

#include "ParserImpl.hpp"
#include "GetLedState.hpp"
#include "FailedCommand.hpp"
#include "GetLedColor.hpp"
#include "GetLedRate.hpp"
#include "SetLedState.hpp"
#include "SetLedColor.hpp"
#include "SetLedRate.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/make_unique.hpp>

namespace fifoserver {
namespace command {

std::unique_ptr<Command> ParserImpl::parse(std::string const &line) const {
    if (line == "get-led-state") {
        return boost::make_unique<GetLedState>();
    }

    if (line == "get-led-color") {
        return boost::make_unique<GetLedColor>();
    }

    if (line == "get-led-rate") {
        return boost::make_unique<GetLedRate>();
    }

    if (boost::starts_with(line, "set-led-state") && (line.size() > sizeof("set-led-state ") - 1)) {
        return parse_set_state(line);
    }

    if (boost::starts_with(line, "set-led-color") && (line.size() > sizeof("set-led-color ") - 1)) {
        return parse_set_color(line);
    }

    if (boost::starts_with(line, "set-led-rate") && (line.size() > sizeof("set-led-rate ") - 1)) {
        return parse_set_rate(line);
    }

    return boost::make_unique<FailedCommand>();
}

std::unique_ptr<Command> ParserImpl::parse_set_state(std::string const &line) const {
    auto arg = line.substr(sizeof("set-led-state ") - 1);

    if (arg == "on") {
        return boost::make_unique<SetLedState>(LedState::On);
    }

    if (arg == "off") {
        return boost::make_unique<SetLedState>(LedState::Off);
    }

    return boost::make_unique<FailedCommand>();
}

std::unique_ptr<Command> ParserImpl::parse_set_color(std::string const &line) const {
    auto arg = line.substr(sizeof("set-led-color ") - 1);

    if (arg == "red") {
        return boost::make_unique<SetLedColor>(LedColor::red);
    }

    if (arg == "green") {
        return boost::make_unique<SetLedColor>(LedColor::green);
    }

    if (arg == "blue") {
        return boost::make_unique<SetLedColor>(LedColor::blue);
    }

    return boost::make_unique<FailedCommand>();
}

std::unique_ptr<Command> ParserImpl::parse_set_rate(std::string const &line) const {
    auto arg = line.substr(sizeof("set-led-rate ") - 1);
    uint32_t rate;

    try {
        rate = std::stoul(arg);
    } catch (std::exception const&) {
        return boost::make_unique<FailedCommand>();
    }

    if (rate >= 0 && rate <= 5) {
        return boost::make_unique<SetLedRate>(rate);
    }

    return boost::make_unique<FailedCommand>();
}

}
}



