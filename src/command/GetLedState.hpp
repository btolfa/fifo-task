/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 27.03.16
 * 
 */

#pragma once

#include "Command.hpp"

namespace fifoserver {
namespace command {

class GetLedState : public Command{
public:
    virtual std::string execute(LedDriver &ledDriver) const override final {
        if (ledDriver.is_enabled()) {
            return "OK on";
        } else {
            return "OK off";
        }

    }
};

}
}


