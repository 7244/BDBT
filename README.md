# Buildable Dynamic Binary Tree
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

BDBT is binary tree library that supports many build settings.

## Features
- Has too many build options
- Supports cpp and c

### Usage
1. Build options
  ```c
  // TODO fill here
  ```

### Depends On
* https://github.com/7244/WITCH requires base features of WITCH.
* https://github.com/7244/bcontainer
* if build setting requires, memory allocation functions (user or `WITCH/generic_alloc.h` can define them):
  * `__generic_mmap` or `__generic_malloc` or `malloc`
  * `__generic_mremap` or `__generic_realloc` or `realloc`
  * `__generic_munmap` or `__generic_free` or `free`

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
