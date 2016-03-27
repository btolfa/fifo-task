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

    return boost::make_unique<FailedCommand>();
}

}
}



