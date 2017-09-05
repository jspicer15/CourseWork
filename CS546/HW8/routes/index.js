const mainRoute = require("./main");
const constructorMethod = (app) => {
    app.use("/", mainRoute);
    app.use("*", (req, res) => {
        res.status(404).json({
            error: "Not found"
        });
    });
};
module.exports = constructorMethod;