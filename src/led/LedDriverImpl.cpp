/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#include "LedDriverImpl.hpp"

namespace fifoserver {

void LedDriverImpl::set_color(const LedColor color) {
    std::lock_guard<std::mutex> guard(mutex_);

    logger_->info("Set color to {}", color);
    color_ = color;
}

LedColor LedDriverImpl::get_color() const {
    std::lock_guard<std::mutex> guard(mutex_);

    return color_;
}

void LedDriverImpl::set_rate(const uint32_t rate_hz) {
    std::lock_guard<std::mutex> guard(mutex_);

    if (rate_hz > 5) {
        logger_->error("Invalid LED blink rate: {}", rate_hz);
    } else {
        logger_->info("Set LED blink rate to {}", rate_hz);
        rate_ = rate_hz;
    }

}

uint32_t LedDriverImpl::get_rate() const {
    std::lock_guard<std::mutex> guard(mutex_);

    return rate_;
}

void LedDriverImpl::set_state(const LedState state) {
    std::lock_guard<std::mutex> guard(mutex_);

    if (state == LedState::On) {
        logger_->info("Enable LED");
    } else {
        logger_->info("Disable LED");
    }

    b_enabled_ = (state == LedState::On);
}

bool LedDriverImpl::is_enabled() const {
    std::lock_guard<std::mutex> guard(mutex_);

    return b_enabled_;
}


}