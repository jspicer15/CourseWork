const userData = require("./users");
let constructorMethod = (app) => {
    app.use("/", userData);
};
module.exports = {
    users: userData 
};