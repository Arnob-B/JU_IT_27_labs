import uuid
class User:
    
    def __init__(self, db) -> None:
        self.db = db;
        self.db.createTable("users","id, fname , lname");
        pass

    def addUser(self, fname, lname):
        # use database query to list items
        id = uuid.uuid4();
        user = self.db.insert("users", f"'{id}','{fname}','{lname}'");
        print("user added ", user);
        return user;

    def findUser(self, fname, lname):
        user = self.db.find("users", "*", f"fname='{fname}' AND lname='{lname}'")
        return user;

    def removeUser(self,fname, lname):
        # use database query to list items
        response = self.db.delete("users", f"fname={fname} AND lname='{lname}'")
        print(response)
