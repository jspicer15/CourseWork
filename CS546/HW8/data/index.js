const termData = require("./terms");
let constructorMethod = (app) => {
    app.use("/", termData);
};
module.exports = {
    terms: termData 
};