#ifndef BYTEUTIL_H
#define BYTEUTIL_H

#include <stddef.h>
#include <stdint.h>


uint32_t read_u32_be(const unsigned char *p);

void write_u32_be(unsigned char *p, uint32_t v);
    
uint16_t read_u16_le(const unsigned char *p);

void write_u16_le(unsigned char *p, uint16_t v);

uint32_t read_u32_le(const unsigned char *p);

void write_u32_le(unsigned char *p, uint32_t v);

uint64_t read_u64_le(const unsigned char *p);

void write_u64_le(unsigned char *p, uint64_t v);

int size_mul_overflow(size_t a, size_t b, size_t *out);

int size_add_overflow(size_t a, size_t b, size_t *out);

int size_mul_u32_u32_size(uint32_t w, uint32_t h, size_t k, size_t *out);



#endif
