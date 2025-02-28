# 143B Virtual Memory
Project 2 for CS 143B class.

## Requirements
- at least cmake 3.20.0
- GCC

## How to Run (FOR GRADERS)
```{bash}
bash compile.sh
./build/main init-dp.txt < input-dp.txt > output-dp.txt
```
If you want to import your own text files to test then follow this:
```{bash}
./build/main [init-file] < [input-file] > [output-file]
```

## How to Run
Build cmake depending on the operating system
```{bash}
cmake --preset linux
cmake --preset windows
```

To build binary, enter:
```{bash}
cmake --build build --target main
```

To execute enter:
```{bash}
./build/main [init-file] < [input-file] > [output-file]
```
- replace [init-file] with init file's path
- replace [input-file] with input file's path
- replace [output-file] with output file's path
