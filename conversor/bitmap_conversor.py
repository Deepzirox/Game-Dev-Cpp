from PIL import Image
from os import listdir, walk, getcwd, remove
from sys import argv
from screeninfo import get_monitors

def get_bmp_files(new_size):
    extensions = ["png", "jpg"]
    f = []
    for (dirpath, dirnames, filenames) in walk(getcwd()):
        f.extend(filenames)
        break

    for file in f:
        for string in range(len(file)):
            if file[string:] in extensions:
                img = Image.open(file)
                img = img.resize(new_size)
                bmp = file[:string - 1] + ".bmp"
                try:
                    img.save(bmp)
                except:
                    print("Can't load", file)


if __name__ == '__main__':
    mon = get_monitors()
    for n in mon:
        w = n.width
        h = n.height
    else:
        get_bmp_files((w, h))
