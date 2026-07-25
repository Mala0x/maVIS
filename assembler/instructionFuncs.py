if __name__ == "__main__":
    print("This program is not made to be ran like a standalone program!")

# Global variable definition

import io, struct, argumentResolution

'''
The biggest thing missing in my opinion from this setup is the error handling.
I want to make this assembler as robust and verbose as possible so it is actually 'nice' to work in this language of mine
I do not want the user to kinda guess what went wrong, sometimes this is needed but I do not want that
This should also be reflected in the virtual_machine/runtime when possible make the errors as verbose as possible
'''

class binFileWriter:
    
    # Add the source file here so that we can grab what IMM or ADDR or something the user wants to go to and to write to it simply and abstractly
    
    outputBinFile: io.BufferedWriter = None

    instructionDict = None

    def __init__(self, outputBinFile):
        self.outputBinFile = outputBinFile

        self.instructionDict = { # This makes the instructions in the python part super modulair and flexible
            "NOP": {"handler": self.nop, "args": []},
            "JMP": {"handler": self.jmp, "args": ["ADDR"]},
            "JE": {"handler": self.je, "args": ["ADDR"]},
            "MOV": {"handler": self.mov, "args": ["REG", "REG_OR_IMM"]},
            "ADD": {"handler": self.add, "args": ["REG", "REG_OR_IMM"]},
            "CMP": {"handler": self.cmp, "args": ["REG", "REG_OR_IMM"]},
            "SYSC": {"handler": self.sysc, "args": ["IMM"]}
        }

    def __reg_or_imm(self, reg_or_imm): # Easy helper function to dispatch the knowlegde if the function should be the imm or the reg version
        if reg_or_imm in argumentResolution.registerDict:
            return 'REG'
        else:
            return 'IMM'

    def __write_to_file(self, argument): # Really simple helper function to 1. DRY and 2. it makes writing the hexcodes nicer because no constant b'\x00'
        
        # I could improve this function a ton by just having 1 argument that is a list with a variable length, then looping over it and checking the type of each item in the array
        # This means I have to only call this function once for each opcode (plus the fact that I then have to flush the buffer sometimes even three time less then with this implementation)
        
        if isinstance(argument, str): # This is to check the variable type so that I can parse them correctly into the final mabin file
            self.outputBinFile.write((int(argument, 16)).to_bytes())
        elif isinstance(argument, int):
            self.outputBinFile.write(argument.to_bytes())
        elif isinstance(argument, bytes):
            self.outputBinFile.write(argument)
        else:
            print(f"An argument passed into the file writer function was neither an int nor a string nor a bytes object. Mhmm... should not happen I think. You parsed a: {type(argument)}")
        self.outputBinFile.flush() # Flushing the buffer everytime might not be the strat when parsing bigger files... Gotta think about that one in a later version

    def __bytepack_imm(self, imm): # This helper function just checks if the IMM is in limits and if it is it bytepacks it so that it actually is a 16 bit mem number instead of 8 bits when < 255
        try:
            imm = int(imm, 16)
        except:
            print("Could not convert your IMM argument into a valid integer! Stopping the compilation here!")
            exit(-1)

        if imm < 0 or imm > 0xFFFF:
            print("Your IMM is to big or to small! This will result in this IMM being 0! (I am currently only supporting unsigned 16bit integers, sowwy :3)")
            return 0
        elif imm >= 0 and imm <= 0xFFFF:
            return struct.pack('>H', imm)
        else:
            print("Something really went wrong here xD. This does result in the IMM becoming 0!")
            return 0

    def nop(self):
        print("nop")
        self.__write_to_file(0x00)

    def jmp(self, argList):
        print(f"jmp, argList: {argList}")
        self.__write_to_file(0x01)
        self.__write_to_file(self.__bytepack_imm(argList[0]))

    def je(self, argList):
        print(f"je, argList: {argList}")
        self.__write_to_file(0x02)
        self.__write_to_file(self.__bytepack_imm(argList[0]))

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

    def cmp(self, argList):
        print(f"cmp, argList: {argList}")
        if self.__reg_or_imm(argList[1]) == 'REG':
            self.__write_to_file(0x07)
            self.__write_to_file(argumentResolution.registerDict[argList[0]])
            self.__write_to_file(argumentResolution.registerDict[argList[1]])
        elif self.__reg_or_imm(argList[1]) == 'IMM':
            self.__write_to_file(0x08)
            self.__write_to_file(argumentResolution.registerDict[argList[0]])
            self.__write_to_file(self.__bytepack_imm(argList[1]))
            
    def sysc(self, argList):
        print(f"sysc, argList: {argList}")
        self.__write_to_file(0x09)
        self.__write_to_file(self.__bytepack_imm(argList[0]))