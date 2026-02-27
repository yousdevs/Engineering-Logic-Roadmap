# Milestone Project: Bank System (Console)

This is a procedural C++ console application built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap) (Course 7). It implements a basic Bank Client Management System, focusing on state-driven UI flow, raw string manipulation, and file-based data persistence.

## Overview

The goal of this project was to build a CRUD application from scratch without relying on heavy external libraries or an SQL database. It relies heavily on custom input validation, struct-based data modeling, and reading/writing delimited text files to maintain state across sessions.

## Features

* **CRUD Operations:** Full support for adding, listing, updating, and deleting client records.
* **Data Persistence:** Automatically saves and loads data from `clients.txt`.
* **Input Validation:** Prevents crashes from invalid data types and handles buffer clearing.
* **Duplicate Prevention:** Checks for existing Account IDs during the creation process.
* **Formatted UI:** Uses `iomanip` for structured, tabular data display in the console.
* **Transaction Management:** Support for deposits, withdrawals, and calculating total bank balances.
* **Transaction Validation:** Logic to prevent negative deposits or withdrawals that exceed the current balance.
* **Direct Memory Updates:** Uses pointer-based search results to modify client data directly in memory before persisting to disk.

## Core Mechanics

* **State Machine UI:** Instead of deep, recursive function calls to handle menus, the application loop is controlled by a state machine using the `enScreen` enum. The `runApp()` function dictates screen transitions based on the return values of the current view, keeping the call stack flat.
* **File Persistence:** Data is serialized into a flat text file (`clients.txt`) using a custom delimiter (`#//#`). The project includes custom `split`, `serializeClient`, and `deserializeClient` functions to parse this data back into memory.
* **Soft Deletions:** Deleting a client does not immediately erase them from the vector or trigger a file rewrite. Instead, their `enClientStatus` is toggled from `ACTIVE` to `DELETED`. The file is only updated with active clients upon screen transitions, preventing unnecessary disk I/O.
* **Input Sanitization:** Built-in safeguards handle whitespace buffer clearing (`std::ws`) and strict type-checking loops (e.g., ensuring a user inputs a valid integer instead of a string) to prevent console infinite-loop crashes.
* **Pointer-Based Mutation:** The search logic was refactored to return a memory address (`stClient*`). This allows transaction screens (Deposit/Withdraw) to modify the client's balance directly in the central vector without redundant searches or passing large objects by value.
* **Transactional Logic:** Implemented validation layers within the `deposit` and `withdraw` functions. These return a `stTransaction` result that captures success status and failure reasons (e.g., insufficient funds), which the UI then uses to provide specific feedback.
* **Nested State Navigation:** The state machine now handles sub-menus (Transactions Menu). The `runApp()` loop remains the single point of control, ensuring that even with nested menus, the application never creates deep recursive calls.

## Data Structures

The main entity is the `stClient` struct:

```cpp
struct stClient {
    std::string accountID;
    std::string pinCode;
    std::string fullName;
    std::string phoneNumber;
    double accountBalance;
    enClientStatus status;
};

```

## How to Run

Since this is standard C++, you can compile it using `g++` or any standard compiler.

1. Clone the repository and navigate to this project's directory.
2. Compile the source code:
```bash
g++ -std=c++11 main.cpp -o bank_system

```


3. Run the executable:
```bash
./bank_system

```



**Note:** The application will generate a `clients.txt` file in the same directory upon first writing data. Ensure the directory has proper write permissions.
