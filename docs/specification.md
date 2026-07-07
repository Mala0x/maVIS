## Registers: 
* R0 ... R7 -> 0x00..0x70: general purpose registers
* SP -> 0xA0: Stack pointer 
* PC -> 0xF0: Program counter

## Argument types:
* REG: one of the registers
* IMM: any 16-bit number
* ADDR: any 16-bit address
* REG_OR_IMM: anything that could either be a 16-bit number or a register

## Flags:
* zero_flag -> 0xF1: bit is set HIGH when CMP is true else bit is set LOW, things like JE use this flag
* overflow_flag -> 0xF2: Bit is set when a mathematical function overflows

## Instructions: 
* NOP -> 0x00: does nothing and goes to the next instruction
* JMP -> 0x01: jumps to another memory adress (arg0: ADDR)
* JE -> 0x02: jumps if zero flag is set to true (arg0: ADRR)
* MOV REG -> 0x03: moves arg1 into register arg0 (arg0: REG, arg1: REG_OR_IMM)
* MOV IMM -> 0x04
* ADD REG -> 0x05: adds arg1 to register arg0 (arg0: REG, arg1: REG_OR_IMM)
* ADD IMM -> 0x06

## Stuff that should be catched at compile time
* Stuff like integer overflow
* Is this a valid registers
* Are the arguments correct

## Stuff that should be catched at runtime
* Things like do you try to jump out of bounds

## Roadmap!