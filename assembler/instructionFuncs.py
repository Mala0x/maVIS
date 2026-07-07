if __name__ == "__main__":
    print("This program is not made to be run like a standalone program!")

# Global variable definition

import io

class binFileWriter:
    
    # Add the source file here so that we can grab what IMM or ADDR or something the user wants to go to
    
    outputBinFile: io.BufferedWriter = None
    
    def __init__(self, outputBinFile):
        self.outputBinFile = outputBinFile
    
    def nop(self):
        print("nop")
        self.outputBinFile.write(b'\x00')

    def jmp(self):
        print("jmp")
        return 0x01

    def je(self):
        print("je")
        return 0x02

    def mov(self):
        print("mov")
        return 0x03

    def add(self):
        print("add")
        return 0x05

# Ofc make the dict reflect everything I have and update the main function to use this choice

instructionDict = { # This makes the instructions in the python part super modulair and flexible
    "NOP": {"opcode": 0x00, "handler": binFileWriter.nop, "args": []}
}