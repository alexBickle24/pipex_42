
# pipex_42 🚰

**Pipes, redirections, IPC, process management, global variables, parsing, and more. This project aims to simulate the behavior of Shell pipes using C. The goal of the project... to become a reliable plumber! 🧑‍🔧**

**pipex_42** is a C project focused on simulating the behavior of shell pipes. It includes topics such as pipes, redirections, inter-process communication (IPC), process management, global variables, parsing, and more. The main objective is to reliably reproduce shell pipe functionalities in C—because every good developer needs to be a reliable plumber!

## Features

- Implementation of pipe and redirection mechanisms in C
- Process creation and management
- Inter-process communication (IPC)
- Shell command parsing and execution
- **Bonus:** Multiple commands and "here document" support

## Requirements

- GCC or compatible C compiler
- Unix-like operating system (Linux, macOS)
- Basic knowledge of Shell and C programming

## Installation

Clone the repository:
```sh
git clone https://github.com/alexBickle24/pipex_42.git
cd pipex_42
```

Compile the project:
```sh
make
```

## Usage

### Basic Usage

Execute the program with the following arguments:
```sh
./pipex infile cmd1 cmd2 outfile
```
This command will:
- Take input from `infile`  
- Execute `cmd1`, pipe its output to `cmd2`  
- Write the final output to `outfile`

### Bonus Features 🎉

If you build and use the **bonus version**, you unlock extra functionalities:

#### 1. Multiple Commands

Chain more than two commands, just like in a real shell pipeline:
```sh
./pipex infile cmd1 cmd2 cmd3 ... cmdN outfile
```
This will pipe the output through each command in sequence, from `infile` to `outfile`.

#### 2. Here Document ("here_doc") 📑

Support for “here_doc” syntax, allowing you to provide input directly in the terminal:
```sh
./pipex here_doc LIMITER cmd1 cmd2 ... cmdN outfile
```
This will:
- Read input from the terminal until the `LIMITER` word is encountered
- Process the commands in sequence
- Write the result to `outfile`

## Example

```sh
./pipex infile "grep hello" "wc -l" outfile
```
Or, using bonus features:
```sh
./pipex here_doc END "cat" "wc -l" outfile
```
Then type your input, and finish with `END` on a new line.

## Author

alexBickle24  
[GitHub Profile](https://github.com/alexBickle24)

---

Let me know if you’d like to adjust the emoji placement or add more examples!