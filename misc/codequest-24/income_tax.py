import math

def test_case():
	n = int(input())
	
	if n >= 578126:
		print(round(n*.37))
	elif n >= 231251:
		print(round(n*.35))
	elif n >= 182101:
		print(round(n*.32))
	elif n >= 95376:
		print(round(n*.24))
	elif n >= 44726:
		print(round(n*.22))
	elif n >= 11001:
		print(round(n*.12))
	else:
		print(round(n*.1))

t = int(input())

for i in range(t):
	test_case()
