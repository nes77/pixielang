//
// Created by nsamson on 5/22/16.
//

#ifndef PIXIE_CLASSES_HPP
#define PIXIE_CLASSES_HPP

#include "../common.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace pixie {
    namespace runtime {

        struct BytecodeEngine;
        struct PixieClass;

        struct PixieFunction {
            std::unordered_map<uint8_t, PixieClass> explicitTypes;
            uint8_t numArgs;

            virtual void call(BytecodeEngine& engine) = 0;
            virtual ~PixieFunction() {}
        };

        struct PixieRuntimeFunction : PixieFunction {

            std::vector<uint8_t> code;

            void call(BytecodeEngine& engine);

            ~PixieRuntimeFunction(){}

        };

        struct PixieClass {

            std::string name;
            std::shared_ptr<PixieClass> superClass;
            std::shared_ptr<PixieFunction> constructor;

            PixieClass(std::string name,
                std::shared_ptr<PixieFunction> constructor,
                std::shared_ptr<PixieClass> super = nullptr);

        };

        struct PixieObject {
            std::shared_ptr<PixieClass> type;
            std::unordered_map<std::string, std::shared_ptr<PixieObject>> attributes;

            virtual std::string toString();

            PixieObject() {}
            PixieObject(std::shared_ptr<PixieClass> type);

            virtual ~PixieObject(){}
        };

        struct PixieString : public PixieObject {
            std::string contents;

            std::string toString();

            PixieString(std::string value);

            virtual ~PixieString(){}
        };

        struct PixieInt : public PixieObject {
            int64_t value;

            std::string toString();
            PixieInt(int64_t value);

            virtual ~PixieInt(){}
        };

        struct PixieFloat : public PixieObject {
            double value;

            std::string toString();

            PixieFloat(double value);

            virtual ~PixieFloat(){}
        };





    }
}

#endif //PIXIE_CLASSES_HPP
