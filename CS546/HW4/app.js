const todoItems = require("./todo");

var createdTask = todoItems.createTask("Ponder Dinosaurs", "Has Anyone Really Been Far Even as Decided to Use Even Go Want to do Look More Like?");

createdTask.then((newTask) => {
    console.log(newTask);
    var firstTaskId = newTask._id;

    var secondTask = todoItems.createTask("Play Pokemon with Twitch TV", "Should we revive Helix");

    secondTask.then((newTask2) => {
      console.log(newTask2);
      var secondTaskId = newTask2._id;

      var getMyTasksPromise = todoItems.getAllTasks();

      getMyTasksPromise.then((taskList) => {
        console.log(taskList);
      });

      var removeFirst = todoItems.removeTask(firstTaskId);

      removeFirst.then((result) => {
        var getTasksAgain = todoItems.getAllTasks();

        getTasksAgain.then((taskList2) => {
          console.log(taskList2);
        });

        var completeLastTask = todoItems.completeTask(secondTaskId);

        completeLastTask.then((result) => {
          return;
        });

        var getTasksLastTime = todoItems.getAllTasks();

        getTasksLastTime.then((result) => {
          console.log(result);
        });
        
        return;
      });

    });

});
