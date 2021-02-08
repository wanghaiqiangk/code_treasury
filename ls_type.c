/*
 * Derive from coreutils-8.28 ls.c
 * Things about:
 * - how to get the maximum and minimum value of a specific type
 * - judge a type unsigned or singed
 * - type width
 */

#include <iostream>
#include <stdint.h>
#include <sys/stat.h>
#include <boost/type_index.hpp>
#include <limits.h>

using boost::typeindex::type_id_with_cvr;

// #define CHAR_BIT 8

#define TYPE_MINIMUM(t) ((t) ~ TYPE_MAXIMUM (t))
#define TYPE_MAXIMUM(t)                                         \
    ((t) (! TYPE_SIGNED (t)                                     \
          ? (t) -1                                              \
          : ((((t) 1 << (TYPE_WIDTH (t) - 2)) - 1) * 2 + 1)))

#define TYPE_WIDTH(t) (sizeof (t) * CHAR_BIT)
#define TYPE_SIGNED(t) (! ((t) 0 < (t) -1))
// (! ((off_t) 0 < (off_t) -1))

#ifndef OFF_T_MIN
# define OFF_T_MIN TYPE_MINIMUM (off_t)
#endif

#ifndef OFF_T_MAX
# define OFF_T_MAX TYPE_MAXIMUM (off_t)
#endif

static uintmax_t
unsigned_file_size (off_t size)
{
    return size + (size < 0) * ((uintmax_t) OFF_T_MAX - OFF_T_MIN + 1);
}

int main(int argc, char const *argv[])
{
    std::cout << type_id_with_cvr<uintmax_t>().pretty_name() << std::endl;
    std::cout << type_id_with_cvr<off_t>().pretty_name() << std::endl;
    std::cout << sizeof(uintmax_t) << std::endl;

    std::cout << unsigned_file_size(-10) << std::endl;
    std::cout << unsigned_file_size(10) << std::endl;
    off_t offtmin = OFF_T_MIN;
    off_t offtmax = OFF_T_MAX;
    std::cout << OFF_T_MIN << std::endl;
    std::cout << OFF_T_MAX << std::endl;
    std::cout << (uintmax_t) OFF_T_MAX - OFF_T_MIN << std::endl;
    return 0;
}
