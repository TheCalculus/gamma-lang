# The Gamma Programming Language
## the bytecode
bytecode is currently limited in Gamma. only basic stack operations, and arithmetic operations exist.
the following Gamma program
```
var x: int = 10;
var y: int = 1;
var c: int = 0;
var b: int = 11;
var p: int = 199;

y = 10 * 1 + 3 + 4;
y = 3 * 2 + 9 * 9;
y = 1 + 1;
y = 1 + 2;
y = 2 * 3;
```
generates the following bytecode
```
ADD_STACK x
ADD_STACK c
FOC_STACK c
MOD_STACK 0

ADD_STACK b
FOC_STACK b
MOD_STACK 11

ADD_STACK p
FOC_STACK p
MOD_STACK 199

FOC_STACK y
MOD_STACK ( ADD 4 ADD 3 ADD 1 MULTIPLY 10 ) (17)
FOC_STACK y
MOD_STACK ( MULTIPLY 9 MULTIPLY 9 ADD 2 MULTIPLY 3 ) (135)
FOC_STACK y
MOD_STACK ( ADD 1 ADD 1 ) (2)
FOC_STACK y
MOD_STACK ( ADD 2 ADD 1 ) (3)
FOC_STACK y
MOD_STACK ( MULTIPLY 3 MULTIPLY 2 ) (6)
```
### expression parsing
In ```MOD_STACK (A) (B)```, A is the value being assigned to the currently focused value in stack. B is not necessarily part of the bytecode, and printed next to the
```MOD_STACK``` command to showcase the unusual parsing of arithmetic expressions in the bytecode. The 'answer' calculated to the arithmetic may seem incorrect,
but this is due to the reversal of the terms and operations in the expression. This allows for the iterative parsing of bytecode, resulting in a correctly
evaluated arithmetic expression, excluding the order of operations.
TODO: 
- add support for evaluating operations adhering to the order of operations
  - support brackets
