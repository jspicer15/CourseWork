import random
def count(arr, n):
	count = 0;
	for i  in range(0, n - 1):
		for j in range(i + 1, n):
			if arr[i] > arr[j]:
				count += 1
	print count

def create():
	i = 100000
	text = []
	while i > 0:
		text.append(i)
		i = i - 1
	for i in text:
		print i,
	return text

count(create(), 99999)
