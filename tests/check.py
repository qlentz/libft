#!/usr/bin/env python3
"""Compile and run libft regressions without third-party test dependencies."""

import argparse
import os
from pathlib import Path
import subprocess
import tempfile


HARNESS = r"""
#include "libft.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>

static long live, malloc_count, malloc_failure;
static long read_count, read_failure, write_count, write_failure;
static unsigned checks;

void *__real_malloc(size_t);
void __real_free(void *);
ssize_t __real_read(int, void *, size_t);
ssize_t __real_write(int, const void *, size_t);

void *__wrap_malloc(size_t size)
{
    void *pointer;
    malloc_count++;
    if (malloc_failure && malloc_count == malloc_failure)
        return NULL;
    pointer = __real_malloc(size);
    if (pointer)
        live++;
    return pointer;
}

void __wrap_free(void *pointer)
{
    if (pointer)
        live--;
    __real_free(pointer);
}

ssize_t __wrap_read(int fd, void *buffer, size_t size)
{
    if (size)
        read_count++;
    if (size && read_failure && read_count == read_failure)
    {
        errno = EIO;
        return -1;
    }
    return __real_read(fd, buffer, size);
}

ssize_t __wrap_write(int fd, const void *buffer, size_t size)
{
    write_count++;
    if (write_failure && write_count == write_failure)
    {
        errno = EIO;
        return -1;
    }
    return __real_write(fd, buffer, size);
}

static void check_string(char *actual, const char *expected)
{
    assert(actual && strcmp(actual, expected) == 0);
    free(actual);
    checks++;
}

static FILE *input_file(const char *data, size_t length)
{
    FILE *file = tmpfile();
    assert(file);
    assert(fwrite(data, 1, length, file) == length);
    assert(fflush(file) == 0);
    rewind(file);
    return file;
}

static void strings(void)
{
    char *empty = malloc(1), *trim = ft_strdup(" \t \t ");
    char *a = malloc(2), *b = malloc(2);
    char dest[8] = "ab";
    assert(empty && trim && a && b);
    empty[0] = 0;
    check_string(ft_strtrim(empty, " "), "");
    check_string(ft_strtrim(trim, " \t"), "");
    check_string(ft_strtrim("xyhelloxy", "xy"), "hello");
    check_string(ft_strtrim("hello", ""), "hello");
    check_string(ft_substr("abc", 99, SIZE_MAX), "");
    check_string(ft_substr("abc", 1, SIZE_MAX), "bc");
    check_string(ft_substr("abc", 1, 0), "");
    assert(!ft_strjoin(NULL, "x") && !ft_strjoin("x", NULL));
    assert(!ft_substr(NULL, 0, 1) && !ft_split(NULL, ' '));
    a[0] = b[0] = 'a';
    a[1] = b[1] = 'b';
    assert(ft_strncmp(a, b, 2) == 0);
    assert(ft_strncmp(NULL, NULL, 0) == 0);
    assert(ft_strnstr(a, "abx", 2) == NULL);
    assert(ft_strnstr(a, "ab", 2) == a);
    assert(ft_strnstr(NULL, "x", 0) == NULL);
    assert(ft_strlcat(a, "x", 2) == 3);
    assert(a[0] == 'a' && a[1] == 'b');
    assert(ft_strlcat(NULL, "abc", 0) == 3);
    assert(ft_strlcat(dest, "cdefgh", sizeof(dest)) == 8);
    assert(strcmp(dest, "abcdefg") == 0);
    assert(!ft_calloc(SIZE_MAX / 2 + 1, 2));
    free(empty);
    free(trim);
    free(a);
    free(b);
    checks += 16;
}

static void memory_and_numbers(void)
{
    unsigned char source[64], actual[64], expected[64];
    int values[] = {INT_MIN, -100, -1, 0, 1, 100, INT_MAX};
    char expected_number[64];
    size_t i, source_offset, destination_offset, count;
    for (i = 0; i < sizeof(source); i++)
        source[i] = (unsigned char)(i * 37);
    for (source_offset = 0; source_offset < 16; source_offset++)
        for (destination_offset = 0; destination_offset < 16; destination_offset++)
            for (count = 0; count < 32; count++)
            {
                memcpy(actual, source, sizeof(source));
                memcpy(expected, source, sizeof(source));
                ft_memmove(actual + destination_offset, actual + source_offset, count);
                memmove(expected + destination_offset, expected + source_offset, count);
                assert(memcmp(actual, expected, sizeof(actual)) == 0);
                checks++;
            }
    for (count = 0; count <= sizeof(source); count++)
    {
        ft_memset(actual, 0xa5, sizeof(actual));
        memset(expected, 0xa5, sizeof(expected));
        assert(ft_memcpy(actual, source, count) == actual);
        memcpy(expected, source, count);
        assert(memcmp(actual, expected, sizeof(actual)) == 0);
        for (i = 0; i < 256; i++)
        {
            assert(ft_memchr(source, (int)i, count) == memchr(source, (int)i, count));
            checks++;
        }
    }
    assert(ft_memmove(NULL, NULL, 0) == NULL);
    assert(ft_memcpy(NULL, NULL, 0) == NULL);
    for (i = 0; i < sizeof(values) / sizeof(*values); i++)
    {
        snprintf(expected_number, sizeof(expected_number), "%d", values[i]);
        check_string(ft_itoa(values[i]), expected_number);
        assert(ft_atoi(expected_number) == values[i]);
    }
    assert(ft_atoi("999999999999999999999999999999") == INT_MAX);
    assert(ft_atoi("-999999999999999999999999999999") == INT_MIN);
    assert(ft_atoi(" \t+123tail") == 123 && ft_atoi("--1") == 0);
    assert(ft_atod("") == 0.0 && ft_atod("123") == 123.0);
    assert(ft_atod("+12.5") == 12.5 && ft_atod("-12.5") == -12.5);
    assert(fabs(ft_atod("  .001") - 0.001) < 1e-15);
    assert(ft_atod("no digits") == 0.0);
    checks += 12;
}

static void split_and_allocation_failures(void)
{
    long failure;
    char **parts;
    char *text;
    size_t i;
    const char *expected[] = {"a", "bb", "ccc", NULL};
    parts = ft_split("..a...bb.ccc..", '.');
    assert(parts);
    for (i = 0; expected[i]; i++)
        assert(parts[i] && strcmp(parts[i], expected[i]) == 0);
    assert(!parts[i]);
    ft_free_tab(parts);
    parts = ft_split("abc", '\0');
    assert(parts && parts[0] && !parts[1] && strcmp(parts[0], "abc") == 0);
    ft_free_tab(parts);
    for (failure = 1; failure <= 8; failure++)
    {
        long baseline = live;
        malloc_count = 0;
        malloc_failure = failure;
        parts = ft_split("a bb ccc", ' ');
        malloc_failure = 0;
        ft_free_tab(parts);
        assert(live == baseline);
        malloc_count = 0;
        malloc_failure = failure;
        text = ft_strtrim("  abc  ", " ");
        malloc_failure = 0;
        free(text);
        assert(live == baseline);
        malloc_count = 0;
        malloc_failure = failure;
        text = ft_substr("abc", 99, SIZE_MAX);
        malloc_failure = 0;
        free(text);
        assert(live == baseline);
        text = ft_strdup("abc");
        malloc_count = 0;
        malloc_failure = failure;
        text = ft_strjoin_gnl(text, "def");
        malloc_failure = 0;
        free(text);
        assert(live == baseline);
        malloc_count = 0;
        malloc_failure = failure;
        text = ft_strjoin_gnl(NULL, "abc");
        malloc_failure = 0;
        free(text);
        assert(live == baseline);
        checks += 5;
    }
}

static void *duplicate_content(void *content)
{
    return ft_strdup(content);
}

static void lists(void)
{
    t_list third = {(void *)"c", NULL}, second = {(void *)"b", &third};
    t_list first = {(void *)"a", &second}, *mapped;
    for (long failure = 0; failure <= 7; failure++)
    {
        long baseline = live;
        malloc_count = 0;
        malloc_failure = failure;
        mapped = ft_lstmap(&first, duplicate_content, free);
        malloc_failure = 0;
        if (mapped)
            assert(ft_lstsize(mapped) == 3);
        ft_lstclear(&mapped, free);
        assert(!mapped && live == baseline);
        checks++;
    }
    assert(!ft_lstmap(&first, NULL, free));
    ft_lstadd_front(NULL, NULL);
    ft_lstadd_back(NULL, NULL);
}

static void lines(void)
{
    FILE *first, *second;
    char *line, *large = malloc((size_t)BUFFER_SIZE + 2);
    assert(large);
    memset(large, 'x', (size_t)BUFFER_SIZE + 2);
    assert(!get_next_line(-1) && !get_next_line(GNL_MAX_FD));
    assert(!get_next_line(1048575));
    first = input_file("\na\nlast", 7);
    second = input_file("other\n", 6);
    check_string(get_next_line(fileno(first)), "\n");
    check_string(get_next_line(fileno(second)), "other\n");
    check_string(get_next_line(fileno(first)), "a\n");
    assert(!get_next_line(fileno(second)));
    check_string(get_next_line(fileno(first)), "last");
    assert(!get_next_line(fileno(first)));
    fclose(first);
    fclose(second);
    for (long failure = 1; failure <= 2; failure++)
    {
        long baseline = live;
        first = input_file(large, (size_t)BUFFER_SIZE + 2);
        read_count = 0;
        read_failure = failure;
        assert(!get_next_line(fileno(first)));
        read_failure = 0;
        assert(live == baseline);
        fclose(first);
        checks++;
    }
    for (long failure = 1; failure <= 12; failure++)
    {
        long baseline = live;
        first = input_file("abc\ndef\n", 8);
        malloc_count = 0;
        malloc_failure = failure;
        line = get_next_line(fileno(first));
        malloc_failure = 0;
        free(line);
        while ((line = get_next_line(fileno(first))))
            free(line);
        fclose(first);
        assert(live == baseline);
        checks++;
    }
    first = input_file("", 0);
    assert(!get_next_line(fileno(first)));
    fclose(first);
    first = input_file("a\nb\n", 4);
    int fd = fileno(first);
    check_string(get_next_line(fd), "a\n");
    fclose(first);
    assert(!get_next_line(fd));
    free(large);
}

static void printing(void)
{
    int channels[2], saved, actual_size, expected_size;
    char actual[512], expected[512];
    ssize_t length;
    assert(pipe(channels) == 0);
    saved = dup(1);
    assert(saved >= 0 && dup2(channels[1], 1) == 1);
    close(channels[1]);
    expected_size = snprintf(expected, sizeof(expected),
        "%s %c %d %i %u %x %X %p %p %%", "text", 0, INT_MIN,
        INT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, (void *)expected, (void *)0);
    actual_size = ft_printf("%s %c %d %i %u %x %X %p %p %%",
        "text", 0, INT_MIN, INT_MAX, UINT_MAX, UINT_MAX, UINT_MAX,
        (void *)expected, (void *)0);
    assert(actual_size == expected_size);
    assert(dup2(saved, 1) == 1);
    length = read(channels[0], actual, sizeof(actual));
    assert(length == expected_size);
    assert(memcmp(actual, expected, (size_t)length) == 0);
    close(channels[0]);
    assert(ft_printf("") == 0 && ft_printf(NULL) == -1 && ft_printf("%") == -1);
    int sink = open("/dev/null", O_WRONLY);
    assert(sink >= 0 && dup2(sink, 1) == 1);
    close(sink);
    for (long failure = 1; failure <= 20; failure++)
    {
        write_count = 0;
        write_failure = failure;
        actual_size = ft_printf("a%s:%d:%x:%u:%p", "bc", INT_MIN,
            0xabcdefU, UINT_MAX, (void *)expected);
        write_failure = 0;
        assert(actual_size == -1);
        checks++;
    }
    assert(dup2(saved, 1) == 1);
    close(saved);
    checks += 5;
}

int main(void)
{
    strings();
    memory_and_numbers();
    split_and_allocation_failures();
    lists();
    if (BUFFER_SIZE > 0)
        lines();
    else
        assert(!get_next_line(0));
    printing();
    assert(live == 0);
    fprintf(stderr, "PASS: %u checks (BUFFER_SIZE=%d), no tracked leaks\n",
        checks, BUFFER_SIZE);
    return 0;
}
"""


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--sanitize", action="store_true")
    parser.add_argument("--valgrind", action="store_true")
    parser.add_argument("--buffer-size", type=int, default=100)
    args = parser.parse_args()
    if args.sanitize and args.valgrind:
        parser.error("run sanitizers and Valgrind separately")
    root = Path(__file__).resolve().parent.parent
    environment = dict(os.environ, CCACHE_DISABLE="1")
    with tempfile.TemporaryDirectory(prefix="libft-regressions-") as directory:
        stage = Path(directory)
        harness = stage / "check.c"
        harness.write_text(HARNESS)
        command = [
            os.environ.get("CC", "gcc"), "-std=c99", "-pedantic",
            "-Wall", "-Wextra", "-Werror", "-g", "-D_POSIX_C_SOURCE=200809L",
            f"-DBUFFER_SIZE={args.buffer_size}", f"-I{root}",
        ]
        if args.sanitize:
            command += ["-fsanitize=address,undefined", "-fno-omit-frame-pointer"]
        command += [str(harness)] + [str(p) for p in sorted(root.glob("*.c"))]
        command += [
            "-Wl,--wrap=malloc", "-Wl,--wrap=free", "-Wl,--wrap=read",
            "-Wl,--wrap=write", "-o", str(stage / "check"),
        ]
        subprocess.run(command, check=True, env=environment)
        runner = [str(stage / "check")]
        if args.valgrind:
            runner = [
                "valgrind", "--quiet", "--leak-check=full",
                "--show-leak-kinds=all", "--errors-for-leak-kinds=all",
                "--error-exitcode=99",
            ] + runner
        environment["ASAN_OPTIONS"] = "detect_leaks=1:allocator_may_return_null=1"
        environment["UBSAN_OPTIONS"] = "halt_on_error=1"
        subprocess.run(runner, check=True, env=environment, timeout=60)


if __name__ == "__main__":
    main()
