/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 27.03.16
 * 
 */

#include "ParserImpl.hpp"
#include "GetLedState.hpp"
#include "FailedCommand.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/make_unique.hpp>

namespace fifoserver {
namespace command {

std::unique_ptr<Command> ParserImpl::parse(std::string const &line) const {
    return boost::make_unique<FailedCommand>();
}

}
}



