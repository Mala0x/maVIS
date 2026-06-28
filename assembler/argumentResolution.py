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

    try:
        ADDR = int(ADDR, 16)
    except:
        print("This did not work! addr to int")

    if ADDR >= 0x0 and ADDR <= 0xFFFF:
        return hex(int(ADDR))
    else:
        print("This does not work! addr to big")

def __REG_RESOLUTION(REG): # Check if the register is a valid register otherwise give an error
    if REG in registerDict:
        return hex(registerDict[REG])
    else:
        print("This does not work! reg")

def __IMM_RESOLUTION(IMM): # Numbers are 16 bit so check if this is right, maybe check for overflow, signed or unsigned that kinda stuff

    try:
        IMM = int(IMM)
    except:
        print("This IMM couldnt be converted to int")

    if IMM > -0x8000 and IMM < 0x7FFF:
        return IMM
    else:
        print("This does not work maybe overflow maybe error maybe do something else! IMM")

def __REG_OR_IMM_RESOLUTION(REG_OR_IMM): # Check if it is reg or IMM and then pass onto the function for that type
    if REG_OR_IMM in registerDict:
        return __REG_RESOLUTION(REG_OR_IMM)
    if REG_OR_IMM not in registerDict:
        return __IMM_RESOLUTION(REG_OR_IMM)
    else:
        print("This does not work! REG or IMM")