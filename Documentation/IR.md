
# Intermediate representation


## Introduction

The intermediate representation (IR) is an intermediate assembly-like language used in the compiler.


It is produced from source code by the compiler and can either be turned into architecture dependednt assembly (and assembled into machine code) or intepreted on the VM directly.




## Syntax and functionality


### Form
All assembly instructions take the form:

    [OPCODE] [ARG1] [ARG2] [ARG3]

- (R)egister type instructions have three operands
    - Opcode, destination register, source register, source register

- (I)mmediate type instructions have three operands
    - Opcode, register, register, immediate

- (J)ump type instructions have one operand
    - Opcode, label

- (A)bstracted type instructions may have any amount of operands in any configuration
    - These instructions are present in the IR as placeholders for functions often involving system calls


### Registers




### Instructions





### Inbuilt functions

To remain architecture independent, the IR contains placeholder instructions that represent system call operations.

These instructions are not classified under the same R, I, J types as other instructions

When architecture specific assembly is produced from the IR, these instrucions are replaced with the target systems call procedures (often system calls).

The IR virtual machine has its own system calls that map to C functions


- ALLOCATE register immediate 
    - Requests (immediate) bytes of memory and places a pointer to the first byte in (register)
    - The size of the block in bytes is stored in the first element of the array as an 8 byte unsigned number
    - If memory could not be allocated, the value in $E is set to 1

- FREE register immediate




































