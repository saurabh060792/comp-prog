def find_repeating_decimal(numerator, denominator):
    remainders = {}
    result = ""
    remainder = numerator % denominator
    index = 0

    while remainder != 0 and remainder not in remainders:
        remainders[remainder] = index
        remainder *= 10
        result += str(remainder // denominator)
        remainder %= denominator
        index += 1

    if remainder in remainders:
        start_index = remainders[remainder]
        return result[start_index:]
    else:
        return ""

max_rep = 0
for i in range(2, 1001):
	repeating_part = find_repeating_decimal(1, i)
	if (len(repeating_part) >= max_rep) :
		max_rep = len(repeating_part)
		print(str(i) + " " + str(repeating_part))
