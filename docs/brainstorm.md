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
%macroname arg0, arg1
    mov %arg0, 1
    cmp %arg0, %arg1
%endmacro
```
- It would be used as follow

```
%addAndCompare arg0, arg1
    MOV %arg0, %arg1
    CMP %arg1, %arg0
%endmacro

@addAndCompare r0, 35

; And this then in the assembler would expand into

@addAndCompare r0, 35 goes to -->

MOV r0, 35
CMP 35, r0

(Should be kinda obvious the only thing I am kinda on the fence about is the syntax but mhmm we'll see)
```

# Stuff I have to do in the rewrite
* Refactor both the python and c++ code to use the same coding style across everything
* Make the folders better rename it to src/ instead of virtual_machine/
* Folder everything up for a better project overview
* Finish writing both the argument parser & the test suite in both python and c++
* Start thinking about the high level language that is going to compile down into bytecode that compiles down into machine code
* Start writing the compiler for the language in rust maybe (I want to learn rust and that seems like a fun way to actually start writing some rust code)
* Introduce SDL3 into the project en the build process and think about how I would implement that into the entire project
  * the sdl window will by default show but can be disabled using --headless
  * the sdl window will refresh at a fixed 60hz by default, vsync or other refresh rates could be implemented without much frictions

* Adapt the bytecode to the high level language and add and subtract as needed

* **The ultimate test:** Write a program that loads a bitmap into a framebuffer and shows it on the sdl3 window


### What else to add
* "syscalls" (<-- This is a pretty big one and will be used in the following: sysc IMM so you have 2^16-1 possible syscalls xD) [This has also been done (now I just need to think about what syscalls I actually want to implement)]
* Bitwise operations such as and, nor, xor, or, etc, etc
* Other jumping options such as JL (jump if less) etc, etc
* Seeing how I would want to implement subtraction
* And some way to kinda print to the terminal (add characters to some kinda buffer, then flush and print the buffer when done ascii) but let's see how I would do that...
* Add a way to have comments in the assembly (both inline and on a seperate newline) [This has been done (was easier then I initially thought lmao)]
* Add SDL3 and that will be the default so I can eventually make my own kinda operating system and there will be a option to run the virtual machine in headless mode so that you do not have the window popping up constantly
* Start thinking about and maybe even writing the specs for a higher level language
* To kinda jump off the above one start thinking about writing a compiler for the higher level langauge 
* Make the decision if I want to also make some intermediate representation or not (I do not think this is needed because this is mostly used for compiler backends that need to cross compile but my language only needs to be compiled down into a .mabin file and it can be run on my emulator)