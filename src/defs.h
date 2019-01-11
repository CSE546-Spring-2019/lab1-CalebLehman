#ifndef DEFS_H
#define DEFS_H

//#define MAX_CHUNK 100
extern const size_t MAX_CHUNK;

typedef struct FileStats {
    size_t length;
    size_t matches;
} FileStats;

// static int byteCompare(char b1, char b2) { return (b1 & 0xff) == (b2 & 0xff); }

#endif // DEFS_H
