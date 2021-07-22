#include <stdio.h>
#include <openssl/des.h>

int main(int argc,char **argv)
{
    DES_cblock key;
    //随机密钥
    DES_random_key(&key);

    DES_key_schedule schedule;
    //转换成schedule
    DES_set_key_checked(&key, &schedule);

    const_DES_cblock input = "hehehe";
    DES_cblock output;

    printf("cleartext: %s\n", input);

    //加密
    DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);
    printf("Encrypted!\n");

    printf("ciphertext: ");
    int i;
    for (i = 0; i < sizeof(input); i++)
         printf("%02x", output[i]);
    printf("\n");

    //解密
    DES_ecb_encrypt(&output, &input, &schedule, DES_DECRYPT);
    printf("Decrypted!\n");
    printf("cleartext:%s\n", input);

    return 0;
}
