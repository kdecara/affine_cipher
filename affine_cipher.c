/*
 * the Affine cipher is a slightly more secure version of the caeser cipher, although still insecure
 * encryption: a * x + b % 128 (or ring size)
 * decryption: a^(-1) * (y-b) % 128 (or ring size)
 */

#include <stdlib.h>
#include <stdio.h>
#include "../file_pack.h"

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

void decrypt(FILE *in, FILE*out, int a, int b)
{
    char c;
    int inv_a = brute_force_inverse(a);
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
    int inverse, c;
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

/*why are some letters not being decrypyed properly? we can start with the most common occurence noted
 *the letter e*/
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


