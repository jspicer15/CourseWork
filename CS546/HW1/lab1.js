/*
	John Spicer
	1/26/2017
*/
function sumOfSquares(num1, num2, num3) {
	if ((!Number.isInteger(num1)) || (!Number.isInteger(num2)) || (!Number.isInteger(num3))) {
		throw "Error: Please make sure each argument is an integer";
	}
	return (num1 * num1) + (num2 * num2) + (num3 * num3);
}

function sayHelloTo(firstName, lastName, title) {
		if ((typeof title == 'string') && (typeof firstName == 'string') && (typeof lastName == 'string')) {
			console.log(`Hello, ${title} ${firstName} ${lastName}!`);
		}

	  else if (typeof lastName != 'undefined') {

			if ((typeof firstName == 'string') && (typeof lastName == 'string')) {
				console.log(`Hello, ${firstName} ${lastName}!`);
			}

			else {
				throw "Error: Please make sure each argument is a string.";
			}
		}

	else if (typeof firstName != 'undefined') {

		if (typeof firstName == 'string') {
			console.log(`Hello, ${firstName}!`);
		}

		else {
			throw "Error: Please make sure each argument is a string.";
		}
	}

	else
	{
		throw "Error: Must have at least one argument";
	}
}

function cupsOfCoffee(howManyCups) {
	var printMe = "";

	if (!Number.isInteger(howManyCups)) {
		throw "Error: Please make sure the argument is an integer";
	}

	if (howManyCups < 1) {
		throw "Error: Please input an integer greater than 1";
	}

	while (howManyCups > 2) {
		printMe = printMe.concat(`${howManyCups} cups of coffee on the desk! 5 cups of coffee!\nPick one up, drink the cup, ` + --howManyCups + ` cups of coffee on the desk!\n\n`);

		if (howManyCups == 2) {
				printMe = printMe.concat("2 cups of coffee on the desk! 2 cups of coffee!\nPick one up, drink the cup, " + --howManyCups + " cup of coffee on the desk!\n\n");
		}
	}

	if (howManyCups == 1) {
		printMe = printMe.concat("1 cup of coffee on the desk! 1 cup of coffee!\nPick it up, drink the cup, no more coffee left on the desk!");
	}

	return printMe;
}

function occurrencesOfSubstring(fullString, substring) {
	if ((typeof fullString != 'string') || (typeof substring != 'string'))
		throw "Error: Please make sure both arguments are strings";

	var index = 0;
	var count = 0;

	while (true) {
		index = fullString.indexOf(substring, index);
		if (index >= 0) {
			count++;
			index++;
		}
		else
			break;
	}
	return count;
}

function randomizeSentences(paragraph) {
	if (typeof paragraph != 'string')
		throw "Error: Please make sure the argument is a string";

	if (paragraph.length < 1) {
		throw "Error: Please provide at least one sentence to randomize."
	}

	var sentences = [];
	var index = 0;
	var printMe = "";

	for (var i = 0; i < paragraph.length; i++) {

		if ((paragraph[i] == '.') || (paragraph[i] == '?') || (paragraph[i] == '!')) {
			sentences.push(paragraph.substring(index, ++i));
			index = i;
		}
	}

	while (sentences.length > 0) {
		var temp = Math.floor(Math.random() * sentences.length - 1) + 1;
		printMe = printMe.concat(sentences[temp]);
		sentences.splice(temp, 1);
	}
	console.log(printMe);
}
/* TESTING
console.log("Testing sumOfSquares:\n");
console.log(sumOfSquares(5, 3, 10)); // 134
//console.log(sumOfSquares('hello', 5, 2)); // throws
console.log("\nTesting sayHelloTo:\n");
//sayHelloTo(); // throws
sayHelloTo("Phil"); // logs: Hello, Phil!
sayHelloTo("Phil", "Barresi"); //logs: Hello, Phil Barresi. I hope you are having a good day!
sayHelloTo("Phil", "Barresi", "Mr."); // logs: Hello, Mr. Phil Barresi! Have a good evening!
console.log("\nTesting cupsOfCoffee:\n");
console.log(cupsOfCoffee(5));
console.log(cupsOfCoffee(2));
console.log(cupsOfCoffee(1));
//console.log(cupsOfCoffee(0)); throws
//console.log(cupsOfCoffee("hi")); throws
console.log("\n");
console.log("Testing occurencesOfSubstring:\n");
console.log(occurrencesOfSubstring("hello world", "o"));
console.log(occurrencesOfSubstring("Helllllllo, class!", "ll"));
console.log("\n");
console.log("Testing randomizeSentences:\n");
var paragraph = "Hello, world! I am a paragraph. You can tell that I am a paragraph because there are multiple sentences that are split up by punctuation marks. Grammar can be funny, so I will only put in paragraphs with periods, exclamation marks, and question marks -- no quotations.";

randomizeSentences(paragraph);
*/
