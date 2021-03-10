# Sudoku Verifier Program

This is a program in c that verifies whether a given sudoku game is solver or not. <br />

It uses 27 worker threads to check each of the sudoku lines or blocks, and if all threads have a solved block, the program returns True, as the sudoku is solved. <br />

The sudoku bidimimensional array is local to the main() function, so this code showcases how to pass references carefully of all the rows, columns and inner grids of the sudoku array. <br />

## Usage

1. Download this repo and store it in your local machine.
2. Open a terminal and move to the folder's root directory.
3. Compile `sudoku-verifier.c` file by typing:

```bash
$ gcc sudoku-verifier.c -o sudoku -lpthread
```
4. Run the executable created in the previous step by typing:

```bash
$ /.sudoku b.txt
```

![image](https://github.com/the-other-mariana/sudoku-verifier/blob/master/res/terminal.png?raw=true)

