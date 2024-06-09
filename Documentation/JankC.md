# JankC

JankC is a compiled/emulated language that takes inspiration from C. It is a low level language that provides low level control over hardware while also providing abstraction over basic control structures



# Syntax

Note: Whitespace is ignored

- Variable declaration

    - [DATATYPE] [NAME] [MODIFIERS] | = [EXPRESSION];
    
    - Datatypes
        - char
        - int
        - float
        - long

    - Modifiers
        - $ - Pointer (Dereference with @)
        - [EXPRESSION] - Static array (Does not support VLAs)




    - Declare "hello" as a pointer to an array of 5 integer elements

            int, hello, @ | =  [5];

    - Declare "hi" as a long float of value 222.43 + the variable x

            float, hi, long | = 222.43 + x;




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

        - func [RETURN_TYPE] | [NAME]([TYPE] | [TYPE] | ...); [CODE] return;

            - a function named check_number which takes two arguments and returns an integer pointer

                    func int, @ | check_number(var1 int,@ | var2 float);


                        #Do something

                    
                    return result;



    - Calling

        - call [NAME]([NAME] | [NAME] | ...);

            - call check_number with two arguments and assign it to an expression

                    hello = call check_number(abc, def);