#ifndef FILE_H
#define FILE_H

#include <time.h>

int file_exists(const char *path);
time_t get_file_timestamp(const char *path);
size_t get_file_size(FILE *fptr);
size_t get_file_size_from_path(const char *path);
unsigned char *read_file(FILE *fptr, size_t *size);
unsigned char *read_file_from_path(const char *path, size_t *out_size);
int write_file(FILE *fptr, const unsigned char *data, size_t size);
int write_file_from_path(const char *path, const unsigned char *data, size_t size);
int file_is_dir(const char *path);
int file_ensure_dir(const char *path);
int file_ensure_parent_dir(const char *filepath);
const char *file_get_extension(const char *path);
const char *file_get_extension_full(const char *path);
const char *file_get_filename(const char *path);

#endif
