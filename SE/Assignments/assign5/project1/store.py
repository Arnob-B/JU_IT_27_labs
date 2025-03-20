from banner import Banner
from items import Item
from lib.console import eraseConsole
from services.db import DB
from services.git import Git
from users import User

class Store:
    banner = Banner();
    def __init__(self):
        self.git = Git();
        self.db = DB("test.db");
        self.users = User(self.db)
        self.items = Item(self.db);
        self.git = Git();
        print('''
              intializing project
              ''');
        self.banner.progress_bar(20, 1)
        eraseConsole();
        

    def start(self):
        [userId, userType] = self.userDetails();
        eraseConsole();
        self.userId = userId;
        self.userType = userType;
        self.banner.greetingPanel();
        while(True):
            if(self.userType=='customer'):
                self.itemPromptForCustomer();
            else:
                self.itemPromptForRetailer();
            choice = input("press y to continue : ");
            if(not choice in {'y',  'Y'}):
                break;
            eraseConsole();

    def itemPromptForRetailer(self):
        while(True):
            print('''
                  1. To add item
                  2. To update item
                  3. To delete item
                  4. List all items
                  ''')
            choice = input("Enter your choice -> ")
            if(choice in ('1','2','3', '4')):
                break
        if(choice == '1'):
            name = input("name : ");
            if(self.items.listItemByName(name)!=[]):
                print("item already present");
                return
            quantity = int(input("quantity : "));
            price = float(input("price : "));
            self.items.addItem(name,name,quantity,price);
            self.git.commit(f"item added {name}|{quantity}|{price}")
        if(choice == '2'):
            id = input("id : ");
            item = self.items.listItemByID(id);
            if(item == []):
                print("item not found");
                return
            print("item details ", item[0]);
            updatedQuantity = int(input("updated quantity : "));
            updatedPrice = float(input("updated price : "));
            self.items.modifyItem(id,updatedQuantity, updatedPrice);
            self.git.commit(f"item modified {id}|{updatedQuantity}|{updatedPrice}")
        if(choice == '3'):
            id = input("id : ");
            self.items.removeItem(id);
            self.git.commit(f"item removed {id}")
        if(choice == '4'):
            items = self.items.listAllItems();
            print("all items")
            for i in items:
                print(f"{i[0]} | {i[1]} | {i[2]} | {i[3]} |");

    def itemPromptForCustomer(self):
        while(True):
            print('''
                  1. To list all items
                  2. Search for a item
                  3. purchase a item
                  4. purchase history
                  ''')
            choice = input("Enter your choice -> ")
            if(choice in ('1','2','3','4')):
                break
        if(choice == '1'):
            items = self.items.listAllItems();
            print("all items")
            for i in items:
                print(f"{i[0]} | {i[1]} | {i[2]} | {i[3]} |");
        if(choice == '2'):
            id = input("id : ");
            response = self.items.listItemByID(id);
            if(not response):
                print(f"item not found")
                return;
            item = response[0];
            self.items.printItem(item[0], item[1], item[2], item[3]);
        if(choice == '3'):
            itemId = input("item id : ");
            quantity = input("quantity : ")
            self.items.purchaseItem(self.userId, itemId, quantity);
            self.git.commit("item purchased")
        if(choice == '4'):
            response = self.items.purchaseItemsHistory(self.userId);
            print(response)

    def userDetails(self):
        print("1. Customer");
        print("2. Retailer");
        choice = input("Enter as 1 or 2 : ");
        if(choice != '1' and choice != '2'):
            return self.userDetails();
        else: 
            fname = input("enter first name : ")
            lname = input("enter last name : ")
            if(choice == '1'):
                user  = self.users.findCustomer(fname, lname);
            else:
                user  = self.users.findRetailer(fname, lname);
            if(user == []):
                if(choice == '1'):
                    self.users.addCustomer(fname, lname);
                    user  = self.users.findCustomer(fname, lname);
                else:
                    self.users.addRetailer(fname, lname);
                    user  = self.users.findRetailer(fname, lname);
                userId = user[0][0];
            else:
                userId = user[0][0];
            return [userId, 'customer' if choice=='1' else 'retailer'];

store = Store();

userid = store.start();
