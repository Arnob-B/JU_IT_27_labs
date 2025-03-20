from banner import Banner
from tasks import Tasks
from lib.console import eraseConsole
from services.db import DB
from services.git import Git
from users import User

class Store:
    banner = Banner();
    def __init__(self):
        self.git = Git();
        self.db = DB("TaskDatabase.db");
        self.users = User(self.db)
        self.tasks = Tasks(self.db);
        self.git = Git();
        print('''
              intializing project
              ''');
        self.banner.progress_bar(20, 1)
        eraseConsole();
        

    def start(self):
        userId = self.userDetails();
        eraseConsole();
        self.userId = userId;
        print(self.userId);
        self.banner.greetingPanel();
        while(True):
            self.taskPromptForUser();
            choice = input("press y to continue : ");
            if(not choice in {'y',  'Y'}):
                break;
            eraseConsole();

    def taskPromptForUser(self):
        while(True):
            print('''
                  1. add task
                  2. update task
                  3. complete task
                  4. List all task
                  ''')
            choice = input("Enter your choice -> ")
            if(choice in ('1','2','3', '4')):
                break
        if(choice == '1'):
            id = input("id : ");
            if(self.tasks.listTaskById(id)!=[]):
                print("item already present");
                return
            title = input("title : ");
            description = input("description : ");
            self.tasks.addTask(id,title,description,self.userId,"pending");
            self.git.commit(f"task added {id}|{title}|{description}|pending for {self.userId}");
        if(choice == '2'):
            id = input("id : ");
            item = self.tasks.listTaskById(id);
            if(item == []):
                print("task not found");
                return
            print("item details ", item[0]);
            title = input("updated title : ");
            description = input("updated description : ");
            self.tasks.modifyTask(id,title, description);
            self.git.commit(f"task modified {id}|{title}|{description}")
        if(choice == '3'):
            id = input("id : ");
            self.tasks.completeTask(self.userId,id);
            self.git.commit(f"item removed {id}")
        if(choice == '4'):
            #items = self.tasks.taskHistory(self.userId);
            tasks = self.tasks.listAllTasks();
            print(tasks);
            print("all tasks")
            for i in tasks:
                print(f"{i[0]} | {i[1]} | {i[2]} | {i[3]} |");


    def userDetails(self):
        fname = input("enter first name : ")
        lname = input("enter last name : ")
        user  = self.users.findUser(fname, lname);
        if(user == []):
            self.users.addUser(fname, lname);
            user =self.users.findUser(fname, lname);
            userId = user[0][0];
        else:
            userId = user[0][0];
        return userId;

store = Store();

userid = store.start();
