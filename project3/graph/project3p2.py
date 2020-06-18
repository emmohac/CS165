import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("data/er.csv")
diameter = df["diameter"]
size = df["size"]

m, b = np.polyfit(np.array(size), np.array(diameter),1)
#plt.loglog(np.array(size), diameter, 'yo', basex=2, alpha=0.6, label=f'ER diameter ~ {m}logN + {b}', color='red')
plt.semilogx(np.array(size), np.array(diameter), 'yo', basex=2, alpha=0.6, label=f'ER diameter ~ {m}logN + {b}', color='red')
#plt.loglog(np.array(size), 2 ** (m * np.log2(np.array(size)) + b), basex=2, basey=2, color='blue')
#plt.loglog(np.log2(np.array(size)), 2 ** (m * np.log2(np.array(size)) + b), basex=2, color='blue')

test_array = [2**i for i in range(3, 18)]
#plt.scatter(np.log2(np.array(size)), np.array(diameter), color="blue")
a = [2**i for i in range(3,18)]
#plt.xticks(a)
#plt.semilogy((np.array(size)), np.array(diameter), color='blue')
plt.show()
print("Done")