# Rock, Paper, Scissors (Console Edition)

A clean, modular implementation of the classic Rock, Paper, Scissors game. This project focuses on structured data using `enums` and `structs`, robust input validation, and dynamic console feedback.

## The Gist

You vs. The Machine. You pick the number of rounds (up to 10), and the computer generates random moves. The console changes color based on the result of each round—**Green** for victory, **Red** for defeat, and **Yellow** for a draw.

---

## Screenshot Placeholder

![Game Screenshot](./screenshot.png)

---

## How to Run

This project is part of a monorepo structure. You can open it via the main solution or the project-specific solution.

### 1. The Monorepo Way

Open the root solution file to see all projects in the workspace:
`./root_monorepo.slnx`

### 2. The Project Way

Navigate directly to the project folder:
`projects/05-l2-p1-rock-paper-scissors/`

From here, you can open:
`05-l2-p1-rock-paper-scissors.slnx`

**Prerequisites:** * A C++ compiler (MSVC recommended for the `system("color")` features).

* Windows OS (required for the specific console color and screen clearing commands).

---

## What I Learned (The Hard Way)

Building a simple game is one thing; making it robust is another. Here’s what this project drilled into my head:

* **Recursion is a Trap:** I originally had the game loop calling itself to "play again." I learned that this is a great way to blow up the stack. Switching to a `do-while` loop in `main` kept the memory flat and safe.
* **The Power of Structs:** Bundling round info (`strRound`) and game results (`strGameReport`) made passing data between functions significantly cleaner than passing 5+ individual variables.
* **Console State Management:** Dealing with Windows `system` commands taught me how to manipulate terminal attributes. I had to be careful with the hex indices (e.g., `color 07`) to ensure the background didn't overwrite the text color.
* **Validation is Key:** Never trust user input. The `readPositiveNumberInRange` function ensures the game doesn't crash just because someone typed "99" in a 3-choice menu.

---


## Credits & References

* **Course Material:** This project was developed as part of the C++ curriculum on [ProgrammingAdvices.com](https://programmingadvices.com).
* **Instructor:** Special thanks to Dr. Mohammed Abu-Hadhoud for the structured logic and problem-solving methodologies.

---