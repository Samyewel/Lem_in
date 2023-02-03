import subprocess
import sys
import os

class colour:
   PURPLE = '\033[95m'
   CYAN = '\033[96m'
   DARKCYAN = '\033[36m'
   BLUE = '\033[94m'
   GREEN = '\033[92m'
   YELLOW = '\033[93m'
   RED = '\033[91m'
   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   END = '\033[0m'


def prompt_user_for_flags():
    flags = {}
    options = ['flow1', 'flow10', 'flow1000', 'big', 'super']
    for i, option in enumerate(options):
        user_input = input(f'Enter 1 to set {option} or 0 to skip: ')
        if user_input == '1':
            flags[option] = True
        else:
            flags[option] = False
    return flags

if __name__ == '__main__':
    flags = prompt_user_for_flags()
    print(flags)