/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 20.03.16
 * 
 */

#pragma once

#include "SessionFactory.hpp"

namespace fifoserver {

class SessionFactoryImpl : public SessionFactory {
public:

    virtual void create_detached(boost::filesystem::path const &input, boost::filesystem::path const &output) override;
};

}


