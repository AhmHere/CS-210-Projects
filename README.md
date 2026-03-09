# CS210 Programming Assignment
## Monopoly Board Simulator (Spring 2026)

### Overview
In this assignment, you will implement a Monopoly-style game board using a **circular linked list**. Unlike previous offerings, the circular structure is not just for storage, it is the engine for traversal and gameplay. Your program will simulate a player moving around a fixed-size Monopoly board, passing GO, and interacting with board spaces through pointer-based movement.

### This assignment emphasizes
- Correct implementation of a circular linked list.
- Careful pointer management under constraints.
- Traversal-based logic instead of index-based shortcuts.
- Professional development practices using GitHub.

---

## Board Constraints
- The Monopoly board has a maximum of **40 spaces**.
- Your linked list must **never exceed 40 nodes**.
- Once the board reaches capacity, additional insertions must be rejected cleanly **without corrupting the list**.

---

## Board Construction Policy (Read This Carefully)
Spaces are added during a **board construction phase**, before gameplay begins.

How you build the board is intentionally **left to you**. You may:
- Define each space manually in code.
- Load spaces from a file.
- Generate spaces programmatically (including random generation).

There is **no single required way** to construct the board. The requirement is that your implementation:
- Supports adding spaces using the provided insertion functions.
- Correctly enforces the 40-space limit.
- Preserves circular integrity regardless of construction strategy.

---

## How to Build and Run
### Build
(Write your build instructions here.)
Example:
- `g++ -std=c++17 monopoly_board_S26_template.cpp -o monopoly_board`

### Run
- `./monopoly_board`

---

## Core Requirements (40 points)
### Core A: Add a Space with Capacity Enforcement (10 points)
**Function:** `addSpace(...)`  
**Description:** Adds a new node to the tail, maintains circular structure, enforces max size 40, returns success/failure beyond capacity.

### Core B: Add Multiple Spaces at Once (10 points)
**Function:** `addMany(...)`  
**Description:** Adds spaces sequentially, stops exactly at capacity, returns how many were added, and does not corrupt pointers.

### Core C: Traversal-Based Player Movement (10 points)
**Function:** `movePlayer(int n)`  
**Description:** Moves a player cursor forward by `n` steps node-by-node, wraps around, and tracks how many times the player passes GO.

### Core D: Controlled Board Display (10 points)
**Function:** `printFromPlayer(int count)`  
**Description:** Prints a fixed number of spaces starting from the player (or a starting point if you design it that way) with a safe stop condition (no infinite loops).

---

## Playable Simulation Requirement
Your `main.cpp` must demonstrate a simple playable traversal loop:
- Build the board (up to 40 spaces).
- Place a player at the starting space.
- Simulate multiple turns:
  - Roll a dice (2–12).
  - Move the player.
  - Print the space landed on.
  - Track how many times the player passes GO.

This is **not** a full Monopoly game. The goal is to prove traversal correctness.

---

## Advanced Requirements (20 points total)
Choose **one** of the following paths.

### Option A: Two Level 1 Features (10 points each)
1) `removeByName(string name)`
- Deletes the first matching space.
- Must correctly handle:
  - deleting the head node,
  - deleting the only-node list,
  - deleting the tail node.

2) `findByColor(string color)`
- Returns a `vector<string>` of matching space names or prints matching spaces.
- Must traverse the ring **exactly once** using a correct stop condition.

### Option B: One Level 2 Feature (20 points)
**Mirror the Board (Circular List Reversal)**  
Implement a function that reverses the traversal direction of the circular linked list.

Required behavior:
- Reverses the `next` links of all nodes.
- Preserves circular structure (the list must still loop correctly).
- Correctly handles:
  - empty board,
  - single-node board.
- The player cursor must remain on the **same logical space** after reversal.

---

## Edge Case Handling (20 points)
Your program must correctly handle the following:
- Operations on an empty board.
- A single-node circular list.
- Deleting the head node.
- Deleting the tail node.
- Adding multiple spaces up to exactly 40 without corruption.

---

## GitHub & Process Requirements (20 points)
### Repository
- Each student must use their **own public GitHub repository**.
- The Canvas submission must be a link to the public repo.

### Commit History
- Minimum **10 commits**.
- Commits must be spread over **at least 14 days**.
- Commits made in one sitting will not receive full credit.

### Developer Log
- Include a `DEVLOG.md` file.
- Minimum **6 entries**.

### README
Your `README.md` must include:
- Build and run instructions.
- Description of data structures used.
- A complete list of functions with short explanations.
- Explanation of traversal and movement logic.
- Explicit mention of the **40-space board limit**.

---

## Submission
- Submit the GitHub repository link on Canvas.
- No zip files.
- Late submissions follow standard course policy.

---

## Notes
This assignment is about thinking in pointers, not arrays. If your logic depends on indexing shortcuts, you are solving the wrong problem. Treat the board like a ring, because that is exactly what it is.
My own notes:
---

# Implementation Details

## Data Structures Used

### MonopolySpace
Represents a single space on the Monopoly board.

Properties:
- `propertyName`
- `propertyColor`
- `value`
- `rent`

Methods:
- `print()` – displays the space information
- `isEqual()` – compares two spaces by name


### Node<T>
Template class representing a node in the linked list.

Properties:
- `data` – stores the space information
- `nextNode` – pointer to the next node in the list


### CircularLinkedList<T>
Stores the Monopoly board as a circular linked list.

Important members:
- `headNode` – first node in the list
- `tailNode` – last node in the list
- `playerNode` – tracks the player's current position
- `nodeCount` – number of spaces in the board
- `passGoCount` – tracks how many times GO has been passed


---

# Functions Implemented

### Core Functions

`addSpace(T value)`
Adds a new space to the board while enforcing the **40-space maximum limit**.

`addMany(vector<T>)`
Adds multiple spaces sequentially until the board reaches capacity.

`movePlayer(int steps)`
Moves the player around the circular board based on a dice roll and tracks when GO is passed.

`printFromPlayer(int count)`
Prints a fixed number of spaces starting from the player's current position.

`printBoardOnce()`
Traverses the circular list exactly once and prints all board spaces.


---

### Advanced Option A Features

`removeByName(string name)`
Deletes the first node matching the given property name while maintaining circular list integrity.

Handles:
- deleting the head node
- deleting the tail node
- deleting the only node in the list
- deleting nodes in the middle

`findByColor(string color)`
Traverses the board once and returns all property names that match the specified color.


---

### Helper Functions

`countSpaces()`
Traverses the circular list once and counts the number of spaces without relying on the stored node count.

`clear()`
Deletes all nodes safely by breaking the circular link before performing normal list deletion.


---

# Traversal and Player Movement Logic

The Monopoly board is implemented as a **circular linked list**, meaning the final node points back to the head node. This allows the player to continuously move around the board without reaching a null pointer.

Player movement is implemented using pointer traversal. The `movePlayer()` function advances the player node one space at a time for each step rolled on the dice.

When the player moves from the tail node back to the head node, the program increments the `passGoCount`, representing passing GO.


---

# Board Size Constraint

The Monopoly board has a maximum size of **40 spaces**. This is enforced in the `addSpace()` function. If the board already contains 40 nodes, additional insertions are rejected and the linked list remains unchanged.

This prevents corruption of the circular list structure.