/** Класс с таким интерфейсом должен создавать session который будет общаться через input и output fifo
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 20.03.16
 * 
 */

#pragma once

#include <boost/filesystem.hpp>

namespace fifoserver {

class SessionFactory {
public:
    virtual ~SessionFactory() = default;

    // detached - значит, что создаёт поток, который тут же отсоединяется.
    virtual void create_detached(boost::filesystem::path const& input, boost::filesystem::path const& output) = 0;
};

}