import sys
from typing import Callable

class Parser:
    triggers: list[str]
    
    ANSI_CODES: list[str] = ['\033[1m', '\033[0m'] # These codes are constant so they can be static

    BOLD_ANSI_CODE: str = ANSI_CODES[0]
    END_ANSI_CODE: str = ANSI_CODES[1]
    
    """
    The argument types are so that you can generate arguments that maybe take another argument as --file fileName.fileExtension
    TXT = the argument will only output text and does not expect any other arguments
    FILE = the argument expects one other argument namely the file that it might need as input (also possible to check for a certain extension)
    """
    
    ARGUMENT_TYPES: list[str] = ['TXT', 'FILE']
    
    programVersion: str | int
    
    argv: list[str]
    argc: int # Mostly for checking if you do not go looking outside the bounds of the argv array
    argIndex: int
    
    commandos: dict[str, Callable[[], None]]
    
    description: dict[str, str]
    
    def __init__(self, version: str | int, argv: list[str], argc: int) -> None: # You have to do this otherwise you cannot bind functions from the class to the dictionary
        self.argv = argv[1:] # Filter out the first argument which is always the program name that is being run and we do not need that
        self.argc = argc
        self.argIndex = 0
        
        self.triggers = ["--h", "--help", "--v", "--version"]
        
        self.description = { # These are the hardcoded values that I would want to see every program have
            "--h": "This shows the help menu (same as --help)",
            "--help": "This shows the help menu (same as --h)",
            "--v": "This shows the version of the program being run",
            "--version": "This shows the version of the program being run"
        }
        
        self.commandos = { # Nice way how to key value pair stuff to methods
            "--h": self.helpArgument,
            "--help": self.helpArgument,
            "--v": self.versionArgument,
            "--version": self.versionArgument
        }
        
        self.programVersion = str(version) # Force to set the version of the program (I will not force integer because version naming is different for differing projects)

    def helpArgument(self) -> None: # Default command that shows the command + description combo
        for k, v in self.description.items():
            print(f"{self.BOLD_ANSI_CODE}{k}{self.END_ANSI_CODE}: {v}") # Sets the trigger to bold (thought that it would be a nice touch)
        self.argIndex += 1
            
    def versionArgument(self) -> None:
        print(f"The program version: {self.programVersion}")
        self.argIndex += 1
        
    def addCommand(self, triggers: str | list, description: str, function: Callable[[], None]) -> None: # Might change this so this is the one public facing command but internally this chains other functions for different user needs like what kind off trigger they want to add
        if isinstance(triggers, list): # Check if the user parsed an array of triggers (this does force all these triggers to use the same function when used)
            for trigger in triggers: # This is usefull for things like --h && --help (these do the same but having both is nice)
                self.triggers.append(str(trigger))
                self.description.update({trigger: description}) # This forces the same description on all the different triggers but this should be fine
                self.commandos.update({trigger: function})
        else: # For when the user only provided 1 trigger
            self.triggers.append(str(triggers))
            self.description.update({triggers: description})
            self.commandos.update({triggers: function})
    
    def addFileCommand(self, fileExtension: str, fileExtensionChecking: bool = True) -> None | str: # The return type could change 
        fileName: str = self.argv[self.argIndex+1] # Grab the next thing in the argument list because that should logically always be the filename
        
        if fileExtensionChecking:
            if fileName.find(fileExtension) == -1:
                print(f"You did not use the correct file extensions, quitting! (Expected file extension: {fileExtension})")
                exit(-1)
            else:
                return fileName
        else:
            return fileName
    
    
    
    
    
    
    
    
    
    
if __name__ == "__main__": # I should also make some testing framework so that I can actually test this shit
    print("This is how you test the argument parser!")
    myParser = Parser(420, sys.argv, len(sys.argv))
    
    def testMethod():
        print(myParser.ANSI_CODES) # Okay so this shows the fact that because everything inside a python object is public that makes making the commands easier

    myParser.addCommand("--t", "This is some bullshit test command", testMethod)
    
    for idx, items in enumerate(sys.argv[1:]): # Should it be legal to make it able to chain commands like --h & --v and then it prints both
        if items in myParser.triggers:
            myParser.commandos[items]()

"""
Stuff to add:
- Methods to add new triggers & commands (DONE) 
- Methods to check the "nature" of a command like when parsing a file the options to make it check the file extension against some kinda set
- Nice color things
- Have an option that makes it possible to save the triggers and stuff to a json or xml file or something so you can use it more and more and then add a function that loads from a json file 
- And the rest I will figure out when I am not on the brink of falling asleep :)
"""