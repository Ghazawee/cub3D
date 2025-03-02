import os

def generate_xpm(width, height, filename):
    header = f'/* XPM */\nstatic char *{filename.split(".")[0]}[] = {{\n'
    header += f'"{width} {height} 2 1",\n'
    header += '"0 c #FF0000",\n"1 c #00FF00",\n'

    pixels = ',\n'.join(['"' + ''.join(['0' if (x + y) % 2 == 0 else '1' for x in range(width)]) + '"' for y in range(height)])
    footer = '\n};\n'
    xpm_data = header + pixels + footer
    file_path = os.path.join(os.getcwd(), filename)  # Save in the current directory
    with open(file_path, "w") as f:
        f.write(xpm_data)

    return file_path

# Create the files
verylarge_xpm_path = generate_xpm(8000, 8000, "large_texture.xpm")
# irregular_xpm_path = generate_xpm(64, 32, "irregular_texture.xpm")
