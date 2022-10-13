<h1 align="center">Two Pass Assembler</h1>
<p align="center">
  <img src="readme/terminal-output.gif" alt="Terminal Output">
  <br>
  <i>Terminal output of the two pass assembler.</i>
</p>

## About

This two pass assembler was written for an [imaginary computer](#computer-and-language-structure) as a final project of the course *[20465 - Systems Programming in C](https://openu.ac.il/courses/20465.htm)*.

The project was written in collaboration with [@OBaca](https://github.com/OBaca).

## Usage

1. Run `make`
2. Run `./assembler yourFileName.as`

The assembler will output *.am*, *.ent*, *.ext* and *.ob* files. 

## Files Structure

- Assembler files:

    - `assembler.c` - Main program.

    - `pre_assembler_phase.c` - Goes through the program and interprets all the macros present in it.

    - `phaseOne.c` - An implementation of first pass algorithm.

    - `phaseTwo.c` - An implementation of second pass algorithm.

    - `manage_line.c` - line analyzing functions used in phasedTwo.

    - `errors.c` - A thorough check of errors during first and second pass.
    
    - `data_structure.c` - Creating linked lists for: macros table, symbol table and line table.


## Computer and Language Structure

### Computer Structure
Our imaginary computer consists of CPU, Registers and RAM (some of the RAM is utilized as stack).

The CPU has 16 registers (r0-r15). each register size is 20 bits. lsb is 0 and msb is 19.

The CPU has a register named PSW which contains flags regarding computer status in each moment.

Memory size is 8192 and each memory cell size is 20 bits.

The computer works only with Integers.

### Word and Sentence Structure

Each computer instruction consists between 1 to 3 words which are encoded in the following manner:

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  destination | destination  |  destination register | destination register  | destination register | destination register | origin | origin | origin register | origin register | origin register | origin register | funct | funct | funct | funct | E |R | A | 0 |

The assembler consists of 16 actions, each of them consists a different funct and opcode (*mov, cmp, add, sub, lea, clr, not, inc, dec, jmp, bne, jsr, red, prn, rts and stop*).

There are 4 kinds of sentences the assembler knows:

1. Empty Sentence - A line contains only whitespaces.

2. Comment Sentence - A line that starts with `;`.

3. Instruction Sentence - Variables assignment and declaration.

4. Command Sentence - Creates an action for the machine to execute upon running the program.

Line maximum length is 80. 

Usage of labels is optional. A label is any word (reserved words not allowed) which is declared at the beginning of the sentence and ends with `:`. For example `myLabel:`.

#### Instruction Sentence

Instruction Sentence may or may not start with a label. Valid instructions are: 

1. **.data** - declaration of integers. For example: `.data 7, –57, +17, 9`.

2. **.string** - declaration of a string contained within *" "*. For example: `.string "abcdef"`.

3. **.extern** - reference to an external label, declared in another file. For example `.extern myLabel`.

4. **.entry** - reference to an internal label, that already was or will be declared in the program. For example `.entry myLabel`.

#### Command Sentence

Command Sentence may or may not start with a label. Valid commands are: 

**mov** - copies origin operand to destination

**cmp** - performs comparison between 2 operands

**add** - destination operand receives the addition result of origin and destination

**lea** - load effective address

**clr** - clears operand

**not** - logical not, reverses all bits in operand

**inc** - increments operand's content by 1

**dec** - decrements operand's content by 1

**jmp** - jumps to instruction in destination operand

**bne** - branch if not equal to zero

**jsr** - calls a subroutine

**red** - reads a char from stdin

**prn** - prints char into stdout

**rts** - returns from subroutine

**stop** - stops the program

## The Two Pass Algorithm

First there is the pre assembler phase that goes through the .as file and interprets all the macros present in it.

then the assembler receives input in .am file, it has to go over the input 2 times. The reason for that is the references to instructions which still has unknown addresses during first pass.

The assembler has linked list representing the Image Code (.ob file) and another 2 linked lists representing the Macro table and Symbol Table .

Symbol Table - will be updated during first pass with the addresses of the instructions.

Image Code - represents machine code of all the command sentences.

Using an instruction counter, each instruction is being added to the counter, ensuring the next instruction will be assigned to free memory space.
  
At first pass, the symbols (labels) in the program are recognized and are assigned a unique number representation in the memory.

At second pass, using the symbol values, the machine code is built. The instruction's addresses are updated from the symbol table.

If any errors are found during first pass (and second), the program will continue to the next file.
