# Developer Log (DEVLOG.md)
## Monopoly Board Simulator (Spring 2026)

Minimum **6 entries** required.

Each entry must document learning and reasoning. Fabricated bugs are not expected.

---

## Allowed Entry Types
Each entry may be one of the following:

1) **Bug Fix Entry**
- The issue encountered.
- Error messages or symptoms.
- Attempts made.
- Final resolution.

2) **Edge Case / Testing Entry**
- A failure discovered through testing.
- The specific input/state that caused it.
- The change you made to handle it correctly.

3) **Engineering Decision Entry (up to 2 allowed)**
- A design decision you made.
- An alternative approach you considered.
- Why you chose one approach over another (tradeoffs).

---

### Entry 1
**Date:** 2026-02-24  
**Entry Type:** Engineering Decision  
**Task worked on:** Implementing addSpace() for the circular linked list board.   
**Issue or decision:** While implementing the insertion logic for the circular linked list, I needed to decide how to maintain the circular structure when adding nodes to the board. The template suggested updating the tail pointer and then linking the tail back to the head node.  
**Error message / symptom (if applicable):** N/A  
**What I tried:**   I considered two approaches: First, I thought about just setting newNode->nextNode = headNode before updating the tail. Second, I thought about following the template's instructions exactly by updating tailNode->nextNode after moving the tail pointer.  
**Fix / resolution (or final decision):** I followed the template’s approach to ensure I accurately followed Manju's expected implementation. After inserting the new node, I updated tailNode->nextNode = headNode to keep the circular linked list properly circular.     
**Commit(s):** Day 3: Implemented addSpace with circular insertion and MAX_SPACES capacity enforcement, following the directions is helpful..      

---

### Entry 2
**Date:** 2026-02-27  
**Entry Type:** Edge Case / Testing  
**Task worked on:** Implementing traversal-based player movement (movePlayer function)  
**Issue or decision:** While testing the movePlayer function, I considered how the program should behave when the player moves across the boundary between the last node (tail) and the first node (head / GO). Because the board is implemented as a circular linked list, I assumed this transition happens automatically through pointer traversal, but the program still needs to correctly detect when the player passes GO.     
**Error message / symptom (if applicable):** There were no compiler errors, but this edge case could lead to incorrect passGoCount tracking if the transition from tail to head is not detected properly.  
**What I tried:** I reviewed how the traversal occurs when the "playerNode" advances through the circular linked list. Since the tail node always links back to the head node, I checked what happens when the player moves forward while currently positioned on the tail node.     
**Fix / resolution (or final decision):** I implemented a check inside the movement loop that detects when playerNode is equal to tailNode before advancing to the next node. If the player moves forward from the tail node, the next node will be the head node (GO), meaning the player has passed GO. In this scenario the program increments "passGoCount" before moving the player pointer forward.     
**Commit(s):** Day 5: Implemented traversal-based player movement with passGo detection    

---

### Entry 3
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**  

---

### Entry 4
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**  

---

### Entry 5
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**  

---

### Entry 6
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**  
