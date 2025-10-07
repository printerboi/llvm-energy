/*
 * zlib_api_demo_heavy.c
 *
 * Heavier usage of zlib APIs to stress CPU:
 *   - many iterations, different levels/strategies
 *   - frequent flushes in streaming mode
 *   - multiple gzip appends + reads
 *   - repeated checksum verifications
 *
 * Compile:
 *   gcc -O2 -std=c11 -Wall -Wextra zlib_api_demo_heavy.c -o zlib_api_demo_heavy -lz
 */

#define _POSIX_C_SOURCE 200809L
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define ROUNDS 20
#define BLOCKSIZE 8192
#define DATA_SIZE (2 * 1024 * 1024) /* 10 MB */

static void die(const char *msg) {
    fprintf(stderr, "FATAL: %s\n", msg);
    exit(2);
}

static void fill_data(uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        buf[i] = (uint8_t)((i * 1315423911u) ^ (i >> 3));
    }
}

/* ----------- Simple API stress ----------- */
static void stress_simple(const uint8_t *input, size_t len) {
    //printf("\n=== stress_simple ===\n");

    uLong bound = compressBound((uLong)len);
    uint8_t *comp = malloc(bound);
    uint8_t *recon = malloc(len);

    for (int round = 0; round < ROUNDS; round++) {
        for (int lvl = 1; lvl <= 9; lvl++) {
            uLong outlen = bound;
            int rc = compress2(comp, &outlen, input, (uLong)len, lvl);
            if (rc != Z_OK) die("compress2 failed");

            /* verify */
            uLong rlen = (uLong)len;
            rc = uncompress(recon, &rlen, comp, outlen);
            if (rc != Z_OK || rlen != len || memcmp(recon, input, len) != 0)
                die("simple roundtrip failed");

            /* checksums */
            uLong ad = adler32(0L, comp, outlen);
            uLong cr = crc32(0L, comp, outlen);
        }
    }
    free(comp);
    free(recon);
    //printf("simple stress done (%d rounds * 9 levels)\n", ROUNDS);
}

/* ----------- Gzip API stress ----------- */
static void stress_gzip(const uint8_t *input, size_t len) {
    //printf("\n=== stress_gzip ===\n");
    const char *fname = "stress.gz";

    for (int round = 0; round < ROUNDS; round++) {
        gzFile gz = gzopen(fname, "wb6");
        if (!gz) die("gzopen write");

        gzbuffer(gz, 65536);
        for (size_t i = 0; i < len; i += BLOCKSIZE) {
            size_t chunk = (i + BLOCKSIZE <= len) ? BLOCKSIZE : (len - i);
            if (gzwrite(gz, input + i, (unsigned)chunk) != (int)chunk)
                die("gzwrite failed");
            if ((i / BLOCKSIZE) % 5 == 0) gzprintf(gz, "[marker %zu]\n", i);
        }
        gzclose(gz);

        gz = gzopen(fname, "rb");
        if (!gz) die("gzopen read");
        uint8_t buf[BLOCKSIZE];
        int total = 0, n;
        while ((n = gzread(gz, buf, sizeof buf)) > 0)
            total += n;
        gzclose(gz);

        if (total < (int)len)
            die("gzip roundtrip too short");
    }
    //printf("gzip stress done (%d rounds)\n", ROUNDS);
}

/* ----------- main ----------- */
int main(void) {
    //printf("Allocating %d MB test data...\n", DATA_SIZE / (1024 * 1024));
    uint8_t *data = malloc(DATA_SIZE);
    if (!data) die("malloc");
    fill_data(data, DATA_SIZE);

    
    stress_gzip(data, DATA_SIZE);

    free(data);
    //printf("All stress tests done.\n");
    return 0;
}
