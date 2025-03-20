import sqlite3
class DB:
    def __init__(self,dbURI):
        self.connect(dbURI);
        pass

    def connect(self, dbURI):
        self.dbURI = dbURI;
        try:
            self.con = sqlite3.connect(dbURI);
            self.cursor = self.con.cursor();
            print("☑️ connected to database")
        except:
            print("unable to connect to db ")

    def find(self, tableName, projectQuery, searchQuery = "" , errorMsg = "unable to find "):
        if(searchQuery == ""):
            query = f"SELECT {projectQuery} FROM {tableName}"
        else: 
            query = f"SELECT {projectQuery} FROM {tableName} WHERE {searchQuery}"
        return self.customExecute(query, errorMsg)

    def update(self, tableName, searchQuery, updateQuery, errorMsg ="unable to update"):
        query = f"UPDATE {tableName} SET {updateQuery} WHERE {searchQuery}"
        response =  self.customExecute(query, errorMsg)
        self.con.commit();
        return response;
    def delete(self, tableName, searchQuery, errorMsg ="unable to delete"):
        query = f"DELETE FROM {tableName} WHERE {searchQuery}"
        response =  self.customExecute(query, errorMsg)
        self.con.commit();
        return response;

    def insert(self, tableName, values,errorMsg="unable to insert"):
        query = f"INSERT INTO {tableName} VALUES ({values})"
        print(query)
        response = self.customExecute(query, errorMsg)
        self.con.commit();
        return response;

    def createTable(self, tableName, props,errorMsg="unable to create table"):
        query = f"CREATE TABLE IF NOT EXISTS {tableName}({props})"
        response = self.customExecute(query, errorMsg)
        self.con.commit();
        print("created table", tableName)
        return response;

    def customExecute(self, query, errorMsg = "unable to execute query"):
        try:
            response = self.cursor.execute(query)
            print("☑️ query executed")
            data =  response.fetchall()
            return data;
        except Exception as e:
            print(errorMsg)
            print(e)
        
