# Milestone Project: ATM System (Console)

This project is a small C++ console application built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap).  
It simulates a simple ATM workflow with login, balance inquiry, withdrawals, and deposits while persisting client data to a text file.

The focus of this project was not UI complexity but practicing clean procedural structure, screen navigation, and separating domain logic from application services.

## Overview

The ATM system loads clients from a text file into memory at startup, allows the user to perform basic banking operations, and writes the updated state back to disk when transactions occur.

Instead of deeply nested menu calls, the program uses a simple router-style screen system where each screen returns the next screen to display. This keeps the program flow predictable and avoids recursive menu calls.

## Features

* **Authentication:** Login using account ID and PIN.
* **Balance Inquiry:** Displays the current account balance.
* **Quick Withdraw:** Predefined withdrawal amounts (e.g., $20, $50, $100).
* **Normal Withdraw:** Custom withdrawal amount entered by the user.
* **Deposit:** Add money to the account with validation.
* **Transaction Validation:** Prevents negative amounts, invalid steps, and withdrawals exceeding the balance.
* **File Persistence:** Client data is loaded from and written back to `clients.txt`.
* **Input Validation:** Handles invalid console input safely.
* **State-Based Navigation:** Screens return the next screen instead of calling each other directly.

## Core Mechanics

* **Screen Router:**  
  The application loop is controlled by a simple router table that maps a `Screen` enum value to its corresponding handler function. Each screen function returns the next screen, allowing the program to move between login, menu, and transaction views.

* **Application Context:**  
  A central `AppContext` struct carries shared state across the program, including the loaded clients, current logged-in client, and file configuration.

* **Domain vs Service Logic:**  
  Transaction logic is separated into two layers:
  
  - **Domain functions** (`executeWithdrawal`, `executeDeposit`) handle validation and balance updates.
  - **Service functions** (`withdraw`, `deposit`) coordinate domain execution and file persistence.

* **File Persistence:**  
  Client data is stored in a flat text file using a custom delimiter (`#//#`).  
  The application serializes and deserializes records manually using helper functions.

* **Money Representation:**  
  Balances are stored as integer cents (`long long`) instead of floating point values to avoid precision errors during financial calculations.

## Data Structures

The system revolves around a small set of structures that hold the application state and transaction results.

```cpp
struct Client {
    std::string accountID;
    std::string pinCode;
    std::string name;
    std::string phoneNumber;
    long long balanceCents;
};

struct Transaction {
    TransactionType type;
    long long amountInCents;
    std::string validationError;
    bool success;
};

struct AppContext {
    Client* currentClient;
    std::vector<Client> clients;
    std::string clientFilePath;
    std::string delim;
};
```

## How to Build and Run

This project uses **CMake**, which allows building the project in a separate directory without polluting the source files.

### 1. Clone the Repository

```
git clone https://github.com/yousdevs/Engineering-Logic-Roadmap.git
cd Engineering-Logic-Roadmap
```

### 2. Configure the Build

```
cmake -B build
```

### 3. Build the ATM Project

```
cmake --build build --target 08-l4-p2-atm-sys
```

### 4. Run the Executable

From the build directory:

```
./build/projects/08-l4-p2-atm-sys/atm-system
```

(On Windows it will be `atm-system.exe`)

## Default Login

You can log in using the sample account:

```
Account ID: 1
PIN: 1234
```

The data is loaded from `clients.txt`.  
If the file is modified or new transactions occur, the updated client data will be written back to the file.

---

This project was primarily an exercise in structuring procedural C++ programs, managing state without global variables, and implementing a simple navigation system for console applications.