const express = require('express');
const router = express.Router();
const data = require("../data");
const recipeData = data.recipes;
const bodyParser = require('body-parser');

router.use(bodyParser.json());

router.get("/", (req, res) => {
    recipeData.getAllRecipes().then((recipes) => {
      for (var i = 0; i < recipes.length; i++) {
        ans = {};
        ans._id = recipes[i]._id;
        ans.title = recipes[i].title;
        recipes[i] = ans;
      }
        res.json(recipes);
    }, () => {
        res.status(500).send();
    });
});

router.get("/:id", (req, res) => {
  recipeData.getRecipeById(req.params.id).then((recipe) => {
    res.json(recipe);
  }, (error) => {
    res.status(404).json({message: "ID Not Found"});
  });
});

router.post("/", (req, res) => {
  var recipe = req.body;
  if (!recipe) {
    res.status(400).json({error: "You must provide data for the recipe"});
    return;
  }

  if (!recipe.title) {
       res.status(400).json({ error: "You must provide a title for the id" });
       return;
   }

   if (!recipe.ingredients) {
       res.status(400).json({ error: "You must provide ingredients" });
       return;
   }

   if (!recipe.steps) {
     res.status(400).json({ error: "You must provide steps" });
     return;
   }

   recipeData.addRecipe(recipe.title, recipe.ingredients, recipe.steps)
       .then((newRecipe) => {
           res.json(newRecipe);
       }, () => {
           res.sendStatus(500);
       });
});


router.put("/:id", (req, res) => {
    var recipe = req.body;
    if (!recipe) {
        res.status(400).json({ error: "You must provide data to update a recipe" });
        return;
    }

    var getRecipe = recipeData.getRecipeById(req.params.id).then((oldRecipe) => {
      var newRecipe = {};
      newRecipe._id = oldRecipe._id;
      if (!recipe.title) {
           newRecipe.title = oldRecipe.title;
       }
       else {
         newRecipe.title = recipe.title;
       }

       if (!recipe.ingredients) {
           newRecipe.ingredients = oldRecipe.ingredients;
       }
       else {
         newRecipe.ingredients = recipe.ingredients;
       }

       if (!recipe.steps) {
         newRecipe.steps = oldRecipe.steps;
       }
       else {
         newRecipe.steps = recipe.steps;
       }
       console.log(newRecipe);
       newRecipe.comments = oldRecipe.comments;
        return recipeData.updateRecipe(req.params.id, newRecipe)
            .then((updatedRecipe) => {
                res.json(updatedRecipe);
            }, (error) => {
                console.log(error);
                res.sendStatus(500);
            });
    }).catch(() => {
        res.status(404).json({ error: "Recipe not found" });
    });

});


router.delete("/:id", (req, res) => {
    var recipe = recipeData.getRecipeById(req.params.id).then(() => {
        return recipeData.removeRecipe(req.params.id)
            .then(() => {
                res.sendStatus(200);
            }).catch(() => {
                res.sendStatus(500);
            });

    }).catch((err) => {
        console.log(err);
        res.status(404).json({ error: "Recipe not found" });
    });
});

module.exports = router;
