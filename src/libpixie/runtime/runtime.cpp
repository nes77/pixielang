//
// Created by nsamson on 5/22/16.
//

#include "../runtime.hpp"

using namespace pixie::runtime;

std::shared_ptr<PixieClass> floatType;
std::shared_ptr<PixieClass> intType;
std::shared_ptr<PixieClass> strType;
std::shared_ptr<PixieFunction> floatConstructor;
std::shared_ptr<PixieFunction> intConstructor;
std::shared_ptr<PixieFunction> strConstructor;

struct FloatConstructor : public PixieFunction {
    void call(BytecodeEngine& env);
    ~FloatConstructor(){}
};

struct IntConstructor : public PixieFunction {
    void call(BytecodeEngine& env);
    ~IntConstructor(){}
};

struct StrConstructor : public PixieFunction {
    void call(BytecodeEngine& env);
    ~StrConstructor(){};
};

void pixie::runtime::initializePixieRuntime() {
    floatConstructor.reset(new FloatConstructor());
    PixieClass* fType = new PixieClass("float", floatConstructor);

    intConstructor.reset(new IntConstructor());
    strConstructor.reset(new StrConstructor());

    PixieClass* iType = new PixieClass("integer", intConstructor);
    PixieClass* sType = new PixieClass("string", strConstructor);

    floatType.reset(fType);
    intType.reset(iType);
    strType.reset(sType);

}