# needed libraries
import os
import pandas as pd

# input
move = input("Please enter move: ")
name = input("Please enter csv name: ")

# path of dataset
path = f'dataset/{move}/'
files = os.listdir(path)

# list for items
items = []

# feature extracting
for file in files:

    try:
        # read csv file
        df = pd.read_csv(path + file)

        # select sensors
        gyroscope_df = df.loc[
            df['ACC_or_GYR'] == 'GYR'
            ].reset_index(drop=True)
        accumulator_df = df.loc[
            df['ACC_or_GYR'] == 'ACC'
            ].reset_index(drop=True)

        # normalized gyro
        gyro_max = gyroscope_df[['x', 'y', 'z']].max()
        df_max = gyro_max.max()
        gyroscope_df = gyroscope_df[['x', 'y', 'z']] / df_max

        # normalized acc
        acc_max = accumulator_df[['x', 'y', 'z']].max()
        df_max = acc_max.max()
        accumulator_df = accumulator_df[['x', 'y', 'z']] / df_max

        # 25 gyro axis
        gyro_x_25 = gyroscope_df['x'].quantile(0.25)
        gyro_y_25 = gyroscope_df['y'].quantile(0.25)
        gyro_z_25 = gyroscope_df['z'].quantile(0.25)

        # 25 acc axis
        acc_x_25 = accumulator_df['x'].quantile(0.25)
        acc_y_25 = accumulator_df['y'].quantile(0.25)
        acc_z_25 = accumulator_df['z'].quantile(0.25)

        # 75 gyro axis
        gyro_x_75 = gyroscope_df['x'].quantile(0.75)
        gyro_y_75 = gyroscope_df['y'].quantile(0.75)
        gyro_z_75 = gyroscope_df['z'].quantile(0.75)

        # 75 acc axis
        acc_x_75 = accumulator_df['x'].quantile(0.75)
        acc_y_75 = accumulator_df['y'].quantile(0.75)
        acc_z_75 = accumulator_df['z'].quantile(0.75)

        # mean gyro axis
        gyro_x_mean = gyroscope_df['x'].mean()
        gyro_y_mean = gyroscope_df['y'].mean()
        gyro_z_mean = gyroscope_df['z'].mean()

        # mean acc axis
        acc_x_mean = accumulator_df['x'].mean()
        acc_y_mean = accumulator_df['y'].mean()
        acc_z_mean = accumulator_df['z'].mean()

        # median gyro axis
        gyro_x_median = gyroscope_df['x'].median()
        gyro_y_median = gyroscope_df['y'].median()
        gyro_z_median = gyroscope_df['z'].median()

        # median acc axis
        acc_x_median = accumulator_df['x'].median()
        acc_y_median = accumulator_df['y'].median()
        acc_z_median = accumulator_df['z'].median()

        # std gyro axis
        gyro_x_std = gyroscope_df['x'].std()
        gyro_y_std = gyroscope_df['y'].std()
        gyro_z_std = gyroscope_df['z'].std()

        # std acc axis
        acc_x_std = accumulator_df['x'].std()
        acc_y_std = accumulator_df['y'].std()
        acc_z_std = accumulator_df['z'].std()

        # var gyro axis
        gyro_x_var = gyroscope_df['x'].var()
        gyro_y_var = gyroscope_df['y'].var()
        gyro_z_var = gyroscope_df['z'].var()

        # var acc axis
        acc_x_var = accumulator_df['x'].var()
        acc_y_var = accumulator_df['y'].var()
        acc_z_var = accumulator_df['z'].var()

        # min gyro axis
        gyro_x_min = gyroscope_df['x'].min()
        gyro_y_min = gyroscope_df['y'].min()
        gyro_z_min = gyroscope_df['z'].min()

        # min acc axis
        acc_x_min = accumulator_df['x'].min()
        acc_y_min = accumulator_df['y'].min()
        acc_z_min = accumulator_df['z'].min()

        # max gyro axis
        gyro_x_max = gyroscope_df['x'].max()
        gyro_y_max = gyroscope_df['y'].max()
        gyro_z_max = gyroscope_df['z'].max()

        # max acc axis
        acc_x_max = accumulator_df['x'].max()
        acc_y_max = accumulator_df['y'].max()
        acc_z_max = accumulator_df['z'].max()

        # kurtosis gyro axis
        gyro_x_kurtosis = gyroscope_df['x'].kurtosis()
        gyro_y_kurtosis = gyroscope_df['y'].kurtosis()
        gyro_z_kurtosis = gyroscope_df['z'].kurtosis()

        # kurtosis acc axis
        acc_x_kurtosis = accumulator_df['x'].kurtosis()
        acc_y_kurtosis = accumulator_df['y'].kurtosis()
        acc_z_kurtosis = accumulator_df['z'].kurtosis()

        # skew gyro axis
        gyro_x_skew = gyroscope_df['x'].skew()
        gyro_y_skew = gyroscope_df['y'].skew()
        gyro_z_skew = gyroscope_df['z'].skew()

        # skew acc axis
        acc_x_skew = accumulator_df['x'].skew()
        acc_y_skew = accumulator_df['y'].skew()
        acc_z_skew = accumulator_df['z'].skew()

        item = [
            move,
            gyro_x_mean,
            gyro_y_mean,
            gyro_z_mean,
            acc_x_mean,
            acc_y_mean,
            acc_z_mean,
            gyro_x_median,
            gyro_y_median,
            gyro_z_median,
            acc_x_median,
            acc_y_median,
            acc_z_median,
            gyro_x_std,
            gyro_y_std,
            gyro_z_std,
            acc_x_std,
            acc_y_std,
            acc_z_std,
            gyro_x_var,
            gyro_y_var,
            gyro_z_var,
            acc_x_var,
            acc_y_var,
            acc_z_var,
            gyro_x_min,
            gyro_y_min,
            gyro_z_min,
            acc_x_min,
            acc_y_min,
            acc_z_min,
            gyro_x_max,
            gyro_y_max,
            gyro_z_max,
            acc_x_max,
            acc_y_max,
            acc_z_max,
            gyro_x_25,
            gyro_y_25,
            gyro_z_25,
            acc_x_25,
            acc_y_25,
            acc_z_25,
            gyro_x_75,
            gyro_y_75,
            gyro_z_75,
            acc_x_75,
            acc_y_75,
            acc_z_75,
            gyro_x_kurtosis,
            gyro_y_kurtosis,
            gyro_z_kurtosis,
            acc_x_kurtosis,
            acc_y_kurtosis,
            acc_z_kurtosis,
            gyro_x_skew,
            gyro_y_skew,
            gyro_z_skew,
            acc_x_skew,
            acc_y_skew,
            acc_z_skew,
        ]
        items.append(item)
    except TypeError:
        pass

