#!/bin/python3 

# Package imports
import sys

# Local imports
import instructionFuncs

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

    lineCount = 0 # This is so if there is an error I can say what line the error is on

    fileHandler = instructionFuncs.binFileWriter(outputBinFile=outputFile)

    for items in sourceFile:
        splitLines = items.split(" ")
        lineCount += 1
        if splitLines[0] in fileHandler.instructionDict:
            if len(fileHandler.instructionDict[splitLines[0]]["args"]) == 0:
                fileHandler.instructionDict[splitLines[0]]["handler"]()
            else:
                fileHandler.instructionDict[splitLines[0]]["handler"](splitLines[1:])
        elif splitLines[0] == "\0" or splitLines[0] == "\n" or splitLines[0] == "":
            print(f"Found a newline or a null terminator? Wattafak (I should ignore this and not give an error but it is fun) line: {lineCount}")
        else:
            print(f"You made a mistake in the code! Something whent wrong with this line: {lineCount}")

'''
The following ranting in this comment is how I think this is a good way for this to work

Every opcode should get its own function that is just a pretty compact function but the function eventually outputs all the bytes
Because now it is writing bytes in 2 kinda steps so first writing the opcode bytes and then the argument bytes
Making this into 1 function the main switch statement is going to be very pretty and easily understandable
Then another question is ofc how am I going to grab the arguments, in function or pass into function?
Making this into small functions also really helps with logging and error catching at compile time
So it is basically only gains from making everything its own small function instead the frankenstein bullshit that this fucking thing is
And the function of each instruction also has their own error codes and can throw anything and therefore the errors are way more explicit and this makes it nicer to work with
'''


if __name__ == "__main__":
    try:
        userGivenFileName = sys.argv[1]
    except:
        print("You did not provide any file! Usage: python3 assembler.py `filelocation.mav`")
        exit(-1)

    if readFile(userGivenFileName) is not None:
        grabInstruction(readFile(userGivenFileName))