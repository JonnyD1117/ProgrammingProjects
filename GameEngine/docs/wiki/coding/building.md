# Build Project

## Install External Dependencies

A key objective of this project is to keep external dependencies to a minimum,
unless they can quickly be added and built by Conan directly.

- [ ] CMake
- [ ] Clang
- [ ] Clang-Tidy
- [ ] Clang-Format
- [ ] Conan
- [ ] mdbook (documentation generation)
- [ ] pipx

## Build Project

### Build & Install External Dependencies

```cpp
make install_deps
```

### Configure & Build from CMake

```cpp
cmake config build
```

### Run Project

```cpp
make run
```
