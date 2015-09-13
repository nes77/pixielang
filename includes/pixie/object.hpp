#pragma once

#include "../pixie/common.hpp"
#include "../pixie/class.hpp"

namespace pixie {

    struct Object {
        
        std::shared_ptr<pixie::Class> type;
        
        virtual ~Object();
    };

}