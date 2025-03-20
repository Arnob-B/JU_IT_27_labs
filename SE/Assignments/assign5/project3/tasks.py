class Tasks:
    def __init__(self, db) -> None:
        self.db = db;
        self.db.createTable("tasks", "id, title, description, ownerId,status");
        print("tasks table created")
        pass

    def completeTask(self, ownerId, taskID):
        task = self.db.find('tasks', '*', f"ownerID='{ownerId}' AND id='{taskID}'");
        if(not task):
            return False;
        self.db.update('tasks', f"id='{taskID}'", f"status='completed'")
        return True;

    def taskHistory(self, ownerId):
        return self.db.find('tasks', '*', f"ownerId='{ownerId}'")

    def listAllTasks(self):
        items = self.db.find("tasks", '*');
        return items;

    def addTask(self,ownerId,  id, title, description , status):
        insertQuery = f"'{id}','{title}','{description}','{ownerId}','{status}' ";
        self.db.insert("tasks", insertQuery)

    def listTaskById(self, taskID):
        items = self.db.find("tasks", '*', f"id='{taskID}'");
        return items;
    def listTaskByTitle(self, title):
        items = self.db.find("tasks", '*', f"title='{title}'");
        return items;

    def removeTask(self, id):
        self.db.delete("tasks", f"id = '{id}'")

    def modifyTask(self, id, title, description):
        self.db.update("tasks", f"id = '{id}'", f"title='{title}', description='{description}'")
