/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 27.03.16
 * 
 */

#pragma once

#include <sstream>
#include "Command.hpp"

namespace fifoserver {
namespace command {

class GetLedRate : public Command{
public:
    virtual std::string execute(LedDriver &ledDriver) const override final {
        if (ledDriver.is_enabled()) {
            std::ostringstream oss;
            oss << "OK " << ledDriver.get_rate();
            return oss.str();
        } else {
            // Нельзя узнать цвет если LED выключен
            return "FAILED";
        }
    }
};

}
}


