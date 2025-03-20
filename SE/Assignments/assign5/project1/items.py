class Item:
    
    def __init__(self, db) -> None:
        self.db = db;
        self.db.createTable("items", "id, name, quantity, price");
        self.db.createTable("purchases", "customerId,itemId, quantity, totalPrice");
        print("items table created")

        pass
    def purchaseItem(self, customerId, itemId, purchaseQuantity):
        # decreasing the 
        response = self.listItemByID(itemId);
        item = response[0]; # id, name, quantity, price
        price = float(item[3]);
        presentQuantity = int(item[2]);
        newQuantity = int(presentQuantity) - int(purchaseQuantity);
        if(newQuantity< 0):
            print("stocks unavailable !!!");
            return
        self.modifyItem(itemId, newQuantity, price);
        self.db.insert("purchases", f"'{customerId}', '{itemId}','{purchaseQuantity}' , '{float(price) * int(purchaseQuantity)}'");

    def purchaseItemsHistory(self, customerId):
        return self.db.find('purchases', '*', f"customerId='{customerId}'")

    def listAllItems(self):
        # use database query to list items
        items = self.db.find("items", '*');
        return items;

    def addItem(self, id, name, quantity , price):
        # use database query to list items
        self.db.insert("items", f"'{id}','{name}','{quantity}','{price}' ")
    def listItemByID(self, id):
        items = self.db.find("items", '*', f"id='{id}'");
        return items;
    def listItemByName(self, name):
        items = self.db.find("items", '*', f"name='{name}'");
        return items;

    def removeItem(self, id):
        # use database query to list items
        self.db.delete("items", f"id = '{id}'")

    def printItem (self,id, name, quantity, price):
        print(f"\nITEM \nID : {id}\nName : {name}\nQuantity : {quantity}\nPrice : {price}");
    def modifyItem(self, id, updatedQty, updatedPrice):
        # use database query to list items
        self.db.update("items", f"id = '{id}'", f"quantity={updatedQty} , price={updatedPrice}")
