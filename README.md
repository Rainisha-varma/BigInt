# BigInt Operations in C

BigInt is a C program that implements basic arithmetic operations (addition, subtraction, and multiplication) on large integers using a custom data structure called `BigInt`. The `BigInt` structure consists of an array to store digits, along with attributes for size and sign. The operations are performed digit by digit, with appropriate handling for sign and carry. 
## Usage

To use the program, simply compile the provided source code and run the executable. Upon execution, the program prompts the user to choose one of the following operations:
1. Addition of BigInt numbers
2. Subtraction of BigInt numbers
3. Multiplication of BigInt numbers

After selecting an operation, the user is prompted to input two large integers. The program then performs the chosen operation and outputs the result.

## Features

- Supports addition, subtraction, and multiplication of 1024 bit integers.
- Handles both positive and negative integers.
- Dynamically allocates memory for storing large integers, ensuring efficient memory usage.
- Provides a simple command-line interface for user interaction.
- Easily extendable for additional arithmetic operations or integration into larger projects.
