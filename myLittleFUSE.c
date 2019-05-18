#define FUSE_USE_VERSION 29
#define _FILE_OFFSET_BITS 64

#include <fuse.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define RED "\e[31m"
#define FIX "\e[0m"

int myLittleFuse_getattr(const char *name, struct stat *result)
{
    printf(RED "Get attribute for %s" FIX "\n", name);

    memset(result, 0, sizeof(struct stat));

    if (strcmp(name, "/") == 0)
    {
        result->st_mode = S_IFDIR;
    }
    else
    {
        result->st_mode = S_IFREG;
    }
    return 0;
}

int myLittleFuse_readdir(const char *name, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    printf(RED "Reading directory %s" FIX "\n", name);

    // Emulate browsing the root directory of the filesystem
    if (!strcmp(name, "/"))
    {
        filler(buffer, "file_in_root", NULL, 0);
    }

    {
        // Emulate files (files 00-99)
        char str[3] = {'\0'};
        str[2] = '\0';

        for (int i = 0; i < 100; i++)
        {
            str[0] = i / 10 + '0';
            str[1] = i % 10 + '0';
            filler(buffer, strdup(str), NULL, 0);
        }
    }

    return 0;
}

int myLittleFuse_unlink(const char *);
int myLittleFuse_rename(const char *, const char *);
int myLittleFuse_truncate(const char *, off_t);
int myLittleFuse_open(const char *, struct fuse_file_info *);
int myLittleFuse_read(const char *, char *, size_t, off_t, struct fuse_file_info *);
int myLittleFuse_write(const char *, const char *, size_t, off_t, struct fuse_file_info *);
int myLittleFuse_release(const char *, struct fuse_file_info *);
void *myLittleFuse_init(struct fuse_conn_info *);
void myLittleFuse_destroy(void *);
int myLittleFuse_create(const char *, mode_t, struct fuse_file_info *);

int myLittleFuse_unlink(const char *path)
{
    printf(RED "Unlinking file %s" FIX "\n", path);
    return 0;
}

int myLittleFuse_rename(const char *oldPath, const char *newPath)
{
    printf(RED "Rename from %s to %s" FIX "\n", oldPath, newPath);
    return 0;
}

int myLittleFuse_truncate(const char *path, off_t size)
{
    printf(RED "Truncate %s to %d bytes long" FIX "\n", path, size);
    return 0;
}

int myLittleFuse_open(const char *file, struct fuse_file_info *fh)
{
    printf(RED "Open file: %s" FIX "\n", file);
    return 0;
}

int myLittleFuse_read(const char *a, char *b, size_t c, off_t d, struct fuse_file_info *fh)
{
    printf(RED "Reading %s...%s %d %d" FIX "\n", a, b, c, d);
    return 0;
}

int myLittleFuse_write(const char *a, const char *b, size_t c, off_t d, struct fuse_file_info *fh)
{
    printf(RED "Writing to `%s` the contents '%s' size %d ... %d" FIX "\n", a, b, c, d);
    return 0;
}

int myLittleFuse_release(const char *path, struct fuse_file_info *fh)
{
    printf(RED "Releasing %s" FIX "\n", path);
    return 0;
}

void *myLittleFuse_init(struct fuse_conn_info *fi)
{
    puts(RED "Init" FIX "\n");
}

void myLittleFuse_destroy(void *uhh)
{
    puts(RED "Destroy" FIX "\n");
}

int myLittleFuse_create(const char *path, mode_t a, struct fuse_file_info *fh)
{
    printf(RED "Create file %s, mode %x" FIX "\n", path, a);
    return 0;
}

struct fuse_operations operationMap = {
    .read = myLittleFuse_read,
    .open = myLittleFuse_open,
    .write = myLittleFuse_write,
    .rename = myLittleFuse_rename,
    .unlink = myLittleFuse_unlink,
    .readdir = myLittleFuse_readdir,
    .getattr = myLittleFuse_getattr,
    .truncate = myLittleFuse_truncate,
    .init = myLittleFuse_init,
    .create = myLittleFuse_create,
    .destroy = myLittleFuse_destroy,
    .release = myLittleFuse_release,
};

int main(int argc, char *argv[])
{
    puts("Start!\n\n");

    return fuse_main(argc, argv, &operationMap, NULL);
}