# JankC

JankC is a compiled/emulated language that takes inspiration from C. It is a low level language that provides low level control over hardware while also providing abstraction over basic control structures



# Syntax


- Variable declaration

    - [DATATYPE] [NAME] [MODIFIERS] = [EXPRESSION];
    
    - Datatypes
        - char
        - int
        - float
        - long

    - Modifiers
        - $ - Pointer (Dereference with @)
        - [EXPRESSION] - Static array (Does not support VLAs)

    - Example

        - int, hello, @ [5];
            - Declares "hello" as a pointer to an array of 5 integer elements
        
        - float, hi, long = 222.43 + x
            - Declares "hi" as a long float of value 222.43 + the variable x

    















