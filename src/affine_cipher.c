/*
 * the Affine cipher is a slightly more secure version of the caeser cipher, although still insecure
 * encryption: a * x + b % 128 (or ring size)
 * decryption: a^(-1) * (y-b) % 128 (or ring size)
 */

#include <stdlib.h>
#include <stdio.h>
#include "file_pack.h"

/*in C, the % operator returns the result remainder, and not necessarily the modulo
 *so it is necessary to write our own mod function. Since this will be used quite frequently I've made
  *it a macro*/
#define MOD(x, n) ((x % n + n) % n)

/*
 * In crytography, the ring size is defined as the size of the space of our possible values
 * since we are using ASCII (and will be for every program in this project) our ring size will
 * be a constant value of 128 
 */
#define RING_SIZE 128

void encrypt(FILE *in, FILE *out, int a, int b);
void decrypt(FILE *in, FILE *out, int a, int b);
int brute_force_inverse(int a);
int gcd_euclid(int a, int b);
int euclid_extended(int a, int b, int *x, int *y);

int main(int argc, char *argv[])
{
    file_s *in_file = open_file(argv[1], "r");
    file_s *out_file = open_file(argv[2], "w");
    int a = atoi(argv[3]);
    int b = atoi(argv[4]);
    char *mode = argv[5];
    if(mode[0] == 'e') encrypt(in_file->fp, out_file->fp, a, b);
    else if(mode[0] == 'd') decrypt(in_file->fp, out_file->fp, a, b);
    
    close_file(in_file);
    close_file(out_file);
    return 0;
}

/*takes every character from in_file and applies the cipher, and places it in outfile*/
void encrypt(FILE *in, FILE *out, int a, int b)
{
    char c;
    c = fgetc(in);
    printf("encrypting file...\n");
    while(c != EOF)
    {
	    c = MOD((c * a + b), RING_SIZE);
	    fputc(c, out);
	    c = fgetc(in);
    }
    printf("file encrypted\n");
}

/*takes every character from infile, undoes the cipher, and places it in outfile*/
void decrypt(FILE *in, FILE*out, int a, int b)
{
    char c;
    int inv_a = brute_force_inverse(a), y;
    euclid_extended(a, RING_SIZE, &inv_a, &y);
    c = fgetc(in);
    printf("decrypting file...\n");
    while(c != EOF)
    {
	    c = MOD((inv_a * (c - b)), RING_SIZE);
	    fputc(c, out);
	    c = fgetc(in);
    }
    printf("file decrypted\n");
}

/*
 * for the affine cipher, we must find the the invese of a to decrypt the
 * message. Since the Euclidean algorithm has not been covered yet, we will have to brute force it.
 * so, this function will return the invese of a given a modulus of 128 (ASCII table)
 */
int brute_force_inverse(int a)
{
    int inverse = - 1, c;
    for(c = 0; c < 128; c++)
    {
	    if(a * c % 128 == 1)
	    {
	        inverse = c; 
	        break;
	    }
    }
    printf("the inverse of %d is %d\n", a, inverse);
    return inverse;
}

/*the euclidean algorithm is a more efficient way to find the greatest common divisor of two integers x and y
 * more efficient than brute force, it returns the g = gcd(a, b)
 *
 * The algorithm is as follows: (note that b in our case is RING_SIZE of 128
 * if a < b switch a and b (does not apply to us since the RING_SIZE = 128 is our b)
 * R = remainder of a/b (a%b in our case, more specicially MOD(a, b))
 * a = b and b = r, repeat previous step
 * if the gcd of a and RING_SIZE is not 1, then a
 *
 * For use in this program, if the GCD(a, RING_SIZE=128) = 1, we can say that a has an inverse
 * in the integer ring RING_SIZE=128. This algorithm can be extended to find the inv_a in RING_SIZE
 * In a way that is more efficient than brute force*/
int gcd_euclid(int a, int b)
{
    int r = MOD(a, b), gcd;
    if(r == 0) return b;
    gcd = gcd_euclid(b, r);
    return gcd;
}

/*
 * The extended euclidean algorithm is a method for for finding inv_a in the ring b (in our case 128)
 * it returns the gcd of a and b, which we know is 1 - this function is called with the assumption the inv
 * of a exists in b.
 * the inv_a is stored in x
 * more efficient than brute force, this function can tell us if the inv_a exists in the given integer ring
 * and if it does, what inv_a is
 */
int euclid_extended(int a, int b, int *x, int *y)
{
    int x1, y1, gcd, r;
    if(a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    r = MOD(b, a);
    gcd = euclid_extended(r, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
    return gcd;
}

/*test to see if the functions are working properly:
void test(FILE* fp)
{
    int a = 5, b = 22, modulus = 128, inv_a = brute_force_inverse(a), enc_c, dec_c;
    char c = fgetc(fp);
    printf("beginning test...\n");
    while(c != EOF)
    {
        enc_c = MOD((a * c + b), modulus);
        dec_c = MOD(inv_a * (enc_c - b), modulus);
	    printf("c = %c = %d\tenc_c = %c = %d\tdec_c = %c = %d\t\n", c, c, enc_c, enc_c, dec_c, dec_c);
	    c = fgetc(fp);
    }
    printf("test done\n");
}
*/


