import sys
import time

class Banner:
    def animated_text(self,text, delay=0.1):
        for char in text:
            sys.stdout.write(char)
            sys.stdout.flush()
            time.sleep(delay)
        print()  # Move to the next line after animation

    def progress_bar(self, total=30, duration=5 ):
        interval = duration / total
        for i in range(total + 1):
            bar = '#' * i + '-' * (total - i)
            percent = (i / total) * 100
            sys.stdout.write(f"\r[{bar}] {percent:.1f}%")
            sys.stdout.flush()
            time.sleep(interval)
        print()  # Move to the next line after animation
    def spinner(self,total_duration=5, spin_duration=0.5):
        chars = ['|', '/', '-', '\\']
        total_cycles = int(total_duration / spin_duration)  # Calculate total cycles
        delay_per_frame = spin_duration / len(chars)        # Delay per character frame

        for _ in range(total_cycles):
            for char in chars:
                sys.stdout.write(f"\rLoading... {char}")
                sys.stdout.flush()
                time.sleep(delay_per_frame)
    def greetingPanel(self):
        text = """
\t ▗▖ ▗▖▗▄▄▄▖▗▖    ▗▄▄▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖ \t\t ▗▄▄▄▖▗▄▖ 
\t ▐▌ ▐▌▐▌   ▐▌   ▐▌   ▐▌ ▐▌▐▛▚▞▜▌▐▌    \t\t   █ ▐▌ ▐▌
\t ▐▌ ▐▌▐▛▀▀▘▐▌   ▐▌   ▐▌ ▐▌▐▌  ▐▌▐▛▀▀▘ \t\t   █ ▐▌ ▐▌
\t ▐▙█▟▌▐▙▄▄▖▐▙▄▄▖▝▚▄▄▖▝▚▄▞▘▐▌  ▐▌▐▙▄▄▖ \t\t   █ ▝▚▄▞▘
\t                                                   
\t 
\t\t ███████╗████████╗ ██████╗ ██████╗ ███████╗
\t\t ██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██╔════╝
\t\t ███████╗   ██║   ██║   ██║██████╔╝█████╗  
\t\t ╚════██║   ██║   ██║   ██║██╔══██╗██╔══╝  
\t\t ███████║   ██║   ╚██████╔╝██║  ██║███████╗
\t\t ╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝
              """
        print(text);
    def choiceFooter(self):
        print("choose any one the following --> ", end="")
    def avaterChoice(self):
        print("Choose any one")
        print("1. Customer")
        print("2. Retailer")
    def selection(self):
        print("Enter Your first name : ")
        print("Enter Your last name : ")
    def optionsMenu(self, whoami):
        print("Options")
        if(whoami == "customer"):
            print("1. List all the items")
            print("2. Search for a item")
            print("3. purchase a item(via purchase Id)")
        else : 
            print("1. List all the items")
            print("2. Add a item")
            print("3. modify item")
            print("4. remove item")
        self.choiceFooter()
