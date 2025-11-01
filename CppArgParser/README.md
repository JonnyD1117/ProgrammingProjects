# C++ Argument Parser

This project is a small "helper" project. I have always wanted to make a thin argument parser (similar to Python's ArgParse  libary) that would enable me to develop CLI's in C++ without front-ending another scripting language to control the execution and parameterization of C++ executables. While I am aware that other C++ libraries exist for this purpose, I think this a nice small project that I would like to keep around and develope with the hope of using it in my larger projects.

## Features

- [ ] Handle passing of (int, double, string, bool) values 
- [ ] Simple and intuitive interfaces to extract values given in CLI within the C++ application
- [ ] Python-like `add_argument()` interface to specify expected arguments
- [ ] Python-like Argument Groups (Group arguments into groups)
- [ ] Python-like REQUIRED arguments
- [ ] Time/Interest permitting it would be cool to create a python-like sub-parser
- [ ] `--config` option to enable YAML or JSON configuration which the CLI can manually override (enabling custom configurations) 
- [ ] Helpful Usage screen when `--help` or `--h` are passed (these are **reserved** and cannot be overriden)

