const fileData = require('./fileData');
const textMetrics = require('./textMetrics')
const fs = require('fs');

if (fs.existsSync("chapter1.result.json")) {
  fileData.getFileAsJSON("chapter1.result.json").then(function(result) {
    console.log(result);
  });
}
else {
  var simplified = "";
  var chap = "";
  chap = fileData.getFileAsString("chapter1.txt");
  chap.then(function(result) {
    simplified = textMetrics.simplify(result);
    fileData.saveStringToFile("chapter1.debug.txt", simplified).then();
    var metrics = textMetrics.createMetrics(simplified);
    fileData.saveJSONToFile("chapter1.result.json", metrics).then();
    console.log(metrics);
  });
}

if (fs.existsSync("chapter2.result.json")) {
  fileData.getFileAsJSON("chapter2.result.json").then(function(result) {
    console.log(result);
  });
}
else {
  var simplified = "";
  var chap = "";
  chap = fileData.getFileAsString("chapter2.txt");
  chap.then(function(result) {
    simplified = textMetrics.simplify(result);
    fileData.saveStringToFile("chapter2.debug.txt", simplified).then();
    var metrics = textMetrics.createMetrics(simplified);
    fileData.saveJSONToFile("chapter2.result.json", metrics).then();
    console.log(metrics);
  });
}

if (fs.existsSync("chapter3.result.json")) {
  fileData.getFileAsJSON("chapter3.result.json").then(function(result) {
    console.log(result);
  });
}
else {
  var simplified = "";
  var chap = "";
  chap = fileData.getFileAsString("chapter3.txt");
  chap.then(function(result) {
    simplified = textMetrics.simplify(result);
    fileData.saveStringToFile("chapter3.debug.txt", simplified).then();
    var metrics = textMetrics.createMetrics(simplified);
    fileData.saveJSONToFile("chapter3.result.json", metrics).then();
    console.log(metrics);
  });
}
