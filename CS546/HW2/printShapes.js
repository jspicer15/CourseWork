module.exports = {
  description: "This is a module to print shapes",
  triangle: (lines) => {
    if (typeof lines != "number") {
      throw "Error: Input must be a number";
    }

    else if (lines < 1) {
      throw "Error: Input must be greater than 1";
    }

    var spaces = 0;
    var printMe = "";

    while (lines > 0) {
        printMe = printMe.concat(Array(lines).join(" "));
        printMe = printMe.concat("/");

        if ((spaces != 0) && (lines != 1)) {
          printMe = printMe.concat(Array((spaces + 1) * 2 - 1).join(" "));
        }

        else if (lines == 1) {
          printMe = printMe.concat(Array((spaces + 1) * 2 - 1).join("-"));
        }

        printMe = printMe.concat("\\\n");
        lines--;
        spaces++;
    }
    console.log(printMe);
},
square: (lines) => {
  if (typeof lines != "number") {
    throw "Error: Input must be a number";
  }

  else if (lines < 2) {
    throw "Error: Squares must be at least 2 lines";
  }

  var printMe = "";
  var max = lines;

  while (lines > 0) {
  printMe = printMe.concat("|");

  if ((lines == max) || (lines == 1)) {
    printMe = printMe.concat(Array(max + 1).join("-"));
  }

  else {
    printMe = printMe.concat(Array(max + 1).join(" "));
  }

  printMe = printMe.concat("|\n");
  lines--;
  }

  console.log(printMe);
},
rhombus: (lines) => {
  if (typeof lines != "number") {
    throw "Error: Input must be a number";
  }

  else if (lines < 2) {
    throw "Error: Input must be at least 2";
  }

  else if (lines % 2 != 0) {
    throw "Error: Input must be an even number";
  }

  var printMe = "";
  var max = lines;
  var midpoint = lines / 2;
  var spaces = 1;

  while (lines > midpoint) {
      if (lines == max) {
        printMe = printMe.concat(Array(lines + 1).join(" "));
        printMe = printMe.concat("/-\\\n")
      }

      else {
        printMe = printMe.concat(Array(lines + 1).join(" "));
        printMe = printMe.concat("/");
        printMe = printMe.concat(Array(spaces + 1).join(" "));
        printMe = printMe.concat("\\\n");
      }

      lines--;
      spaces += 2;
  }

    spaces -= 2;
    lines++;

    while (lines < max + 1) {
      if (lines == max) {
        printMe = printMe.concat(Array(lines + 1).join(" "));
        printMe = printMe.concat("\\-/\n")
      }

      else {
        printMe = printMe.concat(Array(lines + 1).join(" "));
        printMe = printMe.concat("\\");
        printMe = printMe.concat(Array(spaces + 1).join(" "));
        printMe = printMe.concat("/\n");
      }

      lines++;
      spaces -= 2;
    }

  console.log(printMe);
}
};
