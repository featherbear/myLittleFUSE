cd "$(dirname "$0")"
gcc -Wall -o myLittleFUSE myLittleFuse.c `pkg-config fuse --cflags --libs`
