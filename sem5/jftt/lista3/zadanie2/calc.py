P = 1234577

def modNorm(x, p = P):
	x %= p
	if x < 0:
		x += p
	return x

def modInv(a, p = P):
	def nwd(x,y):
		if y == 0:
			return x,1,0
		g,s,t = nwd(y, x%y)
		return g, t, s - (x //y) * t
	
	g, x, _ = nwd(a,p)
	if g != 1:
		return None
	return modNorm(x, p)