const mongoCollections = require("./mongoCollections");
const todo = mongoCollections.todoItems;
const uuidV4 = require('uuid/v4');

Date.prototype.yyyymmdd = function() {
  var mm = this.getMonth() + 1; // getMonth() is zero-based
  var dd = this.getDate();

  return [this.getFullYear(), ":",
          (mm>9 ? '' : '0') + mm, ":",
          (dd>9 ? '' : '0') + dd, ":"
         ].join('');
};
var date = new Date();

let exportedMethods = {
  createTask(title, description) {
      if (!title)
        return Promise.reject("You must provide a title for the task");

      if (!description)
        return Promise.reject("You must provide a description for the task");

      return todo().then((todoCollection) => {
        var newTask = {
          _id: uuidV4(),
          title: title,
          description: description,
          completed: false,
          completedAt: null
        };

        return todoCollection.insertOne(newTask).then((newInsertInformation) => {
          return newInsertInformation.insertedId;
        }).then((newId) => {
          return this.getTask(newId);
        });
    });
  },

  getAllTasks() {
    return todo().then((todoCollection) => {
      return todoCollection.find().toArray();
    });
  },

  getTask(id) {
    if (id === undefined || typeof id !== "string"){
        return Promise.reject("Must be a valid id.");
    }

    return todo().then((todoCollection) => {
        return todoCollection.findOne({ _id: id });
    });
  },

  completeTask(taskId) {
    if (taskId === undefined  || typeof taskId !== "string"){
      return Promise.reject("Must be a valid id.");
    }
    return todo().then((todoCollection) => {
      var currTime = date.yyyymmdd();
      return todoCollection.updateOne({ _id: taskId }, { $set: {completed : true, completedAt : currTime } }).then((result) => {
            return this.getTask(taskId);
      });
    });
  },

  removeTask(id) {
    if (id === undefined || typeof id !== "string"){
      return Promise.reject("Must be a valid id.");
    }
    return todo().then((todoCollection) => {
        return todoCollection.removeOne({ _id: id }).then((deletedInfo) => {
            if (deletedInfo.deletedCount === 0) {
                throw (`Could not delete task with id: ${id}`)
            }
        });
    });
  },

  clearDB() {
    return todo().then((todoCollection) => {
      return todoCollection.remove();
    });
  }
}

module.exports = exportedMethods;
