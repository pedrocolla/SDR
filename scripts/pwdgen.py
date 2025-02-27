import random

def randchar():
    while True:
        yield chr(48 + (random.getrandbits(30) % 75))

r = randchar()

def random_string(length):
    return ''.join((next(r) for _ in range(length)))

# Test
print("Random generated password is: [%s]" % random_string(8))
