## Registers: 
* R0 ... R7 -> 0x00..0x70: general purpose registers
* SP -> 0xA0: Stack pointer 
* PC -> 0xF0: Program counter

## Flags:
* zero_flag -> 0xF1: bit is set HIGH when CMP is true else bit is set LOW, things like JE use this flag
* overflow_flag -> 0xF2: Bit is set when a mathematical function overflows

## Instructions: 
* NOP -> 0x00: does nothing and goes to the next instruction
* JMP -> 0x01: jumps to another memory adress (arg0: memory address to jump to)
* JE -> 0x02: jumps if zero flag is set to true (arg0: memory address to jump to)
* MOV -> 0x03: moves arg1 into register arg0 (arg0: register, arg1: variable OR register)
* ADD -> 0x04: adds arg1 to register arg0 (arg0: register, arg1: variable)
