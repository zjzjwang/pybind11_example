import build.src.module_name as mod
from build.src.module_name import *
from PIL import Image
import time
from concurrent.futures import ThreadPoolExecutor


print(dir(mod))

m = PySomeClass(5)

print(m)

print(some_fn_python_name(2, 5))

print(m.multiply(15))
print(m.multiply_list([1, 3, 10]))
print(m.multiply_two(1, 2))
print(m.make_image())

img = m.make_image()

print(type(img), img.dtype)

Image.fromarray(img, "L").save("/tmp/test.png")

print(m.image)

print(m.multiplier)
m.multiplier = 10
print(m.multiplier)



with ThreadPoolExecutor(4) as ex:
    ex.map(lambda x: m.func_sleep(), [None] * 4)


