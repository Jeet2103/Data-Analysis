import random

# Create a list of numbers from 1 to 100
numbers = list(range(1, 101))

# Shuffle the list
random.shuffle(numbers)

# Now you can pick values one by one from the shuffled list
random_value = numbers.pop()

print(random_value)
