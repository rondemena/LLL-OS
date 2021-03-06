#ifndef _NEXUS_FILE_H_
#define _NEXUS_FILE_H_

#include <limits.h>

#include <nexus/fs.h>
#include <nexus/vector.h>

// an element of a Path
typedef struct PathComponent {
  FSID node;
  char fname[0];
} PathComponent;

// a sequence of 1 or more PathComponent elements
typedef struct Path {
  PointerVector vec;
} Path;

// init an empty path to be root of a filesystem
void Path_new(Path *path, FSID fs_root);

// init an empty path to be a copy of existing path
void Path_dup(Path *dest, Path *path);

// make a path longer
void Path_append(Path *path, FSID node, char *fname);

// get last element of a path
PathComponent *Path_last(Path *path);

// get next to last element of a path, if it exists
PathComponent *Path_lastparent(Path *path);

// get first element of a path
PathComponent *Path_root(Path *path);

// make a path shorter; returns non-zero if path had only one element
int Path_pop(Path *path); 

// get length of path
int Path_len(Path *path);

// get n-th element of a path (0 < n < len)
PathComponent *Path_nth(Path *path, int i);

// reset a path back to an uninitialized state
void Path_clear(Path *path);

int Path_resolve(Path *path, FSID fs_root, Path *cwd, const char *unix_path);

/// same as Path_resolve, but allow the last path element to contain FSID_INVALID
int Path_resolve1(Path *path, FSID fs_root, Path *cwd, const char *unix_path);

/// return the path as a readable string.
char * Path_string(Path *path, int max);

#endif // _NEXUS_FILE_H_

