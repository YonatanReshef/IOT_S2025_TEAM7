from PIL import Image
import numpy as np
import os
import sys
import re


# Define color to BlockType mapping
color_to_block = {
    (255, 255, 255): "EMPTY",   # white - path
    (0, 0, 0): "WALL",          # black - wall
    (255, 0, 0): "BALL",        # red
    (0, 255, 0): "FINISH",      # green
    (0, 0, 255): "BORDER"       # blue
}


def image_to_cpp_array(image_path):
    img = Image.open(image_path).convert("RGB")
    img = img.resize((16, 16))
    arr = np.array(img)

    cpp_lines = []
    cpp_lines.append("BlockType level[16][16] = {")
    for row in arr:
        line = "    { " + ", ".join(color_to_block.get(tuple(pixel), "EMPTY") for pixel in row) + " },"
        cpp_lines.append(line)
    cpp_lines.append("};")

    return "\n".join(cpp_lines)


# Example usage
directory = r"D:\University\Semester 8\IOT"
for i in range(5):
    for j in range(5):
        path = rf"D:\University\Semester 8\IOT\maze{i}_{j}.png"
        if os.path.exists(path):
            print(f"maze num: maze{i}_{j}:")
            cpp_code = image_to_cpp_array(path)
            print(cpp_code)
