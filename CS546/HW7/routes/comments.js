const express = require('express');
const router = express.Router();
const data = require("../data");
const commentData = data.comments;
const recipeData = data.recipes;
const bodyParser = require('body-parser');

router.use(bodyParser.json());

router.get("/:commentId", (req, res) => {
    commentData.getCommentById(req.params.commentId).then((comment) => {
        res.json(comment);
    }).catch(() => {
        res.status(404).json({ error: "Comment not found" });
    });
});

router.get("/recipe/:recipeId", (req, res) => {
    recipeData.getRecipeById(req.params.recipeId).then((recipe) => {
        res.json(recipe.comments);
    }).catch(() => {
      res.status(404).json({ error: "Comment not found" });
    });
});

router.post("/:recipeId", (req, res) => {
    var commentDat = req.body;
    var id = req.params.recipeId;

    if (!commentDat) {
      res.status(400).json({error: "You must provide data for the comment"});
      return;
    }

    if (!commentDat.poster) {
         res.status(400).json({ error: "You must provide a poster for the comment" });
         return;
     }

     if (!commentDat.comment) {
         res.status(400).json({ error: "You must provide a comment" });
         return;
     }

    commentData.addComment(id, commentDat.poster, commentDat.comment)
        .then((newComment) => {
            res.json(newComment);
        }).catch((e) => {
            res.status(500).json({ error: e });
        });
});

router.put("/:recipeId/:commentId", (req, res) => {
    var updatedData = req.body;
    commentData.getCommentById(req.params.commentId).then(() => {
        commentData.updateComment(req.params.recipeId, req.params.commentId, updatedData)
            .then((updatedComment) => {
                res.json(updatedComment);
            }, (error) => {
                res.sendStatus(500);
            });
    }).catch(() => {
        res.status(404).json({ error: "Comment not found" });
    });
  });

router.delete("/:id", (req, res) => {
        commentData.removeComment(req.params.id)
            .then((removedComment) => {
                res.json(removedComment);
            }).catch((e) => {
                res.status(500).json({ error: e });
            });
    });

module.exports = router;
