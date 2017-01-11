#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// A list of bytes, defaulting to 0.
class ByteList {
public:
  map<int, char> data;
  unsigned char get(int index);
  void set(int index, unsigned char value);
};

// Get a value in a ByteList.
unsigned char ByteList::get(int i) {
  if (data.find(i) == data.end()) {
    return 0;
  } else {
    return data.at(i);
  }
}

// Set a value in a ByteList.
void ByteList::set(int i, unsigned char v) {
  data[i] = v;
}

// A bidirectional map for parentheses matching.
class ParenSet {
public:
  ParenSet(string in, char opener, char closer);
  int open(int closedAt);
  int close(int openedAt);
  map<int, int> opened;
  map<int, int> closed;
};

// Create the parenthesis set from the given input, using the given
// opening and closing items for parentheses.
ParenSet::ParenSet(string in, char opener, char closer) {
  vector<int> openList;
  for (int i = 0; i < in.size(); i++) {
    char c = in.at(i);
    if (c == opener) {
      openList.push_back(i);
    } else if (c == closer) {
      opened[i] = openList.back();
      closed[openList.back()] = i;
      openList.pop_back();
    }
  }
}

// Get the opening bracket position given a closing bracket position.
int ParenSet::open(int closedAt) {
  if (opened.find(closedAt) == opened.end()) return 0;
  else return opened[closedAt];
}

// Get the closing bracket position given an opening bracket position.
int ParenSet::close(int openedAt) {
  if (closed.find(openedAt) == closed.end()) return 0;
  else return closed[openedAt];
}

// Brainfuck interpreter.
string brainfuck(string code, string in) {
  ParenSet parens(code, '[', ']'); // Parenthesis mapping.
  ByteList memory; // The code's memory stack.

  int inN = 0;     // Index in input text.
  int codeN = 0;   // Index in code text.
  int memN = 0;    // Index in memory.
  string out;

  // Iterate through the brainfuck code.
  while (codeN < code.size()) {
    switch (code.at(codeN)) {

      // Increment / decrement current memory cell.
      case '+':
        memory.set(memN, memory.get(memN) + 1);
        break;
      case '-':
        memory.set(memN, memory.get(memN) - 1);
        break;

      // Move to memory cells to left and right of current position.
      case '>': memN++; break;
      case '<': memN--; break;

      // Print the current character.
      case '.':
        out += memory.get(memN);
        break;

      // Read a character from standard input.
      case ',':
        if (inN < in.size())
          memory.set(memN, in.at(inN));
        else
          memory.set(memN, 0);
        inN++;
        break;

      // Continue or jump conditionally.
      case '[':
        if (!memory.get(memN)) codeN = parens.close(codeN);
        break;
      case ']':
        codeN = parens.open(codeN) - 1;
    }
    codeN++;
  }
  return out;
}

int main () {
  cout << brainfuck("++[,.]", "This is the brainfuck input text, to be printed!") << endl;
}