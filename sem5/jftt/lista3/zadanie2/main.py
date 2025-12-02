from lexer import lexer, tokens
from parser import parser

def processLine(line):
	try:
		result = parser.parse(line)
	except ZeroDivisionError:
		print("Błąd: dzielenie przez 0.")
		return
	except SyntaxError:
		print("Błąd: niepoprawne wyrażenie.")
		return
	
	value, _, onp = result
	print(' '.join(onp))
	print("Wynik: " + str(value))

def readMulti():
	buffer = ""
	while True:
		line = input().strip()
		if line.endswith('\\'):
			buffer += line[:-1].rstrip() + " "
			continue
		else:
			buffer += line
			return buffer.strip()

def main():
	while True:
		try:
			line = readMulti()
		except EOFError:
			break

		if line.startswith('#'):
			continue

		if line == "exit":
			break
		
		processLine(line)

if __name__ == '__main__':
	main()