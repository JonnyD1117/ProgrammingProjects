# C++ Argument Parser

This project is a small "helper" project. I have always wanted to make a thin argument parser (similar to Python's ArgParse  libary) that would enable me to develop CLI's in C++ without front-ending another scripting language to control the execution and parameterization of C++ executables. While I am aware that other C++ libraries exist for this purpose, I think this a nice small project that I would like to keep around and develope with the hope of using it in my larger projects.

## Features

- [x] Python-like `add_argument()` interface to specify expected arguments
- [x] Handle passing Integers
- [x] Handle passing Doubles 
- [x] Handle passing String
- [ ] Handle passing Booleans
- [x] Helpful Usage screen when `--help` or `--h` are passed (these are **reserved** and cannot be overriden)
- [ ] CLI explicit assignment (`--test_value=52`)
- [ ] `--config` option to enable YAML or JSON configuration which the CLI can manually override 
- [ ] Coexistance of Long & Short cli options
- [ ] Python-like Argument Groups (Group arguments into groups)
- [ ] Python-like REQUIRED arguments
- [ ] Python-like sub-parser mechanism