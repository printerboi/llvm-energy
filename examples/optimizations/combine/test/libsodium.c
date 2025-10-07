#include <sodium.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    if (sodium_init() < 0) {
        printf("sodium_init() failed\n");
        return 1;
    }

    /* --- allocate deterministic 20 MB buffer --- */
    size_t len = 1 * 1024 * 1024;  // 20 MB
    unsigned char *buf = sodium_malloc(len);
    for (size_t i = 0; i < len; i++) {
        buf[i] = (unsigned char)(i & 0xFF);
    }
    printf("buffer allocated: %zu bytes\n", len);

    /* --- crypto_generichash (BLAKE2b) --- */
    unsigned char h1[crypto_generichash_BYTES];
    crypto_generichash(h1, sizeof h1, buf, len, NULL, 0);
    printf("generichash first 8 bytes: ");
    for (int i = 0; i < 8; i++) printf("%02x", h1[i]);
    printf("\n");

    /* --- crypto_hash_sha256 --- */
    unsigned char h2[crypto_hash_sha256_BYTES];
    crypto_hash_sha256(h2, buf, len);
    printf("sha256 first 8 bytes: ");
    for (int i = 0; i < 8; i++) printf("%02x", h2[i]);
    printf("\n");

    /* --- crypto_secretbox_easy --- */
    unsigned char key[crypto_secretbox_KEYBYTES];
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    memset(key, 0x42, sizeof key);   // deterministic key
    memset(nonce, 0x24, sizeof nonce);

    size_t clen = len + crypto_secretbox_MACBYTES;
    unsigned char *cipher = sodium_malloc(clen);
    unsigned char *plain  = sodium_malloc(len);

    crypto_secretbox_easy(cipher, buf, len, nonce, key);
    if (crypto_secretbox_open_easy(plain, cipher, clen, nonce, key) != 0) {
        printf("secretbox decryption failed!\n");
    } else {
        printf("secretbox round-trip ok (first byte %02x)\n", plain[0]);
    }

    /* --- crypto_aead_chacha20poly1305_ietf --- */
    unsigned char ad[] = "assoc-data";
    unsigned char *c2 = sodium_malloc(len + crypto_aead_chacha20poly1305_ietf_ABYTES);
    unsigned long long c2_len;

    crypto_aead_chacha20poly1305_ietf_encrypt(
        c2, &c2_len,
        buf, len,
        ad, sizeof ad,
        NULL, nonce, key
    );

    unsigned char *p2 = sodium_malloc(len);
    unsigned long long p2_len;
    if (crypto_aead_chacha20poly1305_ietf_decrypt(
            p2, &p2_len,
            NULL,
            c2, c2_len,
            ad, sizeof ad,
            nonce, key) == 0) {
        printf("aead chacha20poly1305 ok (len %llu)\n", p2_len);
    }

    /* --- crypto_scalarmult (Curve25519) --- */
    unsigned char sk1[crypto_scalarmult_SCALARBYTES];
    unsigned char sk2[crypto_scalarmult_SCALARBYTES];
    unsigned char pk1[crypto_scalarmult_BYTES];
    unsigned char pk2[crypto_scalarmult_BYTES];
    unsigned char shared1[crypto_scalarmult_BYTES];
    unsigned char shared2[crypto_scalarmult_BYTES];

    memset(sk1, 1, sizeof sk1);
    memset(sk2, 2, sizeof sk2);

    crypto_scalarmult_base(pk1, sk1);
    crypto_scalarmult_base(pk2, sk2);

    crypto_scalarmult(shared1, sk1, pk2);
    crypto_scalarmult(shared2, sk2, pk1);

    printf("scalarmult shared keys match: %s\n",
        sodium_memcmp(shared1, shared2, sizeof shared1) == 0 ? "yes" : "no");

    /* --- crypto_kdf --- */
    unsigned char subkey[32];
    unsigned char master_key[crypto_kdf_KEYBYTES];
    memset(master_key, 0x11, sizeof master_key);

    crypto_kdf_derive_from_key(subkey, sizeof subkey, 1, "ctx1234", master_key);
    printf("kdf subkey first 8 bytes: ");
    for (int i = 0; i < 8; i++) printf("%02x", subkey[i]);
    printf("\n");

    /* --- crypto_sign (use a slice, not full 20MB) --- */
    unsigned char pk[crypto_sign_PUBLICKEYBYTES];
    unsigned char sk[crypto_sign_SECRETKEYBYTES];
    crypto_sign_keypair(pk, sk);

    unsigned char sig[crypto_sign_BYTES];
    if (crypto_sign_detached(sig, NULL, buf, 1024, sk) == 0) {
        printf("sign detached (first byte %02x)\n", sig[0]);
    }
    if (crypto_sign_verify_detached(sig, buf, 1024, pk) == 0) {
        printf("sign verify ok\n");
    }

    /* cleanup */
    sodium_free(buf);
    sodium_free(cipher);
    sodium_free(plain);
    sodium_free(c2);
    sodium_free(p2);

    return 0;
}
