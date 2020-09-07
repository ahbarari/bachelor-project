
test_df = pd.read_csv('test/right up up left left down down right.csv')
max_time = test_df['milisecond'].max()
print(max_time)

test_gyroscope_df = test_df.loc[test_df['ACC_or_GYR'] == 'GYR'].reset_index(drop=True)
test_accumulator_df = test_df.loc[test_df['ACC_or_GYR'] == 'ACC'].reset_index(drop=True)

# plt.plot(test_gyroscope_df['x'])
# plt.show()

start_frame = 0
finish_frame = 2000

frames = []
temp = []

while True:
    if start_frame + 2000 > max_time:
        break
    elif finish_frame - start_frame <= 3000:
        temp_df = test_df.loc[(test_df['milisecond'] >= start_frame) & (test_df['milisecond'] <= finish_frame)]

        test_gyroscope_df = temp_df.loc[temp_df['ACC_or_GYR'] == 'GYR'].reset_index(drop=True)
        test_accumulator_df = temp_df.loc[temp_df['ACC_or_GYR'] == 'ACC'].reset_index(drop=True)

        # normalized gyro
        gyro_max = test_gyroscope_df[['x', 'y', 'z']].max()
        df_max = gyro_max.max()
        test_gyroscope_df = test_gyroscope_df[['x', 'y', 'z']] / df_max

        # normalized acc
        acc_max = test_accumulator_df[['x', 'y', 'z']].max()
        df_max = acc_max.max()
        test_accumulator_df = test_accumulator_df[['x', 'y', 'z']] / df_max

        mean = test_gyroscope_df['x'].mean()
        sum_value = test_gyroscope_df['x'].sum()
        variance = test_gyroscope_df['x'].var()
        std = test_gyroscope_df['x'].std()
        median = test_gyroscope_df['x'].median()
        temp.append({
            'start': start_frame,
            'frame': finish_frame,
            'mean': abs(mean),
            'sum': abs(sum_value),
            'variance': variance,
            'std': std,
            'median': median,
        })
        # plt.plot(test_gyroscope_df['x'])
        # print('min: ', min)
        # print('max: ', max)
        # print('mean: ', mean)
        # print('sum: ', sum)
        # print('----------------------')
        # plt.show()
        finish_frame += 50
    else:
        counter = 0
        best = 0
        min_mean = temp[0]['mean']
        for data in temp:
            if data['mean'] < min_mean:
                min_mean = data['mean']
                best = counter
            counter += 1
        # print(temp)
        frames.append(temp[best]['frame'] - temp[best]['start'])
        start_frame = temp[best]['frame'] + 260
        finish_frame = temp[best]['frame'] + 2000
        temp = []

print(frames)
# frames = [2600, 2500, 2600, 2900, 3000, 2600, 3000, 3000]
start = 0
for frame in frames:
    temp_df = test_df.loc[(test_df['milisecond'] >= start) & (test_df['milisecond'] <= start + frame)]

    test_gyroscope_df = temp_df.loc[temp_df['ACC_or_GYR'] == 'GYR'].reset_index(drop=True)
    test_accumulator_df = temp_df.loc[temp_df['ACC_or_GYR'] == 'ACC'].reset_index(drop=True)

    # normalized gyro
    gyro_max = test_gyroscope_df[['x', 'y', 'z']].max()
    df_max = gyro_max.max()
    test_gyroscope_df = test_gyroscope_df[['x', 'y', 'z']] / df_max

    # normalized acc
    acc_max = test_accumulator_df[['x', 'y', 'z']].max()
    df_max = acc_max.max()
    test_accumulator_df = test_accumulator_df[['x', 'y', 'z']] / df_max

    # plt.plot(test_gyroscope_df['x'])
    # plt.show()

    gyro_x_mean = test_gyroscope_df['x'].mean()
    gyro_y_mean = test_gyroscope_df['y'].mean()
    gyro_z_mean = test_gyroscope_df['z'].mean()
    acc_x_mean = test_accumulator_df['x'].mean()
    acc_y_mean = test_accumulator_df['y'].mean()
    acc_z_mean = test_accumulator_df['z'].mean()
    gyro_x_median = test_gyroscope_df['x'].median()
    gyro_y_median = test_gyroscope_df['y'].median()
    gyro_z_median = test_gyroscope_df['z'].median()
    acc_x_median = test_accumulator_df['x'].median()
    acc_y_median = test_accumulator_df['y'].median()
    acc_z_median = test_accumulator_df['z'].median()
    gyro_x_std = test_gyroscope_df['x'].std()
    gyro_y_std = test_gyroscope_df['y'].std()
    gyro_z_std = test_gyroscope_df['z'].std()
    acc_x_std = test_accumulator_df['x'].std()
    acc_y_std = test_accumulator_df['y'].std()
    acc_z_std = test_accumulator_df['z'].std()
    gyro_x_var = test_gyroscope_df['x'].var()
    gyro_y_var = test_gyroscope_df['y'].var()
    gyro_z_var = test_gyroscope_df['z'].var()
    acc_x_var = test_accumulator_df['x'].var()
    acc_y_var = test_accumulator_df['y'].var()
    acc_z_var = test_accumulator_df['z'].var()
    gyro_x_min = test_gyroscope_df['x'].min()
    gyro_y_min = test_gyroscope_df['y'].min()
    gyro_z_min = test_gyroscope_df['z'].min()
    acc_x_min = test_accumulator_df['x'].min()
    acc_y_min = test_accumulator_df['y'].min()
    acc_z_min = test_accumulator_df['z'].min()
    gyro_x_max = test_gyroscope_df['x'].max()
    gyro_y_max = test_gyroscope_df['y'].max()
    gyro_z_max = test_gyroscope_df['z'].max()
    acc_x_max = test_accumulator_df['x'].max()
    acc_y_max = test_accumulator_df['y'].max()
    acc_z_max = test_accumulator_df['z'].max()
    gyro_x_25 = test_gyroscope_df['x'].quantile(0.25)
    gyro_y_25 = test_gyroscope_df['y'].quantile(0.25)
    gyro_z_25 = test_gyroscope_df['z'].quantile(0.25)
    acc_x_25 = test_accumulator_df['x'].quantile(0.25)
    acc_y_25 = test_accumulator_df['y'].quantile(0.25)
    acc_z_25 = test_accumulator_df['z'].quantile(0.25)
    gyro_x_75 = test_gyroscope_df['x'].quantile(0.75)
    gyro_y_75 = test_gyroscope_df['y'].quantile(0.75)
    gyro_z_75 = test_gyroscope_df['z'].quantile(0.75)
    acc_x_75 = test_accumulator_df['x'].quantile(0.75)
    acc_y_75 = test_accumulator_df['y'].quantile(0.75)
    acc_z_75 = test_accumulator_df['z'].quantile(0.75)

    item = [
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
        acc_z_75
    ]

    columns = [
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
        '75 acc z'
    ]

    new_df = pd.DataFrame([item], columns=columns)
    predicted = clf_svm.predict(new_df)
    predicted_precent = clf_svm.predict_proba(new_df)[0]
    print(predicted)
    print(clf_svm.classes_)
    print(predicted_precent)
    start += frame
