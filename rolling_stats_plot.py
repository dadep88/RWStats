import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":

    df = pd.read_csv('cmake-build-release/output.csv', names = ['t', 'y', 'mean'], delimiter=';')
    plt.plot(df.t, df.y, color = 'grey')
    plt.plot(df.t, df['mean'], color='black')

    plt.show()

