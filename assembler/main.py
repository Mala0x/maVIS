#!/bin/python3 

# Package imports
import sys

# Local imports
import instructionFuncs

#Mhmm I think i should be able to add comments into the assembly code that should not be to difficult i think
#The comments are now a thing in the assembly! Yipzerz

#When this assembler actually is doing something rather then doing a small bit I might want to think about making something like an argument parser (same for the virtual machine btw)

def readFile(fileName):

    if fileName.find(".mav") == -1:
        print("Your file does not have the correct file extension!")
        exit(-1)

    try:
        file = open(fileName, "r")
        return file.read()
    except OSError:
        print("File not found!")

def grabInstruction(sourceFile):

    # All these mappings are defined in the spec (../docs/specification.md)

    sourceFile = sourceFile.replace(",", "").split("\n")

    try:
        outputFile = open("bin.mabin", "wb")
    except OSError:
        print("I cannot make the output bin file :(")

    lineCount = 0 # This is so if there is an error I can say what line the error is on (it is a bit inconsistent because it takes comments into account)

    fileHandler = instructionFuncs.binFileWriter(outputFile)

    for items in sourceFile:
        splitLines = items.split(" ")
        lineCount += 1
        
        if ';' in splitLines: # This is for removing inline and newline comments in the assembler language
            indexOfComment = splitLines.index(';')
            print(f"I've found a comment the idx of the comment in the array is at {indexOfComment} the array is {splitLines}")
            splitLines = splitLines[:indexOfComment]
            if len(splitLines) == 0:
                lineCount -= 1 # This is because this meant that it was a newline comment and those should not count towards the line count total (otherwise the error messages are giving wrong information)
                return # This just makes it so the loop continues past this and it won't trickle down into the rest of the functions below this point
            print(f"I've found a comment the idx of the comment in the array is at {indexOfComment} the array is {splitLines}") # This should only be printed in verbose mode lowk
        
        if splitLines[0] in fileHandler.instructionDict:
            if len(fileHandler.instructionDict[splitLines[0]]["args"]) == 0: # MY ide gives me errors here but those seem to be innocent
                fileHandler.instructionDict[splitLines[0]]["handler"]()
            else:
                fileHandler.instructionDict[splitLines[0]]["handler"](splitLines[1:])
        elif splitLines[0] == "\0" or splitLines[0] == "\n" or splitLines[0] == "":
            print(f"Found a newline or a null terminator? Wattafak (I should ignore this and not give an error but it is fun) line: {lineCount}")
        else:
            print(f"You made a mistake in the code! Something whent wrong with this line: {lineCount}")

if __name__ == "__main__":
    try:
        userGivenFileName = sys.argv[1] # Maybe check if the user passed a verbose flag so to log things into the terminal
    except:
        print("You did not provide any file! Usage: python3 assembler.py `filelocation.mav`") 
        exit(-1)

    if readFile(userGivenFileName) is not None:
        grabInstruction(readFile(userGivenFileName))