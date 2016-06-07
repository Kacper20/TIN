//
// Created by Kacper Harasim on 07.06.2016.
//

#include <sstream>
#include <iostream>
#include "InputReceiver.h"


int InputReceiver::getInt(std::istream &stream) {{
    // Only loop as long as the input is stream is usable.
    // Otherwise you enter an infinite loop.
    while (stream)
    {

      // Read a line of user input.
      std::string line;
      std::getline(stream, line);

      // Now convert user input to value.
      std::stringstream linestream(line);
      int               value;

      if (!(linestream >> value)) {
        continue;   // The input was not an integer.
      }               // So retry the loop.

      // You got a good value.
      // Do you care if there is stuff on the end of the line?
      // i.e.  If the user entered 56 f<enter> is that bad?
      //       If it is then you check to see if there is more valid input on the line.
      char  x;

      if (linestream >> x) {
        continue;    // There was good input (thus the input was bad).
      }
      return value;
    }
    // If you get here,
    // this means you ran out of input.
    // What do you do?
    // You could return a default value.
    // or throw an exception.
    return 0;

    // The trouble with either of these methods is that its hard to detect
    // the error situation. You need to explicitly check. That is why `operator>>`
    // works well. The stream goes bad when things get out of sync and the natural
    // operations cause the current operation to fail.
  } }