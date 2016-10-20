import random
def create():
	i = 5000
	text = ""
	print '['
	while i > 1:
		text += random.randint(1,100000)
		text += ','
		i = i - 1
	text += random.randint(1,100000)
	text += ']'
	return text
