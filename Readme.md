Here is a README draft in English for your project based on its description:

---

# pipex_42

Simulates the behavior of Shell pipes using C. This project covers topics such as pipes, redirections, IPC (Inter-Process Communication), process management, global variables, and parsing. The objective is to reliably reproduce the functionalities of pipes in Unix-like shells.

## Features

- Implementation of pipe and redirection mechanisms
- Handling of process creation and management
- Inter-process communication (IPC)
- Parsing and execution of shell commands

## Requirements

- GCC or another C compiler
- Unix-like operating system (Linux, macOS)
- Basic knowledge of shell and C programming

## Getting Started

Clone the repository:

```bash
git clone https://github.com/alexBickle24/pipex_42.git
cd pipex_42
```

Compile the project:

```bash
make
```

## Usage

Run the executable with the required arguments. Example:

```bash
./pipex infile cmd1 cmd2 outfile
```

This will execute `cmd1` with input from `infile`, pipe the output to `cmd2`, and write the final output to `outfile`.

## Author

alexBickle24

---

Feel free to customize or expand this README as needed!