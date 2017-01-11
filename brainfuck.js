// A list of bytes, with each index defaulting to 0, and wrapping to stay
// in the range of 0 - 255.
class ByteList {
  get(i) {
    return this[i] || 0;
  }
  set(i, n) {
    this[i] = n % 256;
  }
}

// Pre-parse a string to find matching pairs of braces.
// Returns an object that contains two sub-objects: `open` and `close`.
// `open` maps the char index of closing brackets to their opening sibling.
// `close` maps the char index of the opening bracket to their closing sibling.
function matchBraces (str, open, close) {
  var result = {
    open: {},
    close: {}
  };
  var opened = [];
  // Loop through and find opening and closing brackets.
  for (var i = 0; i < str.length; i++) {
    if (str.charAt(i) === open) {
      opened.push(i);
    } else if (str.charAt(i) === close) {
      var openInd = opened.pop();
      result.open[i] = openInd;
      result.close[openInd] = i;
    }
  }
  return result;
}

// Brainfuck interpreter - responds with string output, using input as stdin.
function brainfuck(input, stdin) {
  const data = new ByteList(); // Data cells for storage.
  const brackets = matchBraces(input, '[', ']'); // Matching pairs of brackets.

  let index = 0; // Index within data storage.
  let output = ""; // The output string for stdout.
  let stdIndex = 0; // The index within the given stdin.

  // Iterate every character.
  for (var i = 0; i < input.length; i++) {
    switch (input.charAt(i)) {
    case '.':
      output += String.fromCharCode(data.get(index));
      break;
    case '+':
      data.set(index, data.get(index) + 1);
      break;
    case '-':
      data.set(index, data.get(index) - 1);
      break;
    case '>':
      index++;
      break;
    case '<':
      index--;
      break;
    case '[':
      if (!data.get(index)) {
        // Jump to matching closing bracket.
        i = brackets.close[i];
      }
      break;
    case ']':
      i = brackets.open[i] - 1;
      break;
    case ',':
      if (stdIndex < stdin.length)
        data.set(index, stdin.charCodeAt(stdIndex));
      else
        data.set(index, 0);
      stdIndex++;
      break;
    }
  }
  return output;
}

console.log(brainfuck("+[,.]", "This is the brainfuck input text, to be printed!"));