if __name__ == "__main__":
    print("This program is not made to be run like a standalone program!")

# Global variable definition

import io, argumentResolution

class binFileWriter:
    
    # Add the source file here so that we can grab what IMM or ADDR or something the user wants to go to
    
    outputBinFile: io.BufferedWriter = None

    instructionDict = None
    
    # The functions themselves return something, tho if a function has to decide which of its opcodes it should return it hands this over to another helper function

    def __init__(self, outputBinFile):
        self.outputBinFile = outputBinFile

        self.instructionDict = { # This makes the instructions in the python part super modulair and flexible
            "NOP": {"handler": self.nop, "args": []},
            "JMP": {"handler": self.jmp, "args": ["ADDR"]},
            "JE": {"handler": self.je, "args": ["ADDR"]},
            "MOV": {"handler": self.mov, "args": ["REG", "REG_OR_IMM"]},
            "ADD": {"handler": self.add, "args": ["REG", "REG_OR_IMM"]}
        }

    def __reg_or_imm(self, reg_or_imm):
        if reg_or_imm in argumentResolution.registerDict:
            return 'REG'
        else:
            return 'IMM'

    def nop(self):
        print("nop")

    def jmp(self, argList):
        print(f"jmp, argList: {argList}")

    def je(self, argList):
        print(f"je, argList: {argList}")

    def mov(self, argList):
        print(f"mov, argList: {argList}")

        if self.__reg_or_imm(argList[1]) == 'IMM':
            print("This is an imm! Treat it like it!")
        elif self.__reg_or_imm(argList[1]) == 'REG':
            print("This is a reg! Treat it like it!")

    def add(self, argList):
        print(f"add, argList: {argList}")

        if self.__reg_or_imm(argList[1]) == 'IMM':
            print("This is an imm! Treat it like it!")
        elif self.__reg_or_imm(argList[1]) == 'REG':
            print("This is a reg! Treat it like it!")