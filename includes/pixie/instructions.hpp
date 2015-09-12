/**
 *
 * instructions.hpp
 * Defines the instructions set for pixie
 *
 */

#include "common.hpp"

// Class definition instructions

#define CLASS_DECL 0xFFFFFFFF     // Set pixie to class definition mode
#define CLASS_END  0x00000000      // End definition of a class

#define CLASS_SET_NAME 0x00000001 // Pop string from stack; this becomes the class name
#define CLASS_DEF_MEM  0x00000002  // Pop two from stack; first is member name, second is object

// Class introspection instructions

#define INTRO_GET_ATTR 0x00000003 // Pop two from stack; first is member name, second is object
#define INTRO_SET_ATTR 0x00000004 // Pop three from stack; first is member name, second is object, third is object to set
#define INTRO_HAS_ATTR 0x00000005 // Pop name, obj from stack; put boolean on stack
#define INTRO_GET_TYPE 0x00000006 // Pop obj from stack; put object representing type(obj)

// Builtin functions

#define BI_ADD 0x00000007         // Pop two from stack; put result of add function on stack
#define BI_SUB 0x00000008         // Pop two from stack; put result of sub function on stack
#define BI_MUL 0x00000009         // Pop two from stack; put result of mult function on stack
#define BI_DIV 0x0000000A         // Pop two from stack; put result of div function on stack
#define BI_POW 0x0000000B         // Pop two from stack; put result of pow function on stack

#define BI_COMP_EQ  0x0000000C    // Pop two from stack; put structural equality result on stack
#define BI_COMP_LT  0x0000000D    // Pop two; put result of less than on stack
#define BI_COMP_GT  0x0000000E    // Pop two; put result of greater than on stack
#define BI_COMP_LEQ 0x0000000F    // Pop two; put result of less than or equal to on stack
#define BI_COMP_GEQ 0x00000010    // Pop two; put result of greater than or equal to on stack
#define BI_COMP_NEQ 0x00000011    // Pop two; put inverted result of structured in equality on stack

#define BI_RSHF_LOG 0x00000012    // Pop two; put result of logical right shift on stack
#define BI_LSHF_LOG 0x00000013    // Pop two; put result of logical left shift on stack
#define BI_RSHF_AR  0x00000014    // Pop two; put result of arithmetic right shift on stack
#define BI_LSHF_AR  0x00000015    // Pop two; put result of arithmetic left shift on stack

#define BI_CALL     0x00000016    // Pop function name, execute instructions in function

// Stream IO functions

#define IO_PRINT   0x00000000     // Pop one; print string to current out stream
#define IO_PUTCHAR 0x00000001     // Pop one; print character to current out stream
#define IO_GETCHAR 0x00000002     // Read one char from current in stream; put on stack


