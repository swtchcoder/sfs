#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>

#if defined(_WIN32)
#include <direct.h>
#endif

#include <limits.h>

#include "file.h"

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

static int path_sep(int c)
{
    return c == '/' || c == '\\';
}

int file_is_dir(const char *path)
{
    struct stat st;

    if (!path || !path[0]) {
        return 0;
    }
    if (stat(path, &st) != 0) {
        return 0;
    }
    return S_ISDIR(st.st_mode) ? 1 : 0;
}

static int mkdir_one(const char *path)
{
#if defined(_WIN32)
    if (_mkdir(path) == 0) {
        return 0;
    }
#else
    if (mkdir(path, 0755) == 0) {
        return 0;
    }
#endif
    if (errno == EEXIST) {
        return file_is_dir(path) ? 0 : -1;
    }
    return -1;
}

int file_ensure_dir(const char *path)
{
    char buf[PATH_MAX];
    size_t n;
    size_t i;

    if (!path || !path[0]) {
        errno = EINVAL;
        return -1;
    }
    n = strlen(path);
    if (n >= sizeof buf) {
        errno = ENAMETOOLONG;
        return -1;
    }
    (void)memcpy(buf, path, n + 1u);
    while (n > 1u && path_sep((unsigned char)buf[n - 1u])) {
        buf[--n] = '\0';
    }
    if (n == 0u) {
        errno = EINVAL;
        return -1;
    }

    i = 0;
#if defined(_WIN32)
    if (n >= 2u && ((buf[0] >= 'A' && buf[0] <= 'Z') || (buf[0] >= 'a' && buf[0] <= 'z')) && buf[1] == ':') {
        i = 2u;
        if (i < n && path_sep((unsigned char)buf[i])) {
            i++;
        }
    }
#endif
    if (path_sep((unsigned char)buf[0]) && buf[1] == '\0') {
        return 0;
    }

    for (; i < n; i++) {
        if (path_sep((unsigned char)buf[i])) {
            char sep = buf[i];

            buf[i] = '\0';
            if (i > 0u && buf[i - 1u] != '\0' && buf[i - 1u] != ':') {
                if (mkdir_one(buf) != 0) {
                    return -1;
                }
            }
            buf[i] = sep;
        }
    }
    return mkdir_one(buf);
}

int file_ensure_parent_dir(const char *filepath)
{
    char buf[PATH_MAX];

    size_t n;
    size_t k;

    int found = 0;

    if (!filepath || !filepath[0]) {
        errno = EINVAL;
        return -1;
    }
    n = strlen(filepath);
    if (n >= sizeof buf) {
        errno = ENAMETOOLONG;
        return -1;
    }
    (void)memcpy(buf, filepath, n + 1u);
    while (n > 1u && path_sep((unsigned char)buf[n - 1u])) {
        buf[--n] = '\0';
    }
    for (k = n; k > 0u;) {
        --k;
        if (path_sep((unsigned char)buf[k])) {
            buf[k] = '\0';
            found = 1;
            break;
        }
    }
    if (!found) {
        return file_ensure_dir(".");
    }
    if (buf[0] == '\0') {
        if (path_sep((unsigned char)filepath[0])) {
            return file_ensure_dir("/");
        }
        return file_ensure_dir(".");
    }
#if defined(_WIN32)
    if (buf[1] == ':' && buf[2] == '\0'
        && ((buf[0] >= 'A' && buf[0] <= 'Z') || (buf[0] >= 'a' && buf[0] <= 'z'))) {
        return 0;
    }
#endif
    return file_ensure_dir(buf);
}

int file_exists(const char *path)
{
    if (!path) {
        return 0;
    }

    struct stat st;

    return stat(path, &st) == 0;
}

time_t get_file_timestamp(const char *path)
{
    
    if (!path) {
        return (time_t)0;
    }
    struct stat st;
    if (stat(path, &st) != 0) {
        return (time_t)0;
    }
    
    return st.st_mtime;
}

