/* 
 * File:   class.hpp
 * Author: nsamson
 *
 * Created on September 12, 2015, 1:18 PM
 */

#pragma once

#include "../pixie/common.hpp"
#include "../pixie/function.hpp"
#include <string>
#include <vector>

namespace pixie {
    
    struct ClassMember;
    struct Class;
    
    typedef std::shared_ptr<Class> cls_ptr;
    typedef std::shared_ptr<ClassMember> cls_mem_ptr; 

    struct Class {
        
        Class(std::string,
              std::vector<cls_ptr>,
              std::vector<cls_mem_ptr>);
        
        std::string name;
        
        std::vector<cls_ptr> parents;
        
        std::vector<cls_mem_ptr> members;
        
    };
    
    struct ClassMember {
        
        std::string name;
        std::string doc;
        
        cls_ptr type;        
        
    };

}

