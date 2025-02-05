# Assignments-1 on gdb
[solution](./Assignments/assign1/solutions.md)

1.  Consider the program in folder assign1

<!-- -->

a.  Compile it so that it compiles with debugging symbols \[using proper
    option\]

b.  Put breakpoint to function f1.

c.  Put breakpoint to line 10 of b.c

d.  Run the program until it finishes. Which commands are you using to
    take it to completion?

e.  How many times breakpoint "1" is hit in one run of the program ?

f.  How many times breakpoint "2" is hit in one run of the program

g.  How you can see details about a breakpoint ?

h.  How you can see details about all breakpoints ?

i.  What is value of variable x in f1 when breakpoint "1" is hit for
    3^rd^ time ? How you can examine it ?

j.  Rerun the program.put a breakpoint at function f0. list 5 lines
    where it has stopped with breakpoint 3 for firsttime.

> Explore : Complete this rerun. Now see what is the change in details
> of breakpoint s by using command used in "h"


# assignment 2
[soulution](./Assignments/assign2/solutions.md)

a. Put a breakpoint in 1 st executable line of the innermost loop.

b. If you run and continue ,how many times it is supposed to stop at breakpoint 1?

c. How will you continue so that it stops at 1000th iteration of innermost loop ?

d. How you can condition your breakpoint , so that the loop stops at every 1000 th iteration of innermost loop ?

e. Put a breakpoint in the 1 st line of outermost loop.

f. Disable breakpoint “1”

g. Add a command to breakpoint 2 so that it prints the value of “i” at each hit.

h. Delete breakpoint 2.


# assignment 3
[solutions](./Assignments/assign3/SEassignment3.pdf)
1. Consider the program in Assign3.It is a simple state machine.
    a. Put a breakpoint in line 49
   
    b. Try next command
   
    c. How will you get inside the function without using breakpoint?
   
    d. How will you come out the of the function without using next and continue?

3. Consider the program in Assign4 .It is also a simple state machine.If you provide user id and password properly  account details will be displayed. The basic rule is user id should be positive and less than 20 .password is userid *b1000 .The loop will terminate after 10 iteration. It works fine if you provide valid user  id and password.It works fine for invalid userid. But it goes to infiniteloop for invalid password.Run the program .It goes into infinite loop.you need to kill the program by [ctrl^c]
    a. Set a suitable breakpoint in gdb in the routine show.give valid input and run :
   
    b. How you can see the call stack of the routine.
    
    c. Which commands will help you to see each value change of variable “event”?
   
    d. Correct the program so that it doesn’t go to infinite loop for wrong password. Rather main iteration restarts .  [follow the value change path of event for wrong password]
   
> Explore the commands found for 5c to see/use content of a pointer
