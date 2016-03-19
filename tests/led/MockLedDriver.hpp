/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#pragma once 

#include <gmock/gmock.h>
#include "../../src/led/LedDriver.hpp"

class MockLedDriver : public fifoserver::LedDriver {
public:
    MOCK_METHOD1(set_state, void(const fifoserver::LedState));
    MOCK_CONST_METHOD0(is_enabled, bool());

    MOCK_METHOD1(set_color, void(const fifoserver::LedColor));
    MOCK_CONST_METHOD0(get_color, fifoserver::LedColor());

    MOCK_METHOD1(set_rate, void(const uint32_t));
    MOCK_CONST_METHOD0(get_rate, uint32_t());
};