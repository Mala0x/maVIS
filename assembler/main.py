#!/bin/python3 

import sys

def readFile(fileName):

    if fileName.find(".mav") == -1:
        print("Your file does not have the correct file extension!")
        return

    try:
        file = open(fileName, "r")
        return file.read()
    except OSError:
        print("File not found!")

# These are some yet to be realised functions for the different instructions to call into after the parsing stage
def __NOP_INSTRUCTION():
    return

def __JMP_INSTRUCTION():
    return

def __JE_INSTRUCTION():
    return

def __MOV_INSTRUCTION():
    return

def __ADD_INSTRUCTION():
    return

def grabInstruction(sourceFile):

    # All these mappings are defined in the spec (../docs/specification.md)

    # Maybe add something so I know how many arguments every instruction takes, maybe every instruction should have at least 2 items
    # index 0: opcode, index 1: how many args but that seems like boilerplate because i can do len(list), mhmmm...
    # This is a good thinking exercise it seems

    instructionDict = { # This makes the instructions in the python part super modulair and flexible
        "NOP": [0x00],
        "JMP": [0x01, "ADDR"],
        "JE": [0x02, "ADDR"],
        "MOV": [0x03, "REG", "REG_OR_IMM"],
        "ADD": [0x04, "REG", "REG_OR_IMM"],
    }

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

    sourceFile = sourceFile.replace(",", "").split("\n")

    for items in sourceFile:
        tempThing = items.split(" ")
        if tempThing[0] in instructionDict:
            print(f"Instruction: {tempThing[0]}, argument amount: {len(instructionDict[tempThing[0]])-1}")
            for idx, items in enumerate(instructionDict[tempThing[0]][1:]):
                if items == "ADDR":
                    print(f"This argument was an address: {tempThing[idx+1]}")
                elif items == "REG":
                    print(f"This argument was a register: {tempThing[idx+1]}")
                elif items == "REG_OR_IMM":
                    if tempThing[idx+1] in registerDict:
                        print(f"This argument was REG_OR_IMM and this seems to be an REG {tempThing[idx+1]} (addr): {registerDict[tempThing[idx+1]]}")
                    else:
                        print(f"This argument was REG_OR_IMM and this seems to be a IMM {tempThing[idx+1]}")
                elif items == "IMM":
                    print(f"This argument was an IMM: {tempThing[idx+1]}")
                else:
                    print(f"You made a mistake in the code! Something whent wrong with this {tempThing[idx+1]}")
                
                #this ugly if else block will become a switch statement when i figure out how the core logic works

if __name__ == "__main__":
    try:
        userGivenFileName = sys.argv[1]
    except:
        print("You did not provide any file!")
        exit(-1)

    if readFile(userGivenFileName) is not None:
        print(readFile(userGivenFileName))
        grabInstruction(readFile(userGivenFileName))