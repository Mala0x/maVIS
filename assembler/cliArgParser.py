# import sys

# class Parser:
    
#     commandLineArguments = None
    
#     arguments: dict
    
#     def __init__(self, commandLineArguments) -> None:
#         self.commandLineArguments = commandLineArguments
        
#         self.arguments = { # This is now a hard coded list but I will also add ways to add and delete your own custom commands so this can be used in other projects
#             "UsageProgram": {
#                 "commands": ["", " ", "\n", "\r"],
#                 "output": "This is not how this program is meant to be used!",
#                 "command": self.testingArgumentCommand
#             },
#             "Help": {
#                 "commands": ["--h", "--help"],
#                 "output": "--help or --h gives you the help command!",
#                 "command": self.testingArgumentCommand
#             }
#         }
    
#     def testingArgumentCommand(self, argumentName):
#         print(f"This is a test commando for the: {argumentName} argument!")
        
# if __name__ == "__main__":
#     print("This is how you test the argument parser!")
#     myParser = Parser(sys.argv)
    
#     for items in sys.argv:
#         for arguments in myParser.arguments:
#             if items in myParser.arguments[arguments]["commands"]:
#                 myParser.arguments[arguments]["command"](f"{items}, {arguments}")

"""
The above implementation of a way to map command line arguments to actions takes using --h and --help and " " around 0.222 using the time command
"""

# import sys

# class Parser:
#     arguments = [["--help", "--h"], ["", " ", "\n", "\r"]]    
    
#     commands: list
    
#     outputs = ["This is the help function you can get here by just doing what you did!", "This is just because you gave me a newline"]
    
#     def __init__(self):
#         self.commands = [self.testingArgumentCommand, self.testingArgumentCommand]
    
#     def testingArgumentCommand(self, argumentName):
#         print(f"This is a test commando for the: {argumentName} argument!")
        

# if __name__ == "__main__":
#     print("This is how you test the argument parser!")
#     myParser = Parser()
    
#     for items in sys.argv:
#         for idx, arguments in enumerate(myParser.arguments):
#             if items in arguments:
#                 myParser.commands[idx](items)
                
"""
The above implementation takes around 0.227 seconds. Mhmmmm
"""

import sys

class Parser:
    triggers: list = ["--h", "--help", "", " ", "\n", "\r"]
    
    commandos: dict
    
    def __init__(self):
        self.commandos = {
            "--h": self.testingArgumentCommand,
            "--help": self.testingArgumentCommand,
        }
    
    def testingArgumentCommand(self, argumentName):
        print(argumentName)
    
if __name__ == "__main__":
    print("This is how you test the argument parser!")
    myParser = Parser()
    
    for items in sys.argv:
        if items in myParser.triggers:
            myParser.commandos[items](items)
            
            
""" 
This implementation feels te cleanest and the fastest, the only thing I am worried about is that when a command has a ton of triggers or something it will become really
redundent and stuff
"""

"""
Stuff to add:
- Methods to add new triggers & commands 
- Methods to check the "nature" of a command like when parsing a file the options to make it check the file extension against some kinda set
- Nice color things
- And the rest I will figure out when I am not on the brink of falling asleep :)
"""