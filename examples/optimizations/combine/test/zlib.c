#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <zlib.h>

#define CHUNK 16384  // 16 KB

int main(void) {
    // Langer Input (ca. 10 MB)
    const char *pattern =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
        "Praesent libero. Sed cursus ante dapibus diam. Duis sagittis ipsum.\n";

    size_t repeats = (10 * 1024 * 1024) / strlen(pattern);
    size_t input_size = repeats * strlen(pattern);

    char *input = (char *)malloc(input_size);
    assert(input);
    for (size_t i = 0; i < repeats; i++) {
        memcpy(input + i * strlen(pattern), pattern, strlen(pattern));
    }

    printf("Originalgröße: %zu Bytes (~%.2f MB)\n",
           input_size, input_size / (1024.0 * 1024.0));

    // --- Komprimieren ---
    z_stream strm;
    memset(&strm, 0, sizeof(strm));
    assert(deflateInit(&strm, Z_BEST_COMPRESSION) == Z_OK);

    unsigned char *comp = malloc(input_size); // worst case
    assert(comp);

    strm.next_in = (Bytef *)input;
    strm.avail_in = input_size;
    strm.next_out = comp;
    strm.avail_out = input_size;

    int ret;
    do {
        ret = deflate(&strm, strm.avail_in ? Z_NO_FLUSH : Z_FINISH);
        assert(ret != Z_STREAM_ERROR);
    } while (ret != Z_STREAM_END);

    size_t comp_size = strm.total_out;
    deflateEnd(&strm);

    printf("Komprimiert auf: %zu Bytes (~%.2f MB)\n",
           comp_size, comp_size / (1024.0 * 1024.0));

    // --- Dekomprimieren ---
    z_stream dstrm;
    memset(&dstrm, 0, sizeof(dstrm));
    assert(inflateInit(&dstrm) == Z_OK);

    unsigned char *decomp = malloc(input_size);
    assert(decomp);

    dstrm.next_in = comp;
    dstrm.avail_in = comp_size;
    dstrm.next_out = decomp;
    dstrm.avail_out = input_size;

    do {
        ret = inflate(&dstrm, Z_NO_FLUSH);
        assert(ret != Z_STREAM_ERROR);
    } while (ret != Z_STREAM_END);

    size_t decomp_size = dstrm.total_out;
    inflateEnd(&dstrm);

    printf("Dekomprimiert: %zu Bytes (~%.2f MB)\n",
           decomp_size, decomp_size / (1024.0 * 1024.0));

    // Validierung
    if (memcmp(input, decomp, input_size) == 0) {
        printf("✔️ Text nach Dekompression identisch.\n");
    } else {
        printf("❌ Unterschied nach Dekompression!\n");
    }

    free(input);
    free(comp);
    free(decomp);

    return 0;
}
