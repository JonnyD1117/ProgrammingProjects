from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, cmake_layout

class ArgumentParserProject(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("gtest/1.16.0")
        self.requires("jsoncons/1.3.0")
        self.requires("yaml-cpp/0.8.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = "ConanPresets.json"
        tc.generate()
