from PIL import Image
from os import listdir, walk, getcwd, remove
from sys import argv

def get_bmp_files():
    extensions = ["png", "jpg"]
    f = []
    for (dirpath, dirnames, filenames) in walk(getcwd()):
        f.extend(filenames)
        break

    for file in f:
        for string in range(len(file)):
            if file[string:] in extensions:
                img = Image.open(file)
                bmp = file[:string - 1] + ".bmp"
                try:
                    img.save(f"../bmp/{bmp}")

                except:
                    print("Can't load", file)


if __name__ == '__main__':
    get_bmp_files()