#include"sha256.h"



void split_64bit_int(uint64_t num, uint32_t *left, uint32_t *right) {
    // Extract the left 32 bits by shifting right by 32 bits
    *left = (int)(num >> 32);
    
    // Extract the right 32 bits by masking with 0xFFFFFFFF
    *right = (int)(num & 0xFFFFFFFF);
}

void bin(unsigned n)
{
    unsigned i = 1;
    for ( i = i << 31; i > 0; i = i / 2) {
        ((n & i) != 0)? printf("1"):printf("0");
    }
    printf("\n");
}

void binchar(unsigned n)
{
    unsigned i = 1;
    for ( i = i << 7; i > 0; i = i / 2) {
        ((n & i) != 0)? printf("1"):printf("0");
    }
}

void bin64(long long num) {
    for (int i = 63; i >= 0; i--) {
        putchar((num >> i) & 1 ? '1' : '0');
        if (i % 32 == 0) putchar('\n'); // Add space every 8 bits for readability
    }
    printf("\n");
}

int str_Bitlen(char *inputname){
    return strlen(inputname) * 8;
}

void make_packet(char *inputname) {
    printf("\nFirstly we make the packet 512 bits : \n\nAKA the messege schedule\n");
    uint32_t H_vals[8] = {0},K_const[63] = {0},Working_vars[8] = {0},leftbits,rightbits,m[64]={0};
    uint32_t *ptr1 = &leftbits,*ptr2 = &rightbits;
    uint64_t rounds = countrounds(inputname),bitlen = str_Bitlen(inputname);
    int linebreak = 0,j=0,shift = 24,i,cur_round,rows = 16,lastword = 64,pickoff=0;
    bool last = false; 

    prime_sqroot_rem(H_vals);
    prime_sqroot_rem(Working_vars);
    k_constarr(K_const);
    
    printf("Rounds :%lu\n", rounds);

    for( cur_round = 0; cur_round < rounds ; cur_round++){
        j = 0;
        linebreak = 0;
        if(cur_round > 0)
        setZero(m);
        if (cur_round == rounds -1){
            if( strlen(inputname) % 64 < 56 && strlen(inputname) % 64 != 0){
                lastword = strlen(inputname) % 64;
                last = true;
            }    
            if( strlen(inputname) % 64 > 55 && strlen(inputname) % 64 != 0){
                lastword = 0;
                last = true;    
            }
            if(  strlen(inputname) % 64 == 0){
                lastword = 0;
                last = true;
                m[j] += 1 << 31;    
            }
        }
        for (i = 0; i < lastword; i++) {
            if(inputname[i] == '\0')
                break;
            m[j] += ((int)(inputname[pickoff])) << shift;
            linebreak++;
            shift -= 8;
            pickoff++;
            if (linebreak == 4 && i != lastword -1 && inputname[i+1] != '\0'){
                printf("j is : %d ",j);
                bin(m[j]);
                linebreak = 0;                
                j++;
                shift = 24;
             }
            else if ( i == lastword -1 || inputname[i + 1] == '\0'){
                if(linebreak == 4){
                    printf("j is : %d ",j);
                    bin(m[j]);
                    if((j + 1) < 16){
                        printf("j is : %d ",j+1);
                        m[j+1] += 1 << 31;
                        bin(m[j+1]);
                        linebreak = 0;
                        j++;    
                    }
                }
            else{
                m[j] += 1 << (31 - (linebreak * 8));
                printf("j is : %d ",j);
                bin(m[j]);
                linebreak = 0;
                //j++;
            }
            j++;
         }
    }
        if(last)
            rows = 14;
        while(j < rows) {
            printf("j is : %d ",j);
            bin(m[j]);
            j++;
        }
        if(last){
            split_64bit_int(bitlen,ptr1,ptr2);
            m[j] = leftbits;
            m[j+1] = rightbits;
            printf("j is : %d ",j);
            bin(m[j]);
            printf("j is : %d ",j+1);
            bin(m[j+1]);
        }   
        for(j = 16 ; j < 64 ; j++){
            printf("j is : %d ",j);
            m[j] = e_1(m[j-2]) + m[j-7] + e_0(m[j-15]) + m[j-16];
            bin(m[j]);
        }
        compres_func(m,H_vals,Working_vars,K_const);
    }
    printhash(H_vals);

}

void compres_func(uint32_t m[],uint32_t H_vals[],uint32_t Working_vars[],uint32_t K_const[]){
    uint32_t t1;
    uint32_t t2;
    int i = 0;
    
    for(i = 0 ; i < 8 ;i++){
        printf("Working_vars[%d] :", i );
        Working_vars[i] = H_vals[i];
        bin(Working_vars[i]);
    }

    for(i = 0 ; i < 64 ; i++){
        t1 = Working_vars[h] + E_1(Working_vars[e]) + Ch(Working_vars) + K_const[i] + m[i];
        t2 = E_0(Working_vars[a]) + Maj(Working_vars);
        Working_vars[h] = Working_vars[g];
        Working_vars[g] = Working_vars[f];
        Working_vars[f] = Working_vars[e];
        Working_vars[e] = Working_vars[d] + t1;
        Working_vars[d] = Working_vars[c];
        Working_vars[c] = Working_vars[b];
        Working_vars[b] = Working_vars[a];
        Working_vars[a] = t1 + t2;
    }

    for(i = 0 ;i < 8; i++){
        H_vals[i] = H_vals[i] + Working_vars[i];
    }
}

