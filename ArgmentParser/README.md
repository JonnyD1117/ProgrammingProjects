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
- [x] Support manual adding of YAML || Json Configs (e.g. `add_config(conf_path);`)
  - [x] YAML Config Parsing
  - [ ] Json Config Parsing
- [ ] Automatically set config file by using `--config <file-path>`
- [ ] Ensure manually arguments `--my_var 42` can override an option set in a config (either via `--config` || `add_config()`)
- [ ] Support short & long option prefixes (e.g. `--var` || `-v`) automatically
- [ ] Python-like Argument Groups (Group arguments into groups)
- [ ] Python-like REQUIRED arguments
- [ ] Python-like sub-parser mechanism