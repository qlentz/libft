# libft

Build with `make`; `make re` also supports parallel execution. Header changes
rebuild dependent objects. `make clean` removes objects and dependency files;
`make fclean` also removes the archive.

Run the checks with:

```sh
norminette
python3 tests/check.py
python3 tests/check.py --sanitize
python3 tests/check.py --valgrind
python3 tests/check.py --sanitize --buffer-size 1
python3 tests/check.py --sanitize --buffer-size 4096
```

The regressions cover the reviewed memory bugs, allocation failures, bounded
string reads, overlapping memory moves, integer limits, decimal parsing, list-map
cleanup, failed reads, interleaved line readers, and formatted-output errors.
The tests generate their C harness in a temporary directory.
Sanitizer runs require the compiler's AddressSanitizer/UndefinedBehaviorSanitizer
runtimes; Valgrind runs require Valgrind.

`ft_atoi` accepts leading whitespace and one sign, stops at the first nondigit,
and clamps values outside the `int` range to `INT_MIN` or `INT_MAX`.
`ft_atod` accepts simple signed decimal input, including a fractional part;
exponent notation and locale-specific formatting are outside its interface.

`ft_printf` implements `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, and `%%`.
It returns `-1` for output failures or unsupported/incomplete conversions.
Null strings print `(null)` and null pointers print `(nil)` on Linux.

`get_next_line` supports descriptors from zero through `GNL_MAX_FD - 1` and a
positive `BUFFER_SIZE` (default 100, overridable at compilation). It returns a
heap-allocated line including its newline, or `NULL` at EOF or on error.
Allocation/read failures discard that descriptor's buffered data. Read each
stream through EOF to release buffered data before closing or reusing its fd.
`ft_strjoin_gnl` consumes its first allocation on both success and failure; its
second argument is borrowed.
