if __name__ == "__main__":
    print("This program is not made to be run like a standalone program!")

# Global variables

registerDict = {
    "R0": 0x00,
    "R1": 0x10,
    "R2": 0x20,
    "R3": 0x30,
    "R4": 0x40,
    "R5": 0x50,
    "R6": 0x60,
    "R7": 0x70,
    "SP": 0xA0,
    "PC": 0xF0
}

# Argument resolution functions that are yet to be made 
def __ADDR_RESOLUTION(ADDR): # Check if the given addr is in between the legal lines otherwise give an error
    return 

def __REG_RESOLUTION(REG): # Check if the register is a valid register otherwise give an error
    return

def __IMM_RESOLUTION(IMM): # Numbers are 16 bit so check if this is right, maybe check for overflow, signed or unsigned that kinda stuff
    return

def __REG_OR_IMM_RESOLUTION(REG_OR_IMM): # Check if it is reg or IMM and then pass onto the function for that type
    return