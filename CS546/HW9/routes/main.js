const express = require('express');
const router = express.Router();
const bodyParser = require('body-parser');
const data = require("../data");
const userData = data.users;
const users = userData.users;
const passport = require('passport'), LocalStrategy = require('passport-local').Strategy;
const passHash = require('password-hash');
const flash = require('connect-flash');

function validatePass(pass, password) {
    if (passHash.verify(pass, password)) {
        return true;
    }
    return false;
}

 passport.use(new LocalStrategy(function (username, password, done) {
            for (var i = 0; i < users.length; i++) {
                if (users[i].username == username) {
                    if (validatePass(password, users[i].hashedPassword)) {
                       return done(null, users[i]);
                    }
                    else { 
                       return done(null, false, {message: 'Incorrect password.'});
                    }
                }
            }
     return done(null, false, {message: 'Incorrect username'});
 }));

passport.serializeUser(function(user, done) {
  var sessionUser = {_id : user._id, username: user.username, firstName : user.firstName, lastName: user.lastName, profession: user.profession, bio: user.bio};
    done(null, sessionUser);
});

passport.deserializeUser(function(user, done) {
done(null, user);
});

router.use(bodyParser.urlencoded({
    extended: true
}));

router.get("/", function(req, res, next) {
    if (req.user) {
        res.redirect('/private');
    }
    else {
        res.render('layouts/main', {error: req.flash('error')});
    }
});

function loggedIn(req, res, next) {
    if (req.user) {
       return next();
    } else {
        res.redirect('/');
    }
}

router.get("/private", loggedIn, function(req, res, next) {
    user = req.user;
    res.render('layouts/private', {userID: user._id, username: user.username, firstName : user.firstName, lastName : user.lastName, profession : user.profession, bio : user.bio});
});

router.post("/login", passport.authenticate('local', {successRedirect: '/private',
                                                       failureRedirect: '/',
                                                        failureFlash: true}));

module.exports = router;