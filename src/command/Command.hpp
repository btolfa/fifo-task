/** Интерфейс для комманды - фактического исполнителя запроса
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 20.03.16
 * 
 */

#pragma once

#include "../led/LedDriver.hpp"

namespace fifoserver {
namespace command {

class Command {
public:
    virtual ~Command() = default;

    virtual std::string execute(LedDriver & ledDriver) const = 0;
};

}
}


