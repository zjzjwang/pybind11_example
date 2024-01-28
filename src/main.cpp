#include "pybind11/numpy.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include <iostream>
#include <thread>
#include <vector>

namespace py = pybind11;

float some_fn(float arg1, float arg2) { return arg1 + arg2; }

class SomeClass {
  float multiplier;

public:
  SomeClass(float multiplier_) : multiplier(multiplier_) {}

  float multiply(float input) { return multiplier * input; }

  std::vector<float> multiply_list(std::vector<float> items) {
    for (auto &i : items) {
      i = multiply(i);
    }
    return items;
  }

  py::tuple multiply_two(float one, float two) {
    return py::make_tuple(multiply(one), multiply(two));
  }

  std::vector<std::vector<uint8_t>> make_image() {
    auto out = std::vector<std::vector<uint8_t>>();
    for (auto i = 0; i < 128; i++) {
      out.push_back(std::vector<uint8_t>(64));
    }
    for (auto i = 0; i < 30; i++) {
      for (auto j = 0; j < 30; j++) {
        out[i][j] = 255;
      }
    }
    return out;
  }

  void set_mult(float val) { multiplier = val; }

  float get_mult() { return multiplier; }

  void func_sleep() {
    py::gil_scoped_release release;
    std::cout << "starting fn" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "end fn" << std::endl;
  }
};

PYBIND11_MODULE(module_name, handle) {
  handle.doc() = "This is the module docs. Ha";
  handle.def("some_fn_python_name", &some_fn);

  py::class_<SomeClass>(handle, "PySomeClass")
      .def(py::init<float>())
      .def("multiply", &SomeClass::multiply)
      // .def("multiply_two", &SomeClass::multiply_two)
      .def("multiply_two",
           [](SomeClass &self, float one, float two) {
             return py::make_tuple(self.multiply(one), self.multiply(two));
           })
      .def_property_readonly("image",
                             [](SomeClass &self) {
                               py::array_t<uint8_t> out =
                                   py::cast(self.make_image());
                               return out;
                             })
      .def("make_image",
           [](SomeClass &self) {
             py::array_t<uint8_t> out = py::cast(self.make_image());
             return out;
           })
      .def_property("multiplier", &SomeClass::get_mult, &SomeClass::set_mult)
      .def("func_sleep", &SomeClass::func_sleep)
      .def("multiply_list", &SomeClass::multiply_list);
}
