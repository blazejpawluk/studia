import ply.yacc as yacc
from lexer import tokens
import calc

precedence = (
	('left', 'ADD', 'SUB'),
	('left', 'MUL', 'DIV', 'MOD'),
	('right', 'POW'),
	('right', 'UMINUS'),
)

def p_expression_number(p):
	'expression : NUMBER'
	val = calc.modNorm(p[1])
	p[0] = (val, True, [str(val)])

def p_expression_group(p):
	'expression : LPAREN expression RPAREN'
	val, literal, onp = p[2]
	val = calc.modNorm(val)
	p[0] = (val, literal, onp)

def p_expression_uminus(p):
	'expression : SUB expression %prec UMINUS'
	val, literal, onp = p[2]
	val = calc.modNorm(calc.P - val)
	if literal:
		p[0] = (val, True, [str(val)])
	else:
		p[0] = (val, False, onp + ["NEG"])

def p_expression_add(p):
	'expression : expression ADD expression'
	left, _, onpl = p[1]
	right, _,onpr = p[3]
	left = calc.modNorm(left)
	right = calc.modNorm(right)
	p[0] = (calc.modNorm(left + right), False, onpl + onpr + ["+"])

def p_expression_sub(p):
	'expression : expression SUB expression'
	left, _, onpl = p[1]
	right, _, onpr = p[3]
	left = calc.modNorm(left)
	right = calc.modNorm(right)
	p[0] = (calc.modNorm(left - right), False, onpl + onpr + ["-"])

def p_expression_mul(p):
	'expression : expression MUL expression'
	left, _, onpl = p[1]
	right, _, onpr = p[3]
	left = calc.modNorm(left)
	right = calc.modNorm(right)
	p[0] = (calc.modNorm(left * right), False, onpl + onpr + ["*"])

def p_expression_div(p):
	'expression : expression DIV expression'
	left, _, onpl = p[1]
	right, _, onpr = p[3]
	left = calc.modNorm(left)
	right = calc.modNorm(right)
	inv = calc.modInv(right)
	if right == 0 or inv == 0:
		raise ZeroDivisionError
	p[0] = (calc.modNorm(left * inv), False, onpl + onpr + ["/"])

def p_expression_mod(p):
	'expression : expression MOD expression'
	left, _, onpl = p[1]
	right, _, onpr = p[3]
	left = calc.modNorm(left)
	right = calc.modNorm(right)
	if right == 0:
		raise ZeroDivisionError
	p[0] = (calc.modNorm(left % right), False, onpl + onpr + ["%"])

def p_expression_pow(p):
	'expression : expression POW exponent'
	left, _, onpl = p[1]
	right, _, onpr = p[3]
	left = calc.modNorm(left)
	right = calc.modNorm(right, calc.P-1)
	p[0] = (calc.modNorm(pow(left, right)), False, onpl + onpr + ["^"])

def p_exponent_number(p):
	'exponent : NUMBER'
	'expression : NUMBER'
	val = calc.modNorm(p[1], calc.P-1)
	p[0] = (val, True, [str(val)])

def p_exponent_group(p):
	'exponent : LPAREN exponent RPAREN'
	val, literal, onp = p[2]
	val = calc.modNorm(val, calc.P-1)
	p[0] = (val, literal, onp)

def p_exponent_uminus(p):
	'exponent : SUB exponent %prec UMINUS'
	val, literal, onp = p[2]
	val = calc.modNorm(calc.P-1 - val, calc.P-1)
	if literal:
		p[0] = (val, True, [str(val)])
	else:
		p[0] = (val, False, onp + ["NEG"])

def p_error(p):
	raise SyntaxError("Niepoprawne wyrażenie")

parser = yacc.yacc()