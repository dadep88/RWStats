import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":

    df = pd.read_csv('cmake-build-release/output.csv', names = ['t', 'y'], delimiter=';')
    plt.plot(df.t, df.y)

    plt.show()

