#include <stdio.h>
#include <sodium.h>

#define NUM_ITERATIONS 1000

int main() {
    if (sodium_init() < 0) {
        printf("Failed to initialize libsodium\n");
        return 1;
    }

    // Key pairs for Alice and Bob
    unsigned char alice_pk[crypto_box_PUBLICKEYBYTES];
    unsigned char alice_sk[crypto_box_SECRETKEYBYTES];
    unsigned char bob_pk[crypto_box_PUBLICKEYBYTES];
    unsigned char bob_sk[crypto_box_SECRETKEYBYTES];

    crypto_box_keypair(alice_pk, alice_sk);
    crypto_box_keypair(bob_pk, bob_sk);

    // Small message and nonce
    unsigned char message[32] = {0};
    unsigned char ciphertext[sizeof message + crypto_box_MACBYTES];
    unsigned char nonce[crypto_box_NONCEBYTES] = {0};
    unsigned char decrypted[sizeof message];

    printf("Starting CPU-intensive encryption loop...\n");

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Encrypt the message
        crypto_box_easy(ciphertext, message, sizeof message, nonce, bob_pk, alice_sk);

        // Decrypt the message
        if (crypto_box_open_easy(decrypted, ciphertext, sizeof ciphertext, nonce, alice_pk, bob_sk) != 0) {
            printf("Decryption failed at iteration %d!\n", i);
            return 1;
        }

        // Simple modification to keep CPU busy
        message[0] ^= i & 0xFF;
        nonce[0] ^= i & 0xFF;
    }

    printf("Completed %d iterations of public-key encryption/decryption.\n", NUM_ITERATIONS);
    return 0;
}
