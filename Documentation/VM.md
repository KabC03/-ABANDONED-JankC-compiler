


# IR emulation on the virtual machine

The IR virtual machine is a virtual computer that inteprets IR output as its own assembly

The virtual machine has its own registers, program counter, RAM and emulated syscalls


## How the virtual machine works

### Pass over IR file (Preprocessor)

The IR source file is opened and read line by line for a single instruction at a time. This instruction is placed into token structure and this strucure is placed within an array of tokens.

During this time label addresses are placed in corrospondance with a jump address (via a map).


The preprocessor validates syntax by matching the input to an expected format for the opcode (for instance ADD will expect three registers). If an error is encountered, execution is stopped.

If by the end of the file not all label definitions have been resolved, execution is stopped.



### Pass over tokens (Intepreter)


#### Most features are indentical to other ISA implementations with some exceptions

- Registers

    - The IR virtual machine only contains a specified number of general purpose registers and a stack pointer

- Program counter

    - The program counter is an index into the instruction array
    - Increases by one each cycle


- Arithmatic instructions

    - Instructions are performed on virtual registers


- Memory instructions

    - Instructions are performed on virtual RAM
    - No bounds checking is performed. Segmentation faults cannot be caught. The program terminates if an OOB access occurs

- Jump instructions

    - Labels are looked up as keys in the label map. The program counter is set to the corrosponding address


- Abstracted instructions

    - Most instructions are translated into C library features
        - INPUT_x -> scanf
        - OUTPUT_x -> printf
        - SLEEP -> sleep()

    - ALLOCATE is handled by the interpreter searching the memory pool for an available block
    - FREE is handled by the intepreter setting the block as unused memory










































































