const express = require('express');
const router = express.Router();
const bodyParser = require('body-parser');
const data = require("../data");
const termData = data.terms;
router.use(bodyParser.urlencoded({
    extended: true
}));

function checkPalindrome(word) {
    if (typeof word !== 'string') {
        throw "the word must be a string";
    }
    else {
        if (word.toLowerCase() === word.toLowerCase().split('').reverse().join('')) {
            return true;
        }
        else {
            return false;
        }
    }
}
router.get("/", (req, res) => {
    try {
        termData.getAllTerms().then((termList) => {
            res.render('layouts/main', {
                terms: termList
            });
        });
    }
    catch (err) {
        res.status(500).send('Server Error:' + err);
    }
});
router.post("/", (req, res) => {
    var postData = req.body;
    try {
        if (checkPalindrome(postData.textInput)) {
            termData.newTerm(postData.textInput, true).then(() => {
                return;
            });
        }
        else {
            termData.newTerm(postData.textInput, false).then(() => {
                return;
            });
        }
        res.redirect("/");
    }
    catch (err) {
        res.status(500).send('Server Error:' + err);
    }
});
module.exports = router;