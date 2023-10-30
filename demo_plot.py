import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":

    df = pd.read_csv('cmake-build-release/output.csv', names = ['t', 'y', 'rolling_mean', 'rolling_std_dev'], delimiter=';')
    fig, ax = plt.subplots(2, 1, sharex=True)
    ax[0].plot(df.y, color='grey', label='data')
    ax[0].plot(df.rolling_mean, color='black', label='rolling mean')
    ax[0].grid(True)
    ax[0].legend(loc='lower right')
    ax[1].plot(df.rolling_std_dev, color='black', label='rolling std-dev')
    ax[1].grid(True)
    ax[1].legend(loc='lower right')
    ax[-1].set_xlabel('Samples #')
    ax[-1].set_xlim((0, df.shape[0]))


    plt.show()

