if __name__ == "__main__":
    print("This program is not made to be run like a standalone program!")

# Global variable definition

def nop():
    print("nop")
    
def jmp():
    print("jmp")
    
def je():
    print("je")

def mov():
    print("mov")
    
def add():
    print("add")

instructionDict = { # This makes the instructions in the python part super modulair and flexible
    "NOP": [0x00, nop()],
    "JMP": [0x01, jmp(),"ADDR"],
    "JE": [0x02, je(),"ADDR"],
    "MOV": [0x03, mov(),"REG", "REG_OR_IMM"],
    "ADD": [0x04, add(),"REG", "REG_OR_IMM"],
}