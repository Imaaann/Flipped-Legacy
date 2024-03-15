# Flipped Legacy Game (W.I.P)

## Notes on how to run:
    - We are using SDL2 which I would recommend downloading on your computer if this doesnt work off the bat
    - as for the makefile you need to follow these steps:

### How to install and use makefile:
    **makefiles are used to shorten long commands into simple aliases**
    - Install the chocolatey package manager https://chocolatey.org/install
    - On a adminstative console (powershell) run the command `choco install make`
    **Current makefile commands**:
    - make build (or just make) : builds all the c source files in the src folder into a .exe
    - make testBuild : builds the c file called `test.c` into `test.exe`
    - make run: runs `game.exe`
    - make runTest: runs `test.exe`