columns = [
    'type',
    'mean gyro x',
    'mean gyro y',
    'mean gyro z',
    'mean acc x',
    'mean acc y',
    'mean acc z',
    'median gyro x',
    'median gyro y',
    'median gyro z',
    'median acc x',
    'median acc y',
    'median acc z',
    'std gyro x',
    'std gyro y',
    'std gyro z',
    'std acc x',
    'std acc y',
    'std acc z',
    'var gyro x',
    'var gyro y',
    'var gyro z',
    'var acc x',
    'var acc y',
    'var acc z',
    'min gyro x',
    'min gyro y',
    'min gyro z',
    'min acc x',
    'min acc y',
    'min acc z',
    'max gyro x',
    'max gyro y',
    'max gyro z',
    'max acc x',
    'max acc y',
    'max acc z',
    '25 gyro x',
    '25 gyro y',
    '25 gyro z',
    '25 acc x',
    '25 acc y',
    '25 acc z',
    '75 gyro x',
    '75 gyro y',
    '75 gyro z',
    '75 acc x',
    '75 acc y',
    '75 acc z',
    'gyro x kurtosis',
    'gyro y kurtosis',
    'gyro z kurtosis',
    'acc x kurtosis',
    'acc y kurtosis',
    'acc z kurtosis',
    'gyro x skew',
    'gyro y skew',
    'gyro z skew',
    'acc x skew',
    'acc y skew',
    'acc z skew',
]

new_df = pd.DataFrame(data=items, columns=columns)
new_df.to_csv(f'{name}.csv', index=False)
