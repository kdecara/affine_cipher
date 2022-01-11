# Affine Cipher
The affine cipher is a generalized version of the ceaser or shift cipher. It encrypts by multyplying one part of the plain text by one part of the key - A - followed by
the addition of another part of the key - B. While not secure, implementing the affine cipher can still serve to practice programming skills and learn about cryptography.

# Encryption-Decryption

E(x) = y = a * x + B % 128

D(y) = x = inv_a * (y-b) % 128

Where inv_a is the modular multiplicative inverse of A in the ring of 128. Note that since A needs to be inverted for decryption, it has a restriction of gcd(a, 128) = 1. For the
inv of a to exist, it must be relatively prime with the ring size meaning gcd(a, ring_size) = 1. 

# Brute Force to Find Inverse
We can simple iteraty over all numbers i= {0, ... ,127} and check if their greatest common divisor is 1. With the ASCII key space of 128, this is not computationally expensive,
but a more efficient solution is implemented via Euclid's Algorithm

# Euclid's Algorithm
  1. If a<b, exchange a and b. (does not apply to us, since we know a will always be less than b=RING_SIZE)
  2. Divide a by b and get the remainder, r. If r=0, report b as the GCD of a and b.
  3. Replace a by b and replace b by r. Return to the previous step
Euclid's Algorithm is more efficent that brute force (at least in the worst case) and has applications for other cryptographic algorithms as well
Euclid's extended algorithm can be used to find the key's originially used for encryption and is implemented in the solution

# Cryptanalysis
The affine cipher makes the solution set slightly larger than the shift cipher 12(possible a vals) X 128(possible b vals) = 1536 possible solutions vs the 128 for the shift cipher.
So, a brute force attack is still trivial. Like the shift cipher, the affine cipher is also susceptible to letter frequency analysis, which is implemented in solution as well.
