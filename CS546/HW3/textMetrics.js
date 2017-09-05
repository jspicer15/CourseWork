module.exports = {
  description: "This is a module to simplify text and create metrics about that text",
  simplify: (text) => {
  /*  if (arguments.length != 1) {
      throw "textMetrics.simplify Error: Number of arguments. Found: " + arguments.length + " Expected: 1";
    } */

  	/*else*/ if (typeof text !== 'string') {
  		throw "Error: argument must be a string.";
  	}
  	else {
      var alph = /^[0-9a-zA-Z]+$/;
      text = text.toLowerCase();
      var len = text.length;

  		for (var i = 0; i < len; i++) {
        if (text[i].match(/\s/g) != null) {
          text = text.replace(text[i], " ");
        }
  			else if (text[i].match(alph) == null) {
  				text = text.replace(text[i], "");
          len--;
  			}
  		}
  		return text;
  	}
  },
  createMetrics: (text) => {
    var totalLetters = 0;
    var totalWords = 0;
    var word = "";
    var wordsArr = [];
    var wordOccur = [];
    var wordUnique = [];
    var uniqueWords = 0;
    var longWords = 0;
    var averageWordLength = 0;
    var unique = true;
    var pushed = false;
    var occurenceObj = {};
    var returnMe = {};
    text = module.exports.simplify(text);


    var alph = /^[0-9a-zA-Z]+$/;

    for (var i = 0; i < text.length; i++) {
        if (text[i].match(alph) != null) {
          totalLetters++;
          word = word.concat(text[i]);
        }
        else if (word.length > 0) {
          if (word.length >= 6) {
            longWords++;
          }
          wordsArr.push(word);
          word = "";
        }
    }

    if (word.length > 0) {
      if (word.length >= 6) {
        longWords++;
      }
      wordsArr.push(word);
      word = "";
    }

    totalWords = wordsArr.length;

    for (var i = 0; i < wordsArr.length; i++) {
      if (wordUnique[i] != false) {
      wordUnique[i] = true;
    }
      unique = true;
      for (var j = i + 1; j < wordsArr.length; j++) {
        if (wordsArr[i] == wordsArr[j]) {
          unique = false;
          wordUnique[i] = false;
          wordUnique[j] = false;
        }
        if (unique) {
          uniqueWords++;
      }
    }
  }

    for (var i = 0; i < wordsArr.length; i++) {
      wordOccur.push(1);
      if (!wordUnique[i]) {
        for (var j = i + 1; j < wordsArr.length; j++) {
          if (wordsArr[i] == wordsArr[j]) {
            wordOccur[i]++;
            wordsArr.splice(j, 1);
            j--;
          }
        }
        occurenceObj[wordsArr[i]] = wordOccur[i];
      }
      else {
        wordOccur[i] = 1;
        occurenceObj[wordsArr[i]] = 1;
      }
    }
    averageWordLength = totalLetters / totalWords;
    returnMe["totalLetters"] = totalLetters;
    returnMe["totalWords"] = totalWords;
    returnMe["uniqueWords"] = uniqueWords;
    returnMe["longWords"] = longWords;
    returnMe["averageWordLength"] = averageWordLength;
    returnMe["wordOccurences"] = occurenceObj;
    return returnMe;
  }
};
