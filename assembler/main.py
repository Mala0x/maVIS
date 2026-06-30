#!/bin/python3 

# Package imports
import sys

# Local imports
import instructionFuncs, argumentResolution

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

    # Maybe ADDR something so I know how many arguments every instruction takes, maybe every instruction should have at least 2 items
    # index 0: opcode, index 1: how many args but that seems like boilerplate because i can do len(list), mhmmm...
    # This is a good thinking exercise it seems

    sourceFile = sourceFile.replace(",", "").split("\n")

    try:
        outputFile = open("bin.mabin", "wb")
    except OSError:
        print("I cannot make the output bin file :(")

    # This should be done so much better if i say writing code is art this is fucking ugly

    for items in sourceFile:
        tempThing = items.split(" ")
        if tempThing[0] in instructionFuncs.instructionDict:
            outputFile.write(instructionFuncs.instructionDict[tempThing[0]][0].to_bytes())
            for idx, items in enumerate(instructionFuncs.instructionDict[tempThing[0]][1:]):
                if items == "ADDR":
                    outputFile.write(argumentResolution.__ADDR_RESOLUTION(tempThing[idx+1]))
                elif items == "REG":
                    outputFile.write(argumentResolution.__REG_RESOLUTION(tempThing[idx+1]))
                elif items == "REG_OR_IMM":
                    outputFile.write(argumentResolution.__REG_OR_IMM_RESOLUTION(tempThing[idx+1]))
                elif items == "IMM":
                    outputFile.write(argumentResolution.__IMM_RESOLUTION(tempThing[idx+1]))
                else:
                    print(f"You made a mistake in the code! Something whent wrong with this {tempThing[idx+1]}")
                
                #this ugly if else block will become a switch statement when i figure out how the core logic works

if __name__ == "__main__":
    try:
        userGivenFileName = sys.argv[1]
    except:
        print("You did not provide any file! Usage: python3 assembler.py `filelocation.mav`")
        exit(-1)

    if readFile(userGivenFileName) is not None:
        print(readFile(userGivenFileName))
        grabInstruction(readFile(userGivenFileName))