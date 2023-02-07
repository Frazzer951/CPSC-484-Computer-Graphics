import matplotlib.pyplot as plt
import numpy as np
from alive_progress import alive_bar


def normalize(vector):
    return vector / np.linalg.norm(vector)


def reflected(vector, axis):
    return vector - 2 * np.dot(vector, axis) * axis


def sphere_intersect(center, radius, ray_origin, ray_direction):
    b = 2 * np.dot(ray_direction, ray_origin - center)
    c = np.linalg.norm(ray_origin - center) ** 2 - radius**2
    delta = b**2 - 4 * c
    if delta > 0:
        t1 = (-b + np.sqrt(delta)) / 2
        t2 = (-b - np.sqrt(delta)) / 2
        if t1 > 0 and t2 > 0:
            return min(t1, t2)
    return None


def nearest_intersected_object(objects, ray_origin, ray_direction):
    distances = [sphere_intersect(obj["center"], obj["radius"], ray_origin, ray_direction) for obj in objects]
    nearest_object = None
    min_distance = np.inf
    for index, distance in enumerate(distances):
        if distance and distance < min_distance:
            min_distance = distance
            nearest_object = objects[index]
    return nearest_object, min_distance


def hsv_to_rgb(h, s, v):
    if s == 0.0:
        return (v, v, v)
    i = int(h * 6.0)
    f = (h * 6.0) - i
    p, q, t = v * (1.0 - s), v * (1.0 - s * f), v * (1.0 - s * (1.0 - f))
    i %= 6
    if i == 0:
        return (v, t, p)
    if i == 1:
        return (q, v, p)
    if i == 2:
        return (p, v, t)
    if i == 3:
        return (p, q, v)
    if i == 4:
        return (t, p, v)
    if i == 5:
        return (v, p, q)


width = 3000  # 300
height = 2000  # 200

max_depth = 3

camera = np.array([0, 0, 1])
ratio = float(width) / height
screen = (-1, 1 / ratio, 1, -1 / ratio)  # left, top, right, bottom

light = {
    "position": np.array([5, 5, 5]),
    "ambient": np.array([1, 1, 1]),
    "diffuse": np.array([1, 1, 1]),
    "specular": np.array([1, 1, 1]),
}

objects = [
    {
        "center": np.array([0, 0.2, -1]),
        "radius": 0.5,
        "ambient": np.array([0.2, 0.2, 0.2]),
        "diffuse": np.array([0.5, 0.5, 0.5]),
        "specular": np.array([1, 1, 1]),
        "shininess": 100,
        "reflection": 0.5,
    },
    {
        "center": np.array([0, -9000, 0]),
        "radius": 9000 - 0.7,
        "ambient": np.array([0.1, 0.1, 0.1]),
        "diffuse": np.array([0.6, 0.6, 0.6]),
        "specular": np.array([1, 1, 1]),
        "shininess": 100,
        "reflection": 0.5,
    },
]

num_spheres = 15
delta_angle = 360 / num_spheres
radius = 0.7

for i in range(num_spheres):
    angle = np.radians(i * delta_angle)
    x = radius * np.sin(angle)
    y = radius * np.cos(angle) + 0.2
    objects.append(
        {
            "center": np.array([x, y, -1]),
            "radius": 0.1,
            "ambient": np.array(hsv_to_rgb(np.degrees(angle) / 360, 1, 1)),
            "diffuse": np.array([0.7, 0.7, 0.7]),
            "specular": np.array([1, 1, 1]),
            "shininess": 100,
            "reflection": 0.5,
        }
    )


image = np.zeros((height, width, 3))
with alive_bar(width * height) as bar:
    for i, y in enumerate(np.linspace(screen[1], screen[3], height)):
        for j, x in enumerate(np.linspace(screen[0], screen[2], width)):
            # screen is on origin
            pixel = np.array([x, y, 0])
            origin = camera
            direction = normalize(pixel - origin)

            color = np.zeros((3))
            reflection = 1

            for k in range(max_depth):
                # check for intersections
                nearest_object, min_distance = nearest_intersected_object(objects, origin, direction)
                if nearest_object is None:
                    break

                intersection = origin + min_distance * direction
                normal_to_surface = normalize(intersection - nearest_object["center"])
                shifted_point = intersection + 1e-5 * normal_to_surface
                intersection_to_light = normalize(light["position"] - shifted_point)

                _, min_distance = nearest_intersected_object(objects, shifted_point, intersection_to_light)
                intersection_to_light_distance = np.linalg.norm(light["position"] - intersection)
                is_shadowed = min_distance < intersection_to_light_distance

                if is_shadowed:
                    break

                illumination = np.zeros((3))

                # ambiant
                illumination += nearest_object["ambient"] * light["ambient"]

                # diffuse
                illumination += nearest_object["diffuse"] * light["diffuse"] * np.dot(intersection_to_light, normal_to_surface)

                # specular
                intersection_to_camera = normalize(camera - intersection)
                H = normalize(intersection_to_light + intersection_to_camera)
                illumination += (
                    nearest_object["specular"]
                    * light["specular"]
                    * np.dot(normal_to_surface, H) ** (nearest_object["shininess"] / 4)
                )

                # reflection
                color += reflection * illumination
                reflection *= nearest_object["reflection"]

                origin = shifted_point
                direction = reflected(direction, normal_to_surface)

            image[i, j] = np.clip(color, 0, 1)
            bar()


plt.imsave("image.png", image)

# imgplot = plt.imshow(image)
# plt.show()
