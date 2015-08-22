/**
 *
 * instructions.hpp
 * Defines the instructions set for ppxe
 *
 */

#include "common.hpp"

// Class definition instructions

#define CLASS_DECL 0xFFFFFFFF     // Set ppxe to class definition mode
#define CLASS_END 0x00000000      // End definition of a class

#define CLASS_SET_NAME 0x00000001 // Pop string from stack; this becomes the class name
#define CLASS_DEF_MEM 0x00000002  // Pop two from stack; first is member name, second is object

// Class introspection instructions

#define INTRO_GET_ATTR 0x00000003 // Pop two from stack; first is member name, second is object
#define INTRO_SET_ATTR 0x00000004 // Pop three from stack; first is member name, second is object, third is object to set

