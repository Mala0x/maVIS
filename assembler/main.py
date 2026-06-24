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

def grabInstruction(sourceFile):

    # All these mappings are defined in the spec (../docs/specification.md)

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
            print(hex(instructionDict[tempThing[0]]))

if __name__ == "__main__":
    try:
        userGivenFileName = sys.argv[1]
    except:
        print("You did not provide any file!")
        exit(-1)

    if readFile(userGivenFileName) is not None:
        print(readFile(userGivenFileName))
        grabInstruction(readFile(userGivenFileName))