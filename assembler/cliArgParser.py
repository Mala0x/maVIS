import sys
from typing import Callable

class Parser:
    triggers: list[str]
    
    ANSI_CODES: list = ['\033[1m', '\033[0m'] # These codes are static / const so these can stay in this part of the class definition

    BOLD_ANSI_CODE: str = ANSI_CODES[0]
    END_ANSI_CODE: str = ANSI_CODES[1]
    
    programVersion: str
    
    commandos: dict[str, Callable]
    
    description: dict[str, str]
    
    def __init__(self, version) -> None: # You have to do this otherwise you cannot bind functions from the class to the dictionary
        self.triggers = ["--h", "--help", "--v", "--version"]
        
        self.description = { # These are the hardcoded values that I would want to see every program have
            "--h": "This shows the help menu (same as --help)",
            "--help": "This shows the help menu (same as --h)",
            "--v": "This shows the version of the program being run",
            "--version": "This shows the version of the program being run"
        }
        
        self.commandos = {
            "--h": self.helpArgument,
            "--help": self.helpArgument,
            "--v": self.versionArgument,
            "--version": self.versionArgument
        }
        
        self.programVersion = str(version) # Force to set the version of the program (I will not force integer because version naming is different for differing projects)

    def helpArgument(self) -> None: # Default command that shows the command + description combo
        for k, v in self.description.items():
            print(f"{self.BOLD_ANSI_CODE}{k}{self.END_ANSI_CODE}: {v}") # Sets the trigger to bold (thought that it would be a nice touch)
            
    def versionArgument(self) -> None:
        print(f"The program version: {self.programVersion}")
        
    def addCommand(self, triggers: str | list, description: str, function: Callable[[], None]) -> None:
        
        if isinstance(triggers, list): # Check if the user parsed an array of triggers (this does force all these triggers to use the same function when used)
            for trigger in triggers: # This is usefull for things like --h && --help (these do the same but having both is nice)
                self.triggers.append(str(trigger))
                self.description.update({trigger: description}) # This forces the same description on all the different triggers but this should be fine
                self.commandos.update({trigger: function})
        else: # For when the user only provided 1 trigger
            self.triggers.append(str(triggers))
            self.description.update({triggers: description})
            self.commandos.update({triggers: function})
    
if __name__ == "__main__":
    print("This is how you test the argument parser!")
    myParser = Parser(420)
    
    for items in sys.argv:
        if items in myParser.triggers:
            myParser.commandos[items]()
            
            
""" 
This implementation feels te cleanest and the fastest, the only thing I am worried about is that when a command has a ton of triggers or something it will become really
redundent and stuff
"""

"""
Stuff to add:
- Methods to add new triggers & commands (DONE) 
- Methods to check the "nature" of a command like when parsing a file the options to make it check the file extension against some kinda set
- Nice color things
- And the rest I will figure out when I am not on the brink of falling asleep :)
"""