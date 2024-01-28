import os
import subprocess
from pathlib import Path

from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name: str, sourcedir: str = "") -> None:
        super().__init__(name, sources=[])
        self.sourcedir = os.fspath(Path(sourcedir).resolve())


class CMakeBuild(build_ext):
    def build_extension(self, ext: CMakeExtension) -> None:
        ext_fullpath = Path.cwd() / self.get_ext_fullpath(ext.name)
        extdir = ext_fullpath.parent.resolve()

        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}{os.sep}",
            "-DCMAKE_BUILD_TYPE=Release", 
            "-GNinja",
        ]
        build_temp = Path(self.build_temp) / ext.name
        build_temp.mkdir(parents=True, exist_ok=True)

        subprocess.run(["cmake", *cmake_args, "-B", build_temp, "-S", ext.sourcedir])
        subprocess.run( ["cmake", "--build", build_temp])


setup(
    name="module_name",
    version="0.0.1",
    author="wangzj",
    author_email="wangzj@wanyantech.com",
    description="A test project using pybind11 and CMake",
    long_description="",
    ext_modules=[CMakeExtension("module_name")],
    cmdclass={"build_ext": CMakeBuild},
    zip_safe=False,
    extras_require={"test": ["pytest>=6.0"]},
    python_requires=">=3.7",
)