size_t get_file_size(FILE *fptr)
{
    
    if (fseek(fptr, 0, SEEK_END) != 0) {
        return 0;
    }

    long size;

    size = ftell(fptr);
    if (size < 0) {
        return 0;
    }
    rewind(fptr);
    return (size_t)size;
}

unsigned char *read_file(FILE *fptr, size_t *out_size)
{
    
    if (!fptr) {
        return NULL;
    }
    if (fseek(fptr, 0, SEEK_END) != 0) {
        return NULL;
    }

    unsigned long long file_size;
    file_size = (unsigned long long)ftell(fptr);
    if (file_size <= 0) {
        return NULL;
    }
    rewind(fptr);

    unsigned char *buffer;
    buffer = malloc((size_t)file_size);
    if (!buffer) {
        return NULL;
    }
    size_t read_size;
    read_size = fread(buffer, 1, (size_t)file_size, fptr);
    if (read_size != (size_t)file_size) {
        free(buffer);
        return NULL;
    }
    if (out_size) {
        *out_size = (size_t)file_size;
    }
    return buffer;
}

unsigned char *read_file_from_path(const char *path, size_t *out_size)
{
    
    if (!path) {
        return NULL;
    }
    FILE *fptr;
    fptr = fopen(path, "rb");
    if (!fptr) {
        return NULL;
    }
    unsigned char *buffer;
    buffer = read_file(fptr, out_size);
    fclose(fptr);
    return buffer;
}

int write_file(FILE *fptr, const unsigned char *data, size_t size)
{
    if (!fptr || !data || size == 0) {
        return 0;
    }

    size_t written = fwrite(data, 1, size, fptr);
    if (written != size) {
        return 0;
    }

    if (fflush(fptr) != 0) {
        return 0;
    }

    return 1;
}

int write_file_from_path(const char *path, const unsigned char *data, size_t size)
{
    if (!path || !data || size == 0) {
        return 0;
    }

    FILE *fptr = fopen(path, "wb");
    if (!fptr) {
        return 0;
    }

    int ok = write_file(fptr, data, size);
    fclose(fptr);

    return ok;
}

const char *file_get_extension(const char *path)
{
    if (!path || !*path)
        return NULL;

    const char *base = path;
    const char *p = path;

    while (*p) {
        if (*p == '/' || *p == '\\') {
            base = p + 1;
        }
        p++;
    }

    if (*base == '\0')
        return NULL;

    const char *dot = NULL;
    for (p = base; *p; p++) {
        if (*p == '.') {
            dot = p;
        }
    }

    if (!dot || dot == base)
        return NULL;

    if (dot[1] == '\0')
        return NULL;

    return dot + 1;
}

const char *file_get_extension_full(const char *path)
{
    if (!path || !*path)
        return NULL;

    const char *base = path;
    const char *p = path;

    while (*p) {
        if (*p == '/' || *p == '\\') {
            base = p + 1;
        }
        p++;
    }

    if (*base == '\0' || *base == '.')
        return NULL;

    for (p = base; *p; p++) {
        if (*p == '.') {
            if (p[1] != '\0')
                return p + 1;
            return NULL;
        }
    }

    return NULL;
}

const char *file_get_filename(const char *path)
{
    if (!path || !*path)
        return NULL;

    const char *end = path;

    while (*end)
        end++;

    while (end > path && (end[-1] == '/' || end[-1] == '\\'))
        end--;

    if (end == path)
        return NULL;

    const char *p = end;
    while (p > path) {
        if (p[-1] == '/' || p[-1] == '\\')
            break;
        p--;
    }

    return p;
}


size_t get_file_size_from_path(const char *path)
{
    if (!path) {
        return 0;
    }

    FILE *fptr = fopen(path, "rb");
    if (!fptr) {
        return 0;
    }

    size_t size = get_file_size(fptr);
    fclose(fptr);

    return size;
}