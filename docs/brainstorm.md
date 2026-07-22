# This is basically just a document I brainstorm in about this entire project. I thought it would be interesting for you to see my thought process.

### "Add QOL things"
* Add tags to easily jump to another spot in the program
* Add macro's for a better experience
* Update the virtual machine & spec to keep up to date with this

#### "Add tags for jumping"
- It looks like 
```
add R0, 10
CMP R1, R0
JE jump_here <- This has to be substituted with the memory address of jump_here
ADD R1, 1

jump_here: <- This should never run by itself only by invocation
    MOV 0x99, R9
    syscall 5 // Example syscall for exiting with the code in register R9
```
- How to implement?
```
I think when the assembler sees something it cannot match with anything in the instruction dict
it will check if it is a singular string that ends with :\n. So it should end with colon and a newline
if it does then we now we have a lable and we have to substitute everything to that memory address.
It does feel that this method introduces a new loop which kinda prechecks everything and sanitizes everything, that does not sound like something bad because in this loop I can remove random spaces and even do the first round of error checking.

Actually adding a kinda pre-processor stage like in c,c++ sounds like a good idea to also add macros.
```

- Macro's look like
```
%macro arg0, arg1
mov %arg0, 1
cmp %arg0, %arg1
%endmacro
```

### What else to add
* "syscalls"
* Bitwise operations such as and, nor, xor, or, etc, etc
* Other jumping options such as JL (jump if less) etc, etc
* Seeing how I would want to implement subtraction
* And some way to kinda print to the terminal (add characters to some kinda buffer, then flush and print the buffer when done ascii) but let's see how I would do that...