function permute(text)
	key = Dict{Integer, Integer}(1=>3, 2=>2, 3=>4, 4=>1)
	newWord = Array(data(text))
	numGroups = length(text) / length(key)
	i = 0
	x = 1
	while i < numGroups
		newWord[x + i] = key[x]
		x+= 1
		if(x > 4)
			x = 0
		end
		i+= 1
	end
	newWord
end
