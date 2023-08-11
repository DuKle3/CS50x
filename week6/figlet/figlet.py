from pyfiglet import Figlet
import sys

figlet = Figlet()
if len(sys.argv) == 3 and (sys.argv[1] in ['-f', '--font']) and (sys.argv[2] in figlet.getFonts()):
    figlet.setFont(font=sys.argv[2])
    text = input("Type: ")
    print(figlet.renderText(text))
else:
    print("Invalid usage")
    sys.exit(1)