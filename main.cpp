#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

static const int MAX_SPACES = 40;

// -------------------------------
// Data class (NOT a struct)
// -------------------------------
class MonopolySpace {
public:
    string propertyName;
    string propertyColor;
    int value;
    int rent;

    MonopolySpace() {
        // TODO: define default constructor (recommended)
        propertyName = "";
        propertyColor = "";
        value = 0;
        rent = 0;
    }

    MonopolySpace(string propertyName, string propertyColor, int value, int rent) {
        /* TODO: Define overloaded constructor here */
        this->propertyName = propertyName;
        this->propertyColor = propertyColor;
        this->value = value;
        this->rent = rent;
    }

    bool isEqual(MonopolySpace other) {
        /* TODO: Define isEqual here (compare by name is fine if you enforce uniqueness) */
        return propertyName == other.propertyName;
    }

    void print() {
        /* TODO: Define print here */
        // Example style:
        // cout << propertyName << " | " << propertyColor << " | $" << value << " | Rent " << rent;
        cout << propertyName << " | "
             << propertyColor << " | $"
             << value << " | Rent "
             << rent << endl;
    }
};

// -------------------------------
// Template Node class (NOT a struct)
// -------------------------------
template <typename T>
class Node {
public:
    T data;
    Node<T>* nextNode;

    Node(T value) {
        data = value;
        nextNode = nullptr;
    }
};

// -------------------------------
// Template Circular Linked List class
// Spring 2026 version: traversable board
// -------------------------------
template <typename T>
class CircularLinkedList {
private:
    Node<T>* headNode;
    Node<T>* tailNode;

    // player cursor for traversal-based gameplay
    Node<T>* playerNode;

    int nodeCount;
    int passGoCount;

public:
    CircularLinkedList() {
        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;

        nodeCount = 0;
        passGoCount = 0;
    }

    // -------------------------------
    // Board Construction Policy (Reminder)
    // -------------------------------
    // Spaces are added during board construction BEFORE gameplay.
    // You choose how to construct the board:
    // - hardcode spaces, read from file, or generate programmatically
    // The only non-negotiable requirement:
    // - enforce MAX_SPACES
    // - maintain circular integrity
    // -------------------------------

    // -------------------------------
    // Core A: Add a Space with Capacity Enforcement
    // -------------------------------
    bool addSpace(T value) {
        // TODO:
        // - If nodeCount == MAX_SPACES return false (do not corrupt list)
        // capacity check
        if (nodeCount == MAX_SPACES) {
            return false;
        }
        // - Create new node
        Node<T>* newNode = new Node<T>(value);
        // - If empty list: head=tail=player=new, new->next=head
        if (headNode == nullptr) {
            headNode = newNode;
            tailNode = newNode;
            playerNode = newNode;

            newNode->nextNode = headNode;
        }
        else { // - Else: tail->next=new, tail=new, tail->next=head
            // insert at tail
            tailNode->nextNode = newNode;
            tailNode = newNode;

            tailNode->nextNode = headNode;
        }
        // - nodeCount++
        nodeCount++;
        return true;
    }

    // -------------------------------
    // Core B: Add Multiple Spaces at Once
    // -------------------------------
    int addMany(vector<T> values) {
        // TODO:
        // - Add sequentially until full
        int addedCount = 0;

        for (T value : values) {

            if (!addSpace(value)) {
                break;  // - Stop exactly when you reach MAX_SPACES
            }
        // - Return number successfully added
            addedCount++;
        }
        // - Do not corrupt pointers if capacity is exceeded
        return addedCount;
    }

    // -------------------------------
    // Core C: Traversal-Based Player Movement
    // -------------------------------
    void movePlayer(int steps) {
        // TODO:
        // - Must handle empty list safely
        if (playerNode == nullptr) {
            cout << "Board is empty." << endl;
            return;
        }
        // - Wrap naturally because list is circular
        for (int i = 0; i < steps; i++) {
            // - Move playerNode forward 'steps' times, node-by-node
            // - Detect and track passing GO:
            if (playerNode == tailNode) {
                passGoCount++;
            }
            //   increment passGoCount when a move crosses from tail back to head
            playerNode = playerNode->nextNode;
        }

        cout << "Player landed on: ";
        playerNode->data.print();
    }

    int getPassGoCount() {
        return passGoCount;
    }

    // -------------------------------
    // Core D: Controlled Board Display
    // -------------------------------
    void printFromPlayer(int count) {
        // TODO:
        // - Must handle empty list
        // - Output must be deterministic and readable
        if (playerNode == nullptr) {
            cout << "Board is empty." << endl;
            return;
        }
        // - Print exactly 'count' nodes starting from playerNode
        Node<T>* current = playerNode;
        // - Must not infinite loop
        for (int i = 0; i < count; i++) {

            current->data.print();
            current = current->nextNode;
        }
    }

    // Optional helper: print full board once (one full cycle)
    void printBoardOnce() {
        // TODO:
        // - Traverse exactly one full cycle and print each node
        if (headNode == nullptr) {
            cout << "Board is empty." << endl;
            return;
        }

        Node<T>* current = headNode;

        do {
            current->data.print();
            current = current->nextNode;
        } while (current != headNode);
    }

