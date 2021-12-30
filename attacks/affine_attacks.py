import os
import sys

RING_SIZE = 128

#data structure to hold the solution set given ring size 
class AffineSolutionSet:
    def __init__(self, ring_size: int):
        self.b = list() #list of all possible b vals
        self.a_pairs = dict() #dictionary of all possible keys a:inv_a
        self.ring_size = ring_size #ring size, presumed to be 128, but made modular
        for i in range(ring_size):
            possible_a_vals = euclid_extended(i, self.ring_size)
            if(possible_a_vals[0] == 1): self.a_pairs[i] = possible_a_vals[1]
            self.b.append(i)

#given a possible key for a, return a list that contains:
#list[0] = the gcd of a and the ring_size (will be 1 if they are coprime, and the parameter is a possible key)
#list[1] = the modular multiplicative inverse of a in the ring 
#list[2] = the modular multuplicative inverse of b in the ring
def euclid_extended(a: int, b: int) -> tuple():
    if(a == 0) : return b, 0, 1
    r = int(b) % int(a)
    gcd, x1, y1 = euclid_extended(r, a)
    x = y1 - (b//a) * x1
    y = x1
    return gcd, x, y


#def decrypt(cipher_text, key):
#    plain_text = ""
#    for i in cipher_text:
#        char = chr( (ord(i) - key) % RING_SIZE  )
#        plain_text += char
#    return plain_text 


#open the file and read it's contents into a buffer
def load_buffer(file_name):
    size = os.path.getsize(file_name)
    buffer = ""
    with open(file_name, 'r') as f:
        buffer = f.read(size)
    return buffer

file_name = sys.argv[1]
buffer = load_buffer(file_name)
#solution set defined, now it is only a question of findig the one which produces readable plaintext
solutions = AffineSolutionSet(RING_SIZE)
solution_set = solutions.a_pairs
print(solution_set)

