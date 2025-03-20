import os
import subprocess

class Git:
    def __init__(self):
        self.ensure_git_repo()

    def ensure_git_repo(self):
        # Check if `.git` folder exists; initialize if missing
        if not os.path.exists(".git"):
            print("Initializing Git repository...")
            output = subprocess.check_output("git init --quiet", shell=True)
        else:
            print("Git repository already initialized.")
    def stash(self, custom=""):
        try:
            if custom:
                response = subprocess.check_output(custom, shell=True, text=True)
            else: 
                response = subprocess.check_output("git add .", shell=True, text=True)
            print(response.strip())
        except subprocess.CalledProcessError as e:
            print(f"Error: {e.output.strip()}")

    def commit(self, message="updating ..."):
        self.stash()
        subprocess.check_output(f"git commit -m '{message}'", shell=True, text=False)

    def showLogs(self):
        try:
            response = subprocess.check_output("git log --oneline --graph --format='%s %ad' --date=format:'%Y-%m-%d %H:%M:%S'", shell=True, text=True)
            print(response.strip())
        except subprocess.CalledProcessError as e:
            print(f"Error: {e.output.strip()}")
