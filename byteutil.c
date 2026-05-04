#include "byteutil.h"

#include <limits.h>
#include <stdint.h>

/* ===================== BIG ENDIAN ===================== */
/* ===================== 16 bits ===================== */

uint16_t read_u16_be(const unsigned char *p)
{
    return ((uint16_t)p[0] << 8) |
           (uint16_t)p[1];
}

void write_u16_be(unsigned char *p, uint16_t v)
{
    p[0] = (unsigned char)((v >> 8) & 255u);
    p[1] = (unsigned char)(v & 255u);
}

/* ===================== 32 bits ===================== */

uint32_t read_u32_be(const unsigned char *p)
{
    return ((uint32_t)p[0] << 24) |
           ((uint32_t)p[1] << 16) |
           ((uint32_t)p[2] << 8)  |
           (uint32_t)p[3];
}

void write_u32_be(unsigned char *p, uint32_t v)
{
    p[0] = (unsigned char)((v >> 24) & 255u);
    p[1] = (unsigned char)((v >> 16) & 255u);
    p[2] = (unsigned char)((v >> 8) & 255u);
    p[3] = (unsigned char)(v & 255u);
}

/* ===================== 64 bits ===================== */

uint64_t read_u64_be(const unsigned char *p)
{
    return ((uint64_t)p[0] << 56) |
           ((uint64_t)p[1] << 48) |
           ((uint64_t)p[2] << 40) |
           ((uint64_t)p[3] << 32) |
           ((uint64_t)p[4] << 24) |
           ((uint64_t)p[5] << 16) |
           ((uint64_t)p[6] << 8)  |
           (uint64_t)p[7];
}

void write_u64_be(unsigned char *p, uint64_t v)
{
    p[0] = (unsigned char)((v >> 56) & 255u);
    p[1] = (unsigned char)((v >> 48) & 255u);
    p[2] = (unsigned char)((v >> 40) & 255u);
    p[3] = (unsigned char)((v >> 32) & 255u);
    p[4] = (unsigned char)((v >> 24) & 255u);
    p[5] = (unsigned char)((v >> 16) & 255u);
    p[6] = (unsigned char)((v >> 8) & 255u);
    p[7] = (unsigned char)(v & 255u);
}


/* ===================== LITTLE ENDIAN ===================== */
/* ===================== 16 bits ===================== */

uint16_t read_u16_le(const unsigned char *p)
{
    return (uint16_t)p[0] |
           ((uint16_t)p[1] << 8);
}

void write_u16_le(unsigned char *p, uint16_t v)
{
    p[0] = (unsigned char)(v & 255u);
    p[1] = (unsigned char)((v >> 8) & 255u);
}

/* ===================== 32 bits ===================== */

uint32_t read_u32_le(const unsigned char *p)
{
    return (uint32_t)p[0] |
           ((uint32_t)p[1] << 8)  |
           ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

void write_u32_le(unsigned char *p, uint32_t v)
{
    p[0] = (unsigned char)(v & 255u);
    p[1] = (unsigned char)((v >> 8) & 255u);
    p[2] = (unsigned char)((v >> 16) & 255u);
    p[3] = (unsigned char)((v >> 24) & 255u);
}

/* ===================== 64 bits ===================== */

uint64_t read_u64_le(const unsigned char *p)
{
    return (uint64_t)p[0]        |
           ((uint64_t)p[1] << 8) |
           ((uint64_t)p[2] << 16)|
           ((uint64_t)p[3] << 24)|
           ((uint64_t)p[4] << 32)|
           ((uint64_t)p[5] << 40)|
           ((uint64_t)p[6] << 48)|
           ((uint64_t)p[7] << 56);
}

void write_u64_le(unsigned char *p, uint64_t v)
{
    p[0] = (unsigned char)(v & 255u);
    p[1] = (unsigned char)((v >> 8) & 255u);
    p[2] = (unsigned char)((v >> 16) & 255u);
    p[3] = (unsigned char)((v >> 24) & 255u);
    p[4] = (unsigned char)((v >> 32) & 255u);
    p[5] = (unsigned char)((v >> 40) & 255u);
    p[6] = (unsigned char)((v >> 48) & 255u);
    p[7] = (unsigned char)((v >> 56) & 255u);
}


int size_mul_overflow(size_t a, size_t b, size_t *out) { 
    if (a != 0u && b > SIZE_MAX / a) { 
        return 1; 
    } 
    *out = a * b; 
    return 0; 
} 
int size_add_overflow(size_t a, size_t b, size_t *out) {
    if (b > SIZE_MAX - a) { 
        return 1; 
    } 
    *out = a + b; 
    return 0; 
}

int size_mul_u32_u32_size(uint32_t w, uint32_t h, size_t k, size_t *out) { 
    size_t wh; 
    if (size_mul_overflow((size_t)w, (size_t)h, &wh)) { 
        return 1; 
    } 
    return size_mul_overflow(wh, k, out); 
}