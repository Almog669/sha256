#include<stdio.h>
#include"sha256.h"
#include <math.h>

/*--------------------Helper functions:------------------------------------- */
void calculate_constants(uint32_t k[]) {
    int count = 0; 
    uint32_t num = 2; 
        // Check if the current number is prime
        // If the number is prime, calculate its cube and store the remainder after the decimal point
        while (count < 63){
            if (is_prime(num)){
                printf("count in : %d \n", count);
                uint32_t remainder = first_32_bits_of_cubed(num); // Get the first 32 bits after the decimal point
                bin(remainder);
                k[count++] = remainder;
                printf("remainder cubed root of %u: First 32 bits: 0x%08X in bin :", num, k[count-1]);
                bin(k[count-1]);
            }
            num++;    
        }
}

uint32_t primes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
    59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
    191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
    257, 263, 269, 271, 277, 281, 283, 293, 307, 311
};

void first_64_primes(){
    int count = 0,num = 2;
    while (count < 64){
            if (is_prime(num)){
                printf("at index %d is a prime : %d\n", count,num);
                count++;
            }
            num++;    
        } 
}

uint32_t k1[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t H[8] ={0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f,
0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

void compare_arrays(uint32_t arr1[], uint32_t arr2[], int size) {
    for (int i = 0; i < size; ++i) {
        if (arr1[i] != arr2[i]) {
            printf("not equal\n"); 
            printf("value arr1%u at index :%d\n", arr1[i],i);
            printf("value arr2%u at index :%d\n", arr2[i],i);
            printf("%08X\n", arr1[i]);
            printf("%08X\n", arr2[i]);
            return;// Arrays are not equal
        }
    }
    printf("equal\n"); // Arrays are equal
}

int main() {
    char *str = "wake up ";
    make_packet(str);
    return 0;
}
