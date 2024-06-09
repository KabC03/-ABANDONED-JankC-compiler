# JankC

JankC is a compiled/emulated language that takes inspiration from C. It is a low level language that provides low level control over hardware while also providing abstraction over basic control structures

Note: Compiler does not perform checks beyond syntax. Unsafe code is possible

## Syntax

### Inbuilt control

Note: Whitespace is ignored

- Variable declaration

    - [DATATYPE] [NAME] [MODIFIERS] | = [EXPRESSION];
    
    - Datatypes
        - char -> 1 byte
        - int -> 4 bytes
        - float -> 4 bytes
        - long -> 2 byte char, 8 byte int, 8 byte float

        Note: Zero based indexing, no negative indexing, indexing occurs via the datatype itself (e.g if "x" holds integers then x[2] gets the third integer)

    - Modifiers
        - $ - Pointer (Dereference with @)
        - [EXPRESSION] - Static array (Does not support VLAs)




    - Declare "hello" as a pointer to an array of 5 long integer elements

            int, long, hello, @ | =  [5];

    - Declare "hi" as a long float of value 222.43 + the variable x + the array y at index z + 2

            float, hi, long | = 222.43 + x + y[z + 2];




- If statement

    Compounding conditions are not allowed (e.g no "||" or "&&" in statements)

    - if([EXPRESSION] [COMPARATOR] [EXPRESSION]); [CODE] end;

    - If x + 1 == 2 + abc then execute code

            if(x + 1 == 2);

                #Do something

            end;


- for loop

    Only accepts integer iterators

    - for(i, [START], [COMPARATOR], [STOP], [INCREMENT]); [CODE] end;

    - for i = x to i < 10 loop execute code and add 4 to i each time

            for(i, x, <, 10, 4);

                #Do something
            
            end;


- while loop

    - while([EXPRESSION] [COMPARATOR] [EXPRESSION]); [CODE] end;

    - while abc - 2 != def - 3 execute code

            while(abc - 2 != def - 3);

                #Do something

            end;


- function calls

    - Declaration

        - func [RETURN_TYPE] |:: [NAME]([TYPE] | [TYPE] | ...); [CODE] return;

            - a function named check_number which takes two arguments and returns an integer pointer

                    func int, @ |:: check_number(var1 int,@ | var2 float);


                        #Do something

                    
                    return result;


    - Calling

        Arguments are always passed via reference

        - call [EXPRESSION]([EXPRESSION] | [EXPRESSION] | ...);

            - call check_number with two arguments and assign it to an expression

                    hello = call check_number(abc, def);


### Standard functions


- Dynamic memory

    - allocate([EXPRESSION], [EXPRESSION], [DATATYPE]|);

        Returns nothing. Destination pointer set to 0 if allocation fails.

        - Allocate space for 3 char pointers and return the base pointer to abc

                allocate(abc, 3, char, $);


    - free([EXPRESSION]);
        
        Returns nothing. Frees memory pointed to by the pointer.

        - Free the dynamic memory associated with abc

                free(abc);


    - sleep([EXPRESSION]);

        Returns nothing. Sleeps for a specified number of microseconds

        - Sleep for x + 2 microseconds

                sleep(x + 2);


    - input([Expression], [Datatype]);

        Returns nothing. Takes a single input from the terminal and stores it in a varible

        - Get a char input and store it in x

                    input(x, char);
                    
    - output([Expression]);

        Returns nothing. Prints a single item (cannot print entire arrays)

        - print the value contained within x

                    output(x);




    - request([ID]); [CODE] stop;

        Returns nothing. Request a core with an ID to execute code until a stop is met. Then idles. 
        
        For multicore applications

        - request core 1 to do something


                request(1);

                    #Do something

                stop;


    - sync([ID]);

        Waits for other cores with the same sync ID to finish executing their code before continuing. ID is not a core ID but the ID of the sync itself


        - Wait for all cores to hit their own sync with an ID of 1 before continuing

                sync(1)                    





                    





                    





                    