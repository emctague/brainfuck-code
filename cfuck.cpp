// CFuck / cf - Compiles brainfuck code into a native executable.
// Copyright (C) 2017 Ethan McTague
// Tested on GNU/Linux - may work on other systems.
// Warning: Some functions used are deprecated / unsafe.

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>

using namespace std;

// Brainfuck to C++ conversion function.
string cppBrainfuck(string code) {
  int codeN = 0;   // Index in code text.
  int indents = 1; // Number of indents to add.

  // This is the top bit of the C++ file.
  string out = "#include <iostream>\n\
#include<stdio.h>\n\
#include <map>\n\
using namespace std;\n\
map<char,char> data;\n\
char at(int pos) {\n\
\tif (data.find(pos) == data.end()) return 0;\n\
\telse return data[pos];\n\
}\n\
int main() {\n\
\tint pos = 0;\n";

  // Iterate through the brainfuck code.
  while (codeN < code.size()) {
    // Add necessary indentation.
    for (int ind = 0; ind < indents; ind++) {
      out += "\t";
    }
    // Add the code neccesary for this instruction.
    switch (code.at(codeN)) {

      // Increment / decrement current memory cell.
      case '+': out += "data[pos] = at(pos) + 1;\n"; break;
      case '-': out += "data[pos] = at(pos) - 1;\n"; break;

      // Move to memory cells to left and right of current position.
      case '>': out += "pos++;\n"; break;
      case '<': out += "pos--;\n"; break;

      // Print the current character.
      case '.': out += "cout << at(pos);\n"; break;

      // Read a character from standard input.
      case ',': out += "data[pos] = getchar();\n"; break;

      // Continue or jump conditionally.
      case '[':
        out += "while (at(pos)) {\n";
        indents++;
        break;
      case ']':
        out.pop_back(); // Remove indentation.
        out += "}\n";
        indents--;
        break;
    }
    codeN++;
  }
  // Add final bracket and return.
  out += "}\n";
  return out;
}

int main (int argc, char* argv[]) {
  // Check arg count.
  if (argc < 3) {
    cout << "Usage: " << argv[0] << " [source file] [target]" << endl;
  } else {
    // Read the input file.
    std::ifstream t(argv[1]);
    std::stringstream buffer;
    buffer << t.rdbuf();

    // Parse the brainfuck to C++.
    string code = cppBrainfuck(buffer.str());

    // Create a temporary file ending in .cpp in /tmp.
    string tmpname = tmpnam(NULL);
    tmpname += ".cpp";

    // Write the generated code to the temporary file.
    ofstream fs(tmpname);
    fs << code << endl;
    fs.close();

    // Compile using g++.
    std::string command = "g++ ";
    command += tmpname + " -o " + argv[2];
    system(command.c_str());

    // Delete the temporary file.
    remove(tmpname.c_str());
  }
  return 0;
}