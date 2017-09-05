const fs = require('fs');

module.exports = {
  description: "This is a module to retrieve/save data from/to files",
  getFileAsString: (path) => {
    return new Promise(function(resolve, reject) {
      if (path == null) {
        return reject("No Path Provided");
      }
      fs.readFile(path, 'utf-8', function(err, data) {
        if (err) {
          return reject("Error reading file");
        }
        return resolve(data);
      });
    });
  },
  getFileAsJSON: (path) => {
    return new Promise(function(resolve, reject) {
      module.exports.getFileAsString(path).then(function(result) {
          return resolve(JSON.parse(JSON.stringify(result)));
        });
    });
  },
  saveStringToFile: (path, text) => {
    return new Promise(function(resolve, reject) {
      if ((path == null) || (text == null)) {
        return reject("No Path Provided");
      }
      fs.writeFile(path, text, 'utf-8', function(err) {
        if (err) {
          return reject("Error writing file");
        }
        return resolve(true);
      });
    });
  },
  saveJSONToFile: (path, obj) => {
    return new Promise(function(resolve, reject) {
      module.exports.saveStringToFile(path, JSON.stringify(obj)).then(function(result) {
        return resolve(true);
      });
    });
  }
}
