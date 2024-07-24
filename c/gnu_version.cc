#include <iostream>
#ifdef __GLIBC__
#include <gnu/libc-version.h>
#endif

int
main(void)
{
    std::cout << "g++: " << __GNUC__ << "." << __GNUC_MINOR__ << "."<<  __GNUC_PATCHLEVEL__ << std::endl;
#ifdef __GLIBC__
    std::cout << "GNU libc compile-time version: " << __GLIBC__ << "." << __GLIBC_MINOR__ << std::endl;
    std::cout << "GNU libc runtime version: " << gnu_get_libc_version() << std::endl;
  return 0;
#else
  puts("Not the GNU C Library");
  return 1;
#endif
}
