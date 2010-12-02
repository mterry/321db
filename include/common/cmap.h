// cmap.h
// Map structure and functions for manipulating maps in C
// Matthew A. Terry
// ============================================================================

#include <string.h>
#include <stdlib.h>

// maps are sorted data structures with a key and a value tied to the key.
// The "value" can be of any type, including structures or unions. They are a
// strictly sorted data structure, sorted along the keys, and no duplicate keys
// can occur; however, duplicate values can occur.

// Implementation notes:
// The current implementation is non-generic regarding keys: it instead
// strictly uses unsigned integers as the key.

// cmap structure definition:
// cmap.key.u_key: the key value for the map (unsigned integer); this key is
//                 used to access the associated value
struct cmap
{
  union key_types
  {
    unsigned int u_key;
  }
  key;

  
  
};

// type definition for the cmap structure
typedef struct cmap cmap_t;
