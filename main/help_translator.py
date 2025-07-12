from PIL import Image
import numpy as np
import os
import sys
import re

# Define color to BlockType mapping
color_to_block = {
    (255, 255, 255): "EMPTY",  # white - path
    (0, 0, 0): "WALL",  # black - wall
    (255, 0, 0): "BALL",  # red
    (0, 255, 0): "FINISH",  # green
    (0, 0, 255): "BORDER"  # blue
}

# Your block-to-color mapping
block_to_color = {
    "EMPTY": (" ", "white"),
    "WALL": ("#", "grey"),
    "BALL": ("o", "red"),
    "FINISH": ("F", "green"),
    "BORDER": ("*", "blue")
}


def help_1():

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


"""
    block_map = [
        ['EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['BALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'FINISH'],
    ]

"""
"""
         block_map = [
        ['EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'FINISH'],
        ['EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL'],
        ['BALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY'],
    ]
    """
"""['EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'BALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'FINISH', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],"""

"""
block_map1 = [
        ['WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'BALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL'],

    ]

    block_map2 = [
        ['WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'FINISH', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],

    ]
"""


"""
base
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],

"""


def help_2():
    import pygame
    import sys

    # Define block map
    block_map1 = [
        ['WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'BALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL'],

    ]

    block_map2 = [
        ['WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'FINISH', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],

    ]

    # Define block colors
    block_colors = {
        "EMPTY": (255, 255, 255),  # White
        "WALL": (0, 0, 0),  # Black
        "BALL": (255, 0, 0),  # Red
        "FINISH": (0, 255, 0),  # Green
        "BORDER": (0, 0, 255)  # Blue
    }

    # Settings
    CELL_SIZE = 20
    ROWS = len(block_map1)
    COLS = len(block_map1[0])
    PADDING = 40  # space between maps

    WIDTH = COLS * CELL_SIZE * 2 + PADDING
    HEIGHT = ROWS * CELL_SIZE

    # Initialize Pygame
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Block Map Viewer")

    # Draw the map
    def draw_map(map_data, offset_x=0):
        for i, row in enumerate(map_data):
            for j, block in enumerate(row):
                color = block_colors.get(block, (128, 128, 128))
                rect = pygame.Rect(offset_x + j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE)
                pygame.draw.rect(screen, color, rect)
                pygame.draw.rect(screen, (50, 50, 50), rect, 1)  # Grid lines

    # Main loop
    running = True
    while running:
        screen.fill((200, 200, 200))  # Background
        draw_map(block_map1, offset_x=0)
        draw_map(block_map2, offset_x=COLS * CELL_SIZE + PADDING)
        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

    pygame.quit()
    sys.exit()


def help_3():

    s = """
         block_map1 = [
        ['WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'BALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY'],
        ['WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL'],

    ]

    block_map2 = [
        ['WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'FINISH', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL'],
        ['WALL', 'WALL', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'EMPTY', 'EMPTY', 'WALL'],
        ['EMPTY', 'EMPTY', 'EMPTY', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL'],
        ['WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'EMPTY', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL', 'WALL'],

    ]

    ]

    """

    s = s.replace('[', '{').replace(']', '}').replace("'", "")
    print(s)


if __name__ == '__main__':
    help_3()
