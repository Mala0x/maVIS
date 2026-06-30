if __name__ == "__main__":
    print("This program is not made to be run like a standalone program!")

# Global variable definition

instructionDict = { # This makes the instructions in the python part super modulair and flexible
    "NOP": [0x00],
    "JMP": [0x01, "ADDR"],
    "JE": [0x02, "ADDR"],
    "MOV": [0x03, "REG", "REG_OR_IMM"],
    "ADD": [0x04, "REG", "REG_OR_IMM"],
}