uint32_t first_32_bits_of_sqrt(uint32_t num) {
    double int_part;
    double fraction = modf(sqrt(num), &int_part);
    return (uint32_t)(fraction * (1ULL << 32)); // Extract the first 32 bits of the fractional part
}

void printhash(uint32_t H_vals[]){
    printf("Hash Value : \n\n");
    for(int i = 0 ;i < 8; i++){
        printf("%08x", H_vals[i]);
    }
    printf("\n");
}

void prime_sqroot_rem(uint32_t arr[]){
    int j = 0;
    for(uint32_t i = 0 ; j < 8 ; i++){
        if(is_prime(i)){
            arr[j]=first_32_bits_of_sqrt(i);
            j++;
        }
    }
}

bool is_prime(uint32_t num) {
    if (num <= 1) {
        return false; // 0 and 1 are not prime
    }
    if (num <= 3) {
        return true; // 2 and 3 are prime
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return false; // Multiple of 2 or 3
    }
    for (uint32_t i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false; // Multiple of (6k ± 1)
        }
    }
    return true;
}

void k_constarr(uint32_t k[]) {
    int count = 0; 
    uint32_t num = 2; 
        // Check if the current number is prime
        // If the number is prime, calculate its cube and store the remainder after the decimal point
        while (count < 64){
            if (is_prime(num)){
                uint32_t remainder = first_32_bits_of_cubed(num); // Get the first 32 bits after the decimal point
                k[count++] = remainder;
            }
            num++;    
        }
}

uint32_t first_32_bits_of_cubed(uint32_t num) {
    double int_part;
    double fraction = modf(cbrt(num), &int_part);
    return (uint32_t)(fraction * (1ULL << 32)); // Extract the first 32 bits of the fractional part
}

uint32_t e_0(uint32_t n){
    if(n == 0)
       return 0;
    return rotate_7(n) ^ rotate_18(n) ^ shift_3(n);
}

uint32_t e_1(uint32_t n){    
    if(n == 0)
       return 0;
    return rotate_19(n) ^ rotate_17(n) ^ shift_10(n);    
}

uint32_t E_0(uint32_t n){
    if(n == 0)
       return 0;
    return rotate_2(n) ^ rotate_13(n) ^ rotate_22(n);
}

uint32_t E_1(uint32_t n){
    if(n == 0)
       return 0;
    return rotate_6(n) ^ rotate_11(n) ^ rotate_25(n);
}

uint32_t Ch(uint32_t Working_vars[]){
    enum {a=0,b,c,d,e,f,g};
    return (Working_vars[e] & Working_vars[f]) ^ (~Working_vars[e] & Working_vars[g]);
}

uint32_t Maj(uint32_t Working_vars[]){
    enum {a=0,b,c,d,e,f,g};
    return (Working_vars[a] & Working_vars[b]) ^ (Working_vars[a] & Working_vars[c]) ^ (Working_vars[b] & Working_vars[c]);
}

uint32_t rotate_7(uint32_t n){
       return (n >> 7) | (n << (sizeof(n) * 8 - 7));
}

uint32_t rotate_18(uint32_t n){
    return (n >> 18) | (n << (sizeof(n) * 8 - 18));
}

uint32_t rotate_17(uint32_t n){
    return (n >> 17) | (n << (sizeof(n) * 8 - 17));
}

uint32_t rotate_19(uint32_t n){
    return (n >> 19) | (n << (sizeof(n) * 8 - 19));
}

uint32_t shift_10(uint32_t n){
    return n >> 10;
}

uint32_t shift_3(uint32_t n){
    return n >> 3;
}

uint32_t power_2(int pow){
    if(pow == 0 )
        return 1;
    else{
        int count = 1,res = 2; 
        while(count < pow){
            res *= 2;
            count++;
        }
        return res;
    } 
}

uint32_t rotate_6(uint32_t n){
    return (n >> 6) | (n << (sizeof(n) * 8 - 6));
}

uint32_t rotate_11(uint32_t n){
    return (n >> 11) | (n << (sizeof(n) * 8 - 11));
}

uint32_t rotate_25(uint32_t n){
    return (n >> 25) | (n << (sizeof(n) * 8 - 25));
}

uint32_t rotate_2(uint32_t n){
    return (n >> 2) | (n << (sizeof(n) * 8 - 2));
}

uint32_t rotate_13(uint32_t n){
    return (n >> 13) | (n << (sizeof(n) * 8 - 13));
}

uint32_t rotate_22(uint32_t n){
    return (n >> 22) | (n << (sizeof(n) * 8 - 22));
}

uint64_t countrounds(char *input){
    uint64_t len = strlen(input);
    uint64_t res;
    
    if(len < 56)
        res = 1;
    else if (len > 55 && len <= 64)
        res = 2;
    else if (len > 64 && (len % 64) < 56)
        res = len / 64 + 1;
    else if (len > 64 && (len % 64) > 55)
        res = len / 64 + 2;
    
    return res;
}

void setZero(uint32_t m[]){
    for(int i = 0 ; i < 63 ; i++){
        m[i] = 0;
    }
}