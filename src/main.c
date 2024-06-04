/*
 * File: main.c
 * ------------
 * Overview:
 * This file contains the main entry point for the compiler. It orchestrates the various components of the compiler,
 * including parsing, analysis, and code generation, to translate source code into target language (e.g., assembly, bytecode).
 *
 * Usage:
 * To compile a program, run the compiler executable with the source file as an argument:
 *    ./compiler sourcefile.lang
 *
 * Functions:
 * main() - Initializes the compiler components, processes the input files, and manages the compilation pipeline.
 *
 * Example:
 * The main function initializes all necessary data structures, invokes the parsing process to convert source code into an
 * abstract syntax tree (AST), performs semantic analysis, and finally generates the target code.
 *
 * Details to be included in the final documentation:
 * - How the main loop works: Describe the flow of control through the compiler, detailing how input is read,
 *   processed, and output is generated.
 * - Error handling: Explain how errors are handled throughout the compilation process (e.g., syntax errors, semantic errors).
 * - Dependency management: Detail any compiler flags or dependencies required for running the compiler.
 * - Performance considerations: Discuss any aspects of the implementation that are optimized for performance, such as
 *   memory management or concurrent processing.
 * - Extensibility: Describe how new features can be added to the compiler, such as support for new syntax or optimizations.
 *
 * Note:
 * This is placeholder documentation. Specific details about the implementation should be added as the development progresses.
 * Each major component (parser, analyzer, code generator) should be well-documented, and their integration in `main` should
 * be clearly explained.
 */

#include "compiler_structs.h"  
#include "stack.h"             
#include "storage_controller.h"
#include "intepret_IR.h"


int main(int argc, char *argv[]) {

    //Currently debugging VM

    initialise_virtual_machine(256, 6, 1);
    print_VM_properties();

    run_VM("../data/IR_source.txt", 'y');


    return 0;

}




