/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#pragma once

#include "LedDriver.hpp"

namespace fifoserver {

class LedDriverImpl : public LedDriver {
public:
    LedDriverImpl(bool state, LedColor color, uint32_t rate) : state_(state), color_(color), rate_(rate) { }

    virtual void set_state(const bool state) override;
    virtual bool get_state() const override;

    virtual void set_color(const LedColor color) override;
    virtual LedColor get_color() const override;

    virtual void set_rate(const uint32_t rate_hz) override;
    virtual uint32_t get_rate() const override;
private:
    bool state_;
    LedColor color_;
    uint32_t rate_;
};

}