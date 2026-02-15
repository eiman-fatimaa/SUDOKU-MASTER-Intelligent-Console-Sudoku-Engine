# Sudoku Master

### A Guided Sudoku Learning Engine in C++

Most Sudoku projects focus on solving the puzzle.

Sudoku Master focuses on helping the player solve it better.

This is a console-based intelligent Sudoku system built in C++ that combines puzzle generation, guided gameplay feedback, performance scoring, and structured interaction to create a learning-driven experience instead of simple trial-and-error play.

---

## Why This Is Not Just Another Sudoku Solver

In Sudoku, a move can satisfy all rules and still be wrong.

Beginners often build incorrect logic without realizing it.

Sudoku Master introduces a **color-based feedback layer** that evaluates how close a move is to the actual solution, even when the move is technically valid.

| Feedback | Meaning                |
| -------- | ---------------------- |
| Green    | Correct placement      |
| Yellow   | Close to correct value |
| Red      | Incorrect direction    |

This allows players to understand their logical progress without directly revealing answers.

Instead of rejecting mistakes, the system guides improvement.

---
## Project Demo

[![Watch the Demo](https://img.youtube.com/vi/5mbaCIJDjoY.jpg)](https://www.youtube.com/watch?v=5mbaCIJDjoY)


## Key Features

### Intelligent Gameplay Feedback

Moves are analyzed relative to the solution.

Players receive insight into correctness direction rather than simple rule validation.

---

### Beginner-Oriented Hint Philosophy

Hints are designed to support learning, not replace thinking.

The system helps players avoid progressing with flawed logic.

---

### Dynamic Puzzle Generation

Each session generates a new puzzle using recursive backtracking with randomized placement.

Difficulty levels adjust challenge by removing different numbers of cells:

| Level  | Cells Removed | Lives |
| ------ | ------------- | ----- |
| Easy   | 30            | 100   |
| Medium | 40            | 35    |
| Hard   | 55            | 20    |

---

### Structured Console Interface

Special attention was given to terminal readability:

* Symmetrical grid layout
* Subgrid separation
* Consistent alignment
* Color-based visual feedback

---

### Performance-Based Scoring

The scoring system evaluates solving quality using:

* Time taken
* Invalid moves
* Hint usage
* Logical accuracy

Completion alone does not guarantee a high score.

---

### Timer-Based Gameplay

Real-time tracking evaluates performance and introduces penalties for slow solving.

---

### User Authentication

Includes file-based:

* Signup
* Login
* Attempt tracking

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

## Technical Concepts Used

* Recursive Backtracking
* Constraint Validation
* Randomized Generation
* ANSI Color Rendering
* File Handling
* State Tracking
* Input Validation
* Time-Based Evaluation

---

## Repository Includes

* Source Code
* System Flowchart
* Gameplay Demo Video

---

## Objective

This project explores how algorithmic systems can move beyond solving problems to guiding human decision making.

Sudoku Master focuses on improving the solving process rather than simply producing solutions.


