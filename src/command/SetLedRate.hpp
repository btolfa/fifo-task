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

class SetLedRate : public Command{
public:
    SetLedRate(const uint32_t rate) : rate_{rate} {}

    virtual std::string execute(LedDriver &ledDriver) const override final {
        if (ledDriver.is_enabled()) {
            ledDriver.set_rate(rate_);
            return "OK";
        } else {
            // Нельзя выставлять частоту если LED выключен
            return "FAILED";
        }

    }

    uint32_t rate_;
};

}
}


