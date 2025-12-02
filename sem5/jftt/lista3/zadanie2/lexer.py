import ply.lex as lex

tokens = ('NUMBER', 'ADD', 'SUB', 'MUL', 'DIV', 'MOD', 'POW', 'LPAREN', 'RPAREN')

def t_COMMENT(t):
	r'\#.*'
	pass

def t_NUMBER(t):
	r'\d+'
	t.value = int(t.value)
	return t

t_ADD  = r'\+'
t_SUB = r'\-'
t_MUL  = r'\*'
t_DIV   = r'/'
t_MOD   = r'%'
t_POW   = r'\^'
t_LPAREN = r'\('
t_RPAREN = r'\)'

t_ignore = ' \t'

def t_error(t):
	t.lexer.skip(1)

lexer = lex.lex()