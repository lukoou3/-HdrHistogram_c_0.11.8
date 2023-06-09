#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include <time.h>

#include <stdio.h>
#include <hdr/hdr_histogram.h>
#include <hdr/hdr_histogram_log.h>

static struct hdr_histogram* histogram = NULL;

static void load_histograms(void)
{
    int i;

    free(histogram);

    hdr_alloc(INT64_C(3600) * 1000 * 1000, 3, &histogram);

    for (i = 0; i < 1000000; i++)
    {
        int ret = rand() % 10000 + 1;
        hdr_record_value(histogram, ret);
    }

    hdr_record_value(histogram, 100000000);
}

 int main()
 {
    load_histograms();
    printf("hello, word\n");
    char *data;
    hdr_log_encode(histogram, &data);
    printf("%s\n", data);
    printf("hello, word\n");
    return 0;
}

 int main2()
 {
    load_histograms();
    printf("hello, word\n");
    FILE * fileToWrite = NULL;
    uint8_t* compressed_histogram = NULL;
    size_t compressed_len = 0;
    int rc = 0;
    size_t encoded_len;
    rc = hdr_encode_compressed(histogram, &compressed_histogram, &compressed_len);
    printf("rst_code:%d,len:%d\n", rc, compressed_len );
    if((fileToWrite = fopen("D:\\files\\hdr-c-compress-buildin.bin", "wb+")) != NULL){
    fwrite(compressed_histogram, 1, compressed_len, fileToWrite);
    fclose(fileToWrite);
    }

}