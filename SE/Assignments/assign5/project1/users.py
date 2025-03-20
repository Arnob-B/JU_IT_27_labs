import uuid
class User:
    
    def __init__(self, db) -> None:
        self.db = db;
        self.db.createTable("customer","id, fname , lname");
        self.db.createTable("retailer","id, fname , lname");
        pass

    def addRetailer(self, fname, lname):
        # use database query to list items
        id = uuid.uuid4();
        retailer = self.db.insert("retailer", f"'{id}','{fname}','{lname}'");
        return retailer
    def findRetailer(self, fname, lname):
        retailer = self.db.find("retailer", "*", f"fname='{fname}' AND lname='{lname}'")
        return retailer
    def removeRetailer(self,fname, lname):
        # use database query to list items
        response = self.db.delete("retailer", f"fname={fname} AND lname='{lname}'")
        print(response)

    def addCustomer(self, fname, lname):
        # use database query to list items
        id = uuid.uuid4();
        customer = self.db.insert("customer", f"'{id}','{fname}','{lname}'");
        return customer
    def findCustomer(self, fname, lname):
        customer = self.db.find("customer", "*", f"fname='{fname}' AND lname='{lname}'")
        return customer
    def removeCustomer(self,fname, lname):
        # use database query to list items
        response = self.db.delete("customer", f"fname={fname} AND lname='{lname}'")
        print(response)
