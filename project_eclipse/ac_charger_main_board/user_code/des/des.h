#ifndef _DES_H_
#define _DES_H_

#define ENCRYPTION_MODE 1
#define DECRYPTION_MODE 0

typedef struct {
    unsigned char k[8];
    unsigned char c[4];
    unsigned char d[4];
} key_set;

void des_key_generate(unsigned char* key);
void des_sub_keys_generate(unsigned char* main_key, key_set* key_sets);
void des_message_process(unsigned char* message_piece, unsigned char* processed_piece, key_set* key_sets, int mode);

#endif
