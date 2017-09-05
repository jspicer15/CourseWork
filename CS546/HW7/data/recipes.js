const mongoCollections = require("../config/mongoCollections");
const recipes = mongoCollections.recipes;
const uuid = require('node-uuid');

let exportedMethods = {
    getAllRecipes() {
        return recipes().then((recipeCollection) => {
            return recipeCollection.find({}).toArray();
        });
    },
    // This is a fun new syntax that was brought forth in ES6, where we can define
    // methods on an object with this shorthand!
    getRecipeById(id) {
        return recipes().then((recipeCollection) => {
            return recipeCollection.findOne({ _id: id }).then((recipe) => {
                if (!recipe) throw "recipe not found";

                return recipe;
            });
        });
    },
    addRecipe(title, ingredients, steps, comments) {
        return recipes().then((recipeCollection) => {
            let newRecipe = {
                _id: uuid.v4(),
                title: title,
                ingredients: ingredients,
                steps: steps,
                comments: []
            };

            return recipeCollection.insertOne(newRecipe).then((newInsertInformation) => {
                return newInsertInformation.insertedId;
            }).then((newId) => {
                return this.getRecipeById(newId);
            });
        });
    },
    removeRecipe(id) {
        return recipes().then((recipeCollection) => {
            return recipeCollection.removeOne({ _id: id }).then((deletionInfo) => {
                if (deletionInfo.deletedCount === 0) {
                    throw (`Could not delete recipe with id of ${id}`)
                }
            });
        });
    },
    updateRecipe(id, updatedRecipe) {
        return this.getRecipeById(id).then((currentRecipe) => {
            let recipeUpdateInfo = {
                title: updatedRecipe.title,
                ingredients: updatedRecipe.ingredients,
                steps: updatedRecipe.steps,
            };

            let updateCommand = {
                $set: recipeUpdateInfo
            };

            return recipes().then((recipeCollection) => {
                return recipeCollection.updateOne({ _id: id }, updateCommand).then(() => {
                    return this.getRecipeById(id);
                });
            });
        });
    },
    addCommentToRecipe(recipeId, commentId, commentPoster, comment) {
        return this.getRecipeById(recipeId).then((currentRecipe) => {
            return recipes().then((recipeCollection) => {
              return recipeCollection.updateOne({ _id: recipeId }, {
                  $addToSet: {
                      comments: {
                          _id: commentId,
                          poster: commentPoster,
                          comment: comment
                      }
                  }
              }).then(() => {
                return this.getRecipeById(recipeId);
              });
        });
      });
    },
    removeCommentFromRecipe(recipeId, commentId) {
        return this.getRecipeById(id).then((currentRecipe) => {
            return recipeCollection.updateOne({ _id: id }, {
                $pull: {
                    comments: {
                        _id: recipeId,
                        _id: commentId
                    }
                }
            });
        });
    }
}

module.exports = exportedMethods;
