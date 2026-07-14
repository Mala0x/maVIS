if __name__ == "__main__":
    print("This program is not made to be run like a standalone program!")

# Global variable definition

import io, struct, argumentResolution

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

    def __write_to_file(self, argument): # Really simple helper function to 1. DRY and 2. it makes writing the hexcodes nicer because no constant b'\x00'
        
        if (type(argument) is type('string')):
            self.outputBinFile.write((int(argument, 16)).to_bytes())
        elif (type(argument) is type(10)):
            self.outputBinFile.write(argument.to_bytes())
        elif (type(argument) is type(b'\00')):
            self.outputBinFile.write(argument)
        else:
            print("An argument passed into the file writer function was neither an int nor a string. Mhmm... should not happen I think")
        self.outputBinFile.flush()

    def __bytepack_imm(self, imm): # This helper function just checks if the IMM is in limits and if it is it bytepacks it so that it actually is a 16 bit mem number instead of 8 bits when < 255
        imm = int(imm)
        
        if imm < 0 or imm > 0xFFFF:
            print("Your IMM is to big or to small! This will result in this IMM being 0!")
            return 0
        elif imm >= 0 and imm <= 0xFF:
            return struct.pack('>H', imm)
        elif imm > 0xFF:
            return struct.pack('>H', imm)

    def nop(self):
        print("nop")
        self.__write_to_file(0x00)

    def jmp(self, argList):
        print(f"jmp, argList: {argList}")
        self.__write_to_file(0x01)
        self.__write_to_file(argList[0])

    def je(self, argList):
        print(f"je, argList: {argList}")
        self.__write_to_file(0x02)
        self.__write_to_file(argList[0])

    def mov(self, argList):
        print(f"mov, argList: {argList}")
        if self.__reg_or_imm(argList[1]) == 'REG':
            self.__write_to_file(0x03)
            self.__write_to_file(argumentResolution.registerDict[argList[0]])
            self.__write_to_file(argumentResolution.registerDict[argList[1]])
        elif self.__reg_or_imm(argList[1]) == 'IMM':
            self.__write_to_file(0x04)
            self.__write_to_file(argumentResolution.registerDict[argList[0]])
            self.__write_to_file(self.__bytepack_imm(argList[1]))
            

    def add(self, argList):
        print(f"add, argList: {argList}")

        if self.__reg_or_imm(argList[1]) == 'REG':
            self.__write_to_file(0x05)
            self.__write_to_file(argumentResolution.registerDict[argList[0]])
            self.__write_to_file(argumentResolution.registerDict[argList[1]])
        elif self.__reg_or_imm(argList[1]) == 'IMM':
            self.__write_to_file(0x06)
            self.__write_to_file(argumentResolution.registerDict[argList[0]])
            self.__write_to_file(self.__bytepack_imm(argList[1]))