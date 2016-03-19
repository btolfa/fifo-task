/** Если бы led был настоящим, тут бы был тест для интерфейса
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#include <gtest/gtest.h>
#include "../../src/led/LedDriverImpl.hpp"

namespace {

TEST(LedDriverTest, ShouldSetAndGet) {
    fifoserver::LedDriverImpl impl(false, fifoserver::LedColor::red, 0);
    fifoserver::LedDriver& led = impl;

    ASSERT_FALSE(led.is_enabled());
    led.set_state(fifoserver::LedState::On);
    EXPECT_TRUE(led.is_enabled());

    ASSERT_EQ(fifoserver::LedColor::red, led.get_color());
    led.set_color(fifoserver::LedColor::green);
    EXPECT_EQ(fifoserver::LedColor::green, led.get_color());

    ASSERT_EQ(0, led.get_rate());
    led.set_rate(3);
    EXPECT_EQ(3, led.get_rate());
}

}