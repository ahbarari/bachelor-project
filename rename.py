import os

move = input("Please enter move: ")
name = input("Please enter csv name: ")
path = f'dataset/{move}/'
files = os.listdir(path)

counter = 1
for file in files:
    _, ext = os.path.splitext(file)
    os.rename(os.path.join(path, file), os.path.join(path, name + str(counter) + ext))
    counter += 1
