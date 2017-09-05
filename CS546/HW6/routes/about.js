const express = require('express');
const router = express.Router();
const about = {
  "name": "John Spicer",
  "biography": "Born in 1982 to a family of Warlocks, John Spicer was the first Ukrainian born man to attend clown school in the United States. After strengthening his skills as a clown, John began working on fine tuning his wizarding skills, and desired to one day combine his skills as both a clown and a wizard. John left the United States to join the underwater wizarding school in Atlantis, where soon after graduating he became a professor. Garnering much interest for his practices in clown wizardry, John gained many enemies in the field. In his fifth year of teaching, a student dressed as a sad clown (the only clowns that John detested) came into his classroom and turned him into a toad. The student took John in toad form back to his apartment, where John has lived ever more.",
  "favoriteShows": ["Pretty Little Liars", "Teen Mom", "Catfish", "MLB Baseball", "Baggage"],
  "hobbies": ["Home Improvement", "Working on Cars", "eCommerce", "Eating", "Instagram"]
};

router.get("/", (req, res) => {
  try {
        res.json(about);
      } catch(err) {
        res.status(500).send('Server Error:' + err);
      }
});

module.exports = router;