    // -------------------------------
    // Advanced Option A (Level 1): removeByName
    // -------------------------------
    bool removeByName(string name) {
        // TODO:
        if (headNode == nullptr) {
            return false;
        }
        // - Delete FIRST matching node
        Node<T>* current = headNode;
        Node<T>* previous = tailNode;

        do {

            if (current->data.propertyName == name) {

                //   - deleting the only-node list
                if (current == headNode && current == tailNode) {
                    headNode = nullptr;
                    tailNode = nullptr;
                    playerNode = nullptr;
                }

                //   - deleting head
                else if (current == headNode) {
                    headNode = headNode->nextNode;
                    // - Maintain circular link tail->next=head
                    tailNode->nextNode = headNode;
                }

                //   - deleting tail
                else if (current == tailNode) {
                    previous->nextNode = headNode;
                    tailNode = previous;
                }

                //   - deleting middle node
                else {
                    previous->nextNode = current->nextNode;
                }

                // - If playerNode points to deleted node, move playerNode to a safe node
                if (playerNode == current) {
                    playerNode = current->nextNode;
                }
                // - nodeCount--
                delete current;
                nodeCount--;

                return true;
            }

            previous = current;
            current = current->nextNode;

        } while (current != headNode);

        return false;
    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    vector<string> findByColor(string color) {
        // TODO:
        vector<string> matches;
        // - Handle Empty Board
        if (headNode == nullptr) {
            return matches;
        }

        Node<T>* current = headNode;
        // - Traverse ring exactly once
        do {
            // - Collect matching names in vector<string>
            if (current->data.propertyColor == color) {
                matches.push_back(current->data.propertyName);
            }

            current = current->nextNode;

        } while (current != headNode);
        // - Return matches
        return matches;
    }

    // -------------------------------
    // Advanced Option B (Level 2): Mirror the Board (Circular Reversal)
    // -------------------------------
    void mirrorBoard() {
        // TODO:
        // - Reverse the direction of the circular list by reversing next pointers
        // - Preserve circular structure
        // - Correctly handle empty list and single-node list
        // - Player cursor must remain on the same logical space after reversal
        cout << "mirrorBoard unwritten" << endl;
    }

    // -------------------------------
    // Edge-case helper: countSpaces O(n)
    // -------------------------------
    int countSpaces() {
        // TODO:
        if (headNode == nullptr) {
            return 0;
        }

        int count = 0;
        // - Must be O(n), traverse exactly once with correct stop condition
        Node<T>* current = headNode;
        // - Do NOT rely on nodeCount for this method
        do {

            count++;
            current = current->nextNode;

        } while (current != headNode);

        return count;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        // TODO:
        if (headNode == nullptr) {
            return;
        }
        // - Tip: if tailNode exists, break the cycle first: tailNode->nextNode = nullptr
        // break circular link first
        if (tailNode != nullptr) {
            tailNode->nextNode = nullptr;
        }

        Node<T>* current = headNode;
        // - Safely delete all nodes
        // - Then delete like a normal singly linked list
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->nextNode;
            delete temp;
        }

        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;

        nodeCount = 0;
        passGoCount = 0;
    }
};

// -------------------------------
// Main: playable loop demo
// -------------------------------
int rollDice2to12() {
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    CircularLinkedList<MonopolySpace> board;

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    // You decide how to build the board:
    // - hardcode spaces, load from file, or generate spaces programmatically
    // The only requirement: never exceed MAX_SPACES and keep the list circular.
    //
    // Example (hardcoded) usage:
    // vector<MonopolySpace> spaces;
    // spaces.push_back(MonopolySpace("GO","None",0,0));
    // ...
    // board.addMany(spaces);
    //
    // NOTE: This starter calls addSpace once to show the intended API,
    // but your final submission should build a meaningful board.
    vector<MonopolySpace> spaces;

    spaces.push_back(MonopolySpace("GO", "None", 0, 0));
    spaces.push_back(MonopolySpace("Mediterranean Avenue", "Brown", 60, 2));
    spaces.push_back(MonopolySpace("Community Chest", "None", 0, 0));
    spaces.push_back(MonopolySpace("Baltic Avenue", "Brown", 60, 4));
    spaces.push_back(MonopolySpace("Income Tax", "None", 0, 0));
    spaces.push_back(MonopolySpace("Reading Railroad", "Railroad", 200, 25));
    spaces.push_back(MonopolySpace("Oriental Avenue", "Light Blue", 100, 6));
    spaces.push_back(MonopolySpace("Chance", "None", 0, 0));
    spaces.push_back(MonopolySpace("Vermont Avenue", "Light Blue", 100, 6));
    spaces.push_back(MonopolySpace("Connecticut Avenue", "Light Blue", 120, 8));
    spaces.push_back(MonopolySpace("Jail", "None", 0, 0));

    board.addMany(spaces);
    // Wanted to demonstrate use of our helper function to verify board size
    cout << "Total spaces on board: " << board.countSpaces() << endl;

    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
    for (int turn = 1; turn <= 10; turn++) {
        int roll = rollDice2to12();
        cout << "\nTurn " << turn << " | Rolled: " << roll << endl;

        board.movePlayer(roll);

        cout << "Board view from player (next 5 spaces):" << endl;
        board.printFromPlayer(5);

        cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
    }

    // -------------------------------
    // Advanced Feature Demos (students choose path)
    // -------------------------------
    // Option A examples:
    // board.removeByName("Baltic Avenue");
    // vector<string> brownProps = board.findByColor("Brown");
    cout << "\n--- Advanced Feature Demo ---" << endl;

    // Demonstrate findByColor
    vector<string> brownProps = board.findByColor("Brown");

    cout << "Brown properties:" << endl;
    for (string name : brownProps) {
        cout << name << endl;
    }

    // Demonstrate removeByName
    cout << "\nRemoving Baltic Avenue..." << endl;

    if (board.removeByName("Baltic Avenue")) {
        cout << "Baltic Avenue removed successfully." << endl;
    } else {
        cout << "Baltic Avenue not found." << endl;
    }

    // Verify removal
    cout << "\nBoard after removal:" << endl;
    board.printBoardOnce();
    // Option B example:
    // board.mirrorBoard();

    return 0;
}
