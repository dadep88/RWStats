import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":

    df = pd.read_csv('cmake-build-release/output.csv', names = ['t', 'y', 'rolling_mean', 'rolling_std_dev'], delimiter=';')
    fig, ax = plt.subplots(2,1, sharex=True)
    ax[0].plot(df.t, df.y, color = 'grey')
    ax[0].plot(df.t, df.rolling_mean, color='black')
    ax[1].plot(df.t, df.rolling_std_dev, color= 'black')

    plt.show()

