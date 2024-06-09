
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


- ALLOCATE R1 R2

    - Requests a block of memory of size (R2) in bytes and places a pointer to its first element into (R1)
    - If allocation fails R1 is set to 0
    - The size of the block is put into the first element of the array as an unsigned number
        - On the IR virtual machine the datatype of this size type must be specified during initialisation

- FREE R1

    - Mark memory pointed to by R1 as free

- SLEEP Register1

    - Pauses execution and sleeps for (Register1) microseconds



- PARALLEL_START Immediate1

    - Marks the instructions below it to be executed in parallel by a CPU core with ID (Immediate1)

- PARALLEL_STOP

    - Stops the current CPU core executing a block in parallel causing it to idle indefnintely

- SYNC Immediate1

    - Synchronises CPU cores by pausing execution until all cores executing a program with the ID of (Immediate1) reach their SYNC instruction with the same ID of (Immediate1)



























