import numpy as np
import matplotlib.pyplot as plt
from alive_progress import alive_bar

width = 300
height = 200

camera = np.array([0, 0, 1])
ratio = float(width) / height
screen = (-1, 1 / ratio, 1, -1 / ratio)  # left, top, right, bottom

image = np.zeros((height, width, 3))
with alive_bar(width * height) as bar:
    for i, y in enumerate(np.linspace(screen[1], screen[3], height)):
        for j, x in enumerate(np.linspace(screen[0], screen[2], width)):
            # image[i, j] = ...
            bar()
            # print("progress: %d/%d" % (i + 1, height))
            # print(f"progress: {i*width+j:5}/{width*height}")

# plt.imsave("image.png", image)

imgplot = plt.imshow(image)
plt.show()
