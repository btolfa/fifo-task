/**
 * @author Tengiz Sharafiev <btolfa@gmail.com>
 * @date 20.03.16.
 */

#pragma once

#include <boost/filesystem.hpp>

namespace fifoserver {

class SessionFactory {
public:
    virtual ~SessionFactory() = default;

    virtual void create_and_detach(boost::filesystem::path const& input, boost::filesystem::path const& output) = 0;
};

}