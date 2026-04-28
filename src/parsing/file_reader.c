#include "cub3d.h"


/*
The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.*/


int read_map_file(const char *filename, char ***lines, int *count)
{
    //open the map file;
    int fd = open(filename, O_RDONLY);
    char *line;
    int line_count;

    //read everyline with GNL
    while((line = get_next_line(fd)))
    {
        //store lines in a dyamic array

        line_count++;

    }

    //return succed/failure + line count
}

/*
Function contract (important first)

Input: filename
Output: lines array + count (through pointers)
Return: 1 on success, 0 on error
On error: free everything already allocated, set outputs to safe values
Recommended build order

Step 1: open file and loop get_next_line
Step 2: count lines only (temporary)
Step 3: add dynamic storage (grow array as lines come)
Step 4: finalize with NULL-terminated array (optional but useful)
Step 5: clean error paths (malloc fail, open fail, read fail)
Memory strategy

Start with capacity (example 8 or 16).
When full, allocate a bigger array (usually x2), copy pointers, free old array.
Store each returned line pointer directly (do not duplicate unless needed).
At end, close fd in all cases.
Common mistakes to avoid

Forgetting to close fd when returning early.
Losing pointers during resize (causes leaks).
Not freeing partially built array on failure.
Returning success with uninitialized output pointers.
Quick self-check

Nonexistent file → clean failure
Empty file → success with count 0 (or your project rule)
1-line file → correct count and content
Multi-line file → exact order preserved
Run with valgrind/leaks to confirm no leaks
*/