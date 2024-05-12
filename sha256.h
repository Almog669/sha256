//#pragma once
#ifndef SHA_H
#define SHA_H

#include <stdbool.h>//for bool
#include<string.h>// for strlen()
#include<stdio.h>// for printf()
#include<stdint.h>// for uint32_t
#include<math.h>//for sqroot()
#include<stdbool.h>//for true false

enum {a = 0,b ,c ,d ,e ,f ,g ,h};
/*Compression and messege Schedule :*/
void make_packet(char *inputname);
void compres_func(uint32_t m[],uint32_t H_vals[],uint32_t Working_vars[],uint32_t K_const[]);

/*Value Initialization functions :*/
uint32_t first_32_bits_of_sqrt(uint32_t num);
void prime_sqroot_rem(uint32_t arr[]);
bool is_prime(uint32_t num);
void k_constarr(uint32_t k[]);
uint32_t first_32_bits_of_cubed(uint32_t num);
uint32_t e_0(uint32_t n);
uint32_t e_1(uint32_t n);
uint32_t E_0(uint32_t n);
uint32_t E_1(uint32_t n);
uint32_t Ch(uint32_t Working_vars[]);
uint32_t Maj(uint32_t Working_vars[]);
uint64_t countrounds(char *input);
void setZero(uint32_t m[]);

/*Helper function to bitwise operations : */
uint32_t rotate_7(uint32_t n);
uint32_t rotate_2(uint32_t n);
uint32_t rotate_13(uint32_t n);
uint32_t rotate_22(uint32_t n);
uint32_t rotate_6(uint32_t n);
uint32_t rotate_11(uint32_t n);
uint32_t rotate_25(uint32_t n);
uint32_t rotate_18(uint32_t n);
uint32_t rotate_17(uint32_t n);
uint32_t rotate_19(uint32_t n);
uint32_t shift_10(uint32_t n);
uint32_t shift_3(uint32_t n);
uint32_t power_2(int pow);

/*Repesentational functions for bits for variables :*/
void bin(unsigned n);
void binchar(unsigned n);
void bin64(long long num);
int str_Bitlen(char *inputname);
void split_64bit_int(uint64_t num, uint32_t *left, uint32_t *right);
void printhash(uint32_t H_vals[]);

#endif