# Sudoku Master

### A Guided Sudoku Learning Engine in C++
Sudoku Master is a console-based interactive Sudoku game developed in C++ 
It automatically generates a valid 9×9 Sudoku puzzle using a backtracking algorithm and allows users to solve it through coordinate-based input. 
The system validates every move, prevents illegal changes, provides color-coded feedback, and determines win or loss conditions based on correctness, time, score, and lives.

This project is not just another Sudoku solver. It is a learning-driven gameplay engine designed to guide beginners and improve logical reasoning through visual feedback and scoring.
---
## Project Demo
Watch full video demo:

[![Sudoku Master Demo](https://img.youtube.com/vi/5mbaCIJDjoY/hqdefault.jpg)](https://www.youtube.com/watch?v=5mbaCIJDjoY)
---
## Why This Project Exists
Traditional Sudoku puzzles are solved manually, which can be time-consuming and error-prone, especially for beginners. 
Players often struggle to detect rule violations without external help.

Sudoku Master addresses these challenges by:
- Generating unique puzzles automatically for different difficulty levels.
- Validating every move against Sudoku rules.
- Preventing edits to fixed cells.
- Providing hints and color-coded feedback.
- Verifying the final solution using an automated solver
---
## Key Features
1. **Automatic puzzle generation** using backtracking.
2. **Random removal of cells** to create playable puzzles.
3. **Difficulty levels** (Easy, Medium, Hard) with adjusted removed cells and lives.
4. **Coordinate-based input** for row, column, and value.
5. **Locked cells** cannot be edited.
6. **Rule validation** for rows, columns, and 3×3 subgrids.
7. **Color-coded feedback**:
   * Green → Correct placement
   * Orange → Close (±1 or ±2)
   * Red → Far from correct value
8. Overwrite previous entries (except locked cells).
9. **Hint system** reveals a random empty cell with score penalty.
10. **Timer and scoring system** with penalties for slow play, invalid moves, and hint usage.
11. **User authentication** with login, signup, and attempt tracking.
12. **Game win/loss detection** with final statistics display.
---
## Programming Concepts Used:
* Loops for grid display and validation
* Conditional statements for rule enforcement and feedback
* Functions for modular design
* 2D arrays for puzzle, solution, and user grid
* Backtracking algorithm for puzzle generation
* Random number generation
* File handling for user authentication
* Console formatting and ANSI color codes
* Input validation
---

## System Design and Implementation

**Sudoku Generation:** `generateFullGrid()` fills the grid using `isSafe()`
**Puzzle Creation:** Cells removed randomly based on difficulty level
**User Interaction:** Moves entered as row, column, and value
**Invalid Input Handling:** Immediate rejection and feedback
**Overwrite Handling:** Users can update their entries; locked cells cannot be modified
**Scoring & Timer:**

* Base score 1000
* Penalties for invalid moves, hints, and time exceeding 3 minutes
* Score increments for valid moves

---

## Controls

| Input           | Action       |
| --------------- | ------------ |
| `row col value` | Place number |
| `h`             | Reveal hint  |
| `q`             | Quit game    |

Example:

```
2 5 7
```

---

## Expected Outcome

Upon execution, the user:

* Logs in or signs up successfully
* Selects a difficulty level
* Sees a **neatly formatted Sudoku grid**
* Receives **real-time validation and color-coded feedback**
* Uses hints strategically
* Completes the puzzle or reaches a game-over condition
* Receives a final score and completion message

---

## Testing and Validation

The system has been tested for:

* Input validation (invalid row, column, or value)
* Non-numeric input handling
* Rule violation detection
* Locked cell protection
* Overwriting user entries
* Hint system functionality
* Difficulty level correctness
* Timer and scoring accuracy
* Game win and loss conditions
* User authentication and attempt tracking
---

## Additional Materials

* [Flowchart](docs/flowchart.pdf) — System design and logic flow
* [Project PPT](docs/project_demo.pptx) — Contributions, screenshots, and feature overview

---

## Objective

Sudoku Master fulfills its goal of creating a **user-friendly, interactive Sudoku system** that handles errors effectively while teaching logical reasoning.

It demonstrates strong knowledge of **C++ fundamentals, problem solving techniques, and modular programming**. The **scoring, color feedback, hints, and authentication** enhance usability and learning value, making it more than just a puzzle solver.
