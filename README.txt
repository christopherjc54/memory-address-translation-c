Written by Christopher Coutinho.

To compile and run on LINUX:
    make all
Open "output/part3-console.txt" to see output (results saved in binary in "output/part3-out").
To deleted all generated files:
    make clean


To compile and run on WINDOWS:
Prerequisites: install MinGW and add to PATH
    [as admin, run only once] mklink C:\MinGW\bin\make.exe C:\MinGW\bin\mingw32-make.exe
    make -f .\Makefile-Windows all
Open "output/part3-console.txt" to see output (results saved in binary in "output/part3-out").
To deleted all generated files:
    make -f .\Makefile-Windows clean
IMPORTANT NOTE: MD5 sum for part1 matches Windows sum, but part2 and part3 have Linux MD5 sum because my implementation skips empty addresses.