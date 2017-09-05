const uuid = require('node-uuid');
const passport = require('passport');
const passHash = require('password-hash');
const users = [
  { _id: "1245325124124", username: "masterdetective123", firstName: "Sherlock", lastName: "holmes", profession: "Detective", bio: "Sherlock Holmes (/ˈʃɜːrlɒk ˈhoʊmz/) is a fictional private detective created by British author Sir Arthur Conan Doyle. Known as a 'consulting detective' in the stories, Holmes is known for a proficiency with observation, forensic science, and logical reasoning that borders on the fantastic, which he employs when investigating cases for a wide variety of clients, including Scotland Yard.", hashedPassword: "sha1$b34c946b$1$cb4d670ae77b32bb1b68e8ea8e8a92642b287d4b" },
    
  { _id: "723445325124124", username: "lemon", firstName: "Elizabeth", lastName: "Lemon", profession: "Writer", bio: "Elizabeth Miervaldis 'Liz' Lemon is the main character of the American television series 30 Rock. She created and writes for the fictional comedy-sketch show The Girlie Show or TGS with Tracy Jordan.", hashedPassword: "sha1$be978fd2$1$c7cb41650e6555b136133ffc2b0bfa079d1e76eb" },
    
    {_id: "72344532516712", username: "theboywholived", firstName: "Harry", lastName: "Potter", profession: "Student", bio: "Harry Potter is a series of fantasy novels written by British author J. K. Rowling. The novels chronicle the life of a young wizard, Harry Potter, and his friends Hermione Granger and Ron Weasley, all of whom are students at Hogwarts School of Witchcraft and Wizardry . The main story arc concerns Harry's struggle against Lord Voldemort, a dark wizard who intends to become immortal, overthrow the wizard governing body known as the Ministry of Magic, and subjugate all wizards and Muggles.", hashedPassword: "sha1$e5ed4dd4$1$e24a391e39726d0ef1303c949c8d6db66c709720"}
];

function validatePass(pass, password) {
    if (!passHash.verify(pass, password)) {
        return false;
    }
    return true;
}

var exportedMethods = {
    login(username, password) {
        passport.use(new LocalStrategy(function (username, password, done) {
            for (var i = 0; i < users.length; i++) {
                if (users[i].username == username) {
                    if (!validatePass(users[i].password, password)) {
                        return done(null, false);
                    }
                    return done(null, obj[i]);
                }
            }
            return done(null, false);
        }));
    }
};

module.exports = exportedMethods;
module.exports.users = users;