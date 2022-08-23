#include <utils_dns.h>

int utils_dns_domain_get(uint8_t *records, uint8_t *buf, int *len)
{
    int i, pos_in, pos_out, size_buf;

    size_buf = *len;

    pos_in = 0;
    pos_out = 0;
    i = records[pos_in++];
    while (i > 0 && size_buf > 0) {
        buf[pos_out++] = records[pos_in++];
        i--;
        size_buf--;

        if (0 == i && size_buf > 0) {
            /*current record is empty*/
            buf[pos_out++] = '.';
            i = records[pos_in++];
        }
    }
    *len = pos_out;

    return 0;
}
