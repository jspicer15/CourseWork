const express = require('express');
const router = express.Router();
const education = [
    {
      "schoolName": "Stevens Institute of Technology",
      "degree": "Bachelor's of Science",
      "favoriteClass": "CS519 Introduction to eCommerce",
      "favoriteMemory": "Humphreys"
    },
    {
      "schoolName": "Immaculata High School",
      "degree": "High School Diploma",
      "favoriteClass": "Senior Year English",
      "favoriteMemory": "My friend telling my English teacher that I did not read the book we were writing an essay on."
    }
];

router.get("/", (req, res) => {
  try {
        res.json(education);
      } catch(err) {
        res.status(500).send('Server Error:' + err);
      }
});

module.exports = router;
