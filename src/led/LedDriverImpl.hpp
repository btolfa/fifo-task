/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#pragma once

#include <spdlog/spdlog.h>
#include "LedDriver.hpp"

namespace fifoserver {

class LedDriverImpl : public LedDriver {
public:
    LedDriverImpl(bool state, LedColor color, uint32_t rate) : b_enabled_(state), color_(color), rate_(rate) { }

    virtual void set_state(const LedState state) override;
    virtual bool is_enabled() const override;

    virtual void set_color(const LedColor color) override;
    virtual LedColor get_color() const override;

    virtual void set_rate(const uint32_t rate_hz) override;
    virtual uint32_t get_rate() const override;
private:
    bool b_enabled_;
    LedColor color_;
    uint32_t rate_;

    std::shared_ptr<spdlog::logger> logger_ {spdlog::stdout_logger_mt("led")};
};

}