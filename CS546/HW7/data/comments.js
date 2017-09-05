const mongoCollections = require("../config/mongoCollections");
const comments = mongoCollections.comments;
const recipeCollections = mongoCollections.recipes;
const recipes = require("./recipes");
const uuid = require('node-uuid');

let exportedMethods = {
  getAllComments() {
  return recipeCollections().then((recipeCollection) => {
      return recipeCollection
          .find({}, {_id: 0, ingredients: 0, steps: 0, comments: 1})
          .toArray();
  });
},
getCommentById(id) {
  return recipeCollections().then((recipeCollection) => {
      return recipeCollection
          .findOne({"comments._id": id}).then((comment) => {
            if (comment) {
              for (var i = 0; i < comment.comments.length; i++) {
                if (comment.comments[i]._id == id)
                    return comment.comments[i];
              }
            }
            else
              throw ('Error could not find comment')
          });
  });
},
    addComment(id, poster, comment) {
        if (typeof poster !== "string")
            return Promise.reject("No poster provided");
        if (typeof comment !== "string")
            return Promise.reject("No comment provided!");

        return comments().then((commentCollection) => {
          var newComment = {
              _id: uuid.v4(),
              poster: poster,
              comment: comment
          };
          console.log(newComment);
            return recipes
                .addCommentToRecipe(id, newComment._id, newComment.poster, newComment.comment)
                .then((recipeOfId) => {
                    return commentCollection
                        .insertOne(newComment)
                        .then((newInsertInformation) => {
                            return newInsertInformation.insertedId;
                        })
                        .then((newId) => {
                            return this.getCommentById(newId);
                        });
                });
        });
    },
    removeComment(id) {
      return recipeCollections().then((recipeCollection) => {
          return recipeCollection.update({}, {$pull: {comments: {_id: id } }}).then((deletionInfo) => {
              if (deletionInfo.deletedCount === 0) {
                  throw (`Could not delete comment with id of ${id}`)
              }
                return comments().then((commentCollection) => {
                  return commentCollection.removeOne({_id: id}).then((deletionInfo) => {
                    if (deletionInfo.deletedCount === 0) {
                      throw ('Could not delete comment with id of ${id}')
                    }
                  });
                });
          });
      });
  },
    updateComment(recipeId, commentId, updatedComment) {
      return this.getCommentById(commentId).then((currentComment) => {
        var updatedCommentData = {
          _id: currentComment._id,
          poster: updatedComment.poster,
          comment: updatedComment.comment,
        };

        var updateCommand = {
            $set: updatedCommentData
        };

        var updateRecipeCommand = {
            $set: { "comments.$" : updatedCommentData}
        }

        return recipeCollections().then((recipeCollection) => {
          return recipeCollection.updateOne({_id: recipeId, "comments._id": commentId}, updateRecipeCommand).then(() => {
            return comments().then((commentCollection) => {
                return commentCollection
                .updateOne({ _id: currentComment._id}, updateCommand)
                .then(() => {
                    return this.getCommentById(commentId);
                });
            });
            });
          });
        });
    }
}

module.exports = exportedMethods;
