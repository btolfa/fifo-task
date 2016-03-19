/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#pragma once

#include <cstdint>
#include "LedColor.hpp"

namespace fifoserver {

enum class LedState {
    On,
    Off
};

/// Интерфейс для работы с LED, за этим интерфейсом находится "железо"
class LedDriver {
public:
    virtual ~LedDriver() = default;

    virtual void set_state(const LedState state) = 0;
    virtual bool is_enabled() const = 0;

    virtual void set_color(const LedColor color) = 0;
    virtual LedColor get_color() const = 0;

    virtual void set_rate(const uint32_t rate_hz) = 0;
    virtual uint32_t get_rate() const = 0;
};

}