import pandas as pd
import os

path = "."
dir_list = os.listdir(path)
csv_files = [file for file in dir_list if file.endswith('.csv')]
print(csv_files)

df = pd.concat(map(pd.read_csv, csv_files))

df.to_csv('dataset.csv', index=False)
