var request = require('request');
var jsonRecipe = {
"title": "Cooked Eggs",
"ingredients": [
{
  "name": "Egg",
  "amount": "15 eggs"
},
{
  "name": "Olive Oil",
  "amount": "2 tbsp"
},
],
"steps": [
"First, heat a non-stick pan on medium-high until hot",
"Add the oil to the pan and allow oil to warm; it is ready the oil immediately sizzles upon contact with a drop of water.",
"Crack the egg and place the egg and yolk in a small prep bowl; do not crack the yolk!",
"Gently pour the egg from the bowl onto the oil",
"Wait for egg white to turn bubbly and completely opaque (approx 2 min)",
"Using a spatula, flip the egg onto its uncooked side until it is completely cooked (approx 2 min)",
"Remove from oil and plate",
"Repeat for second egg"
],
"comments": []
};
var jsonComment = {
  poster: "Jeffrey Ramsay",
  comment: "These eggs are delicious!"
}
request({
    url: "http://localhost:3000/comments/dd188f2b-bb20-4db4-b4d5-9efa276821d7",
    method: "POST",
    json: true,   // <--Very important!!!
    body: jsonComment
}, function (error, response, body){
    console.log(response);
});
