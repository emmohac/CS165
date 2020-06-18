import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

input_type = sys.argv[1]
data_frame_merge = pd.read_csv(f'{input_type}_timing/{input_type}_merge.csv', sep=',')
data_frame_merge["time"] = data_frame_merge["time"].apply(lambda r: r/1000)

data_frame_insertion = pd.read_csv(f'{input_type}_timing/{input_type}_insertion.csv', sep=',')
data_frame_insertion["time"] = data_frame_insertion["time"].apply(lambda r: r/1000)

merge_time = data_frame_merge["time"]
merge_size = data_frame_merge["size"]
m1, b1 = np.polyfit(np.log2(np.array(merge_size)), np.log2(np.array(merge_time)), 1)

insertion_time = data_frame_insertion["time"]
insertion_size = data_frame_insertion["size"]
m2, b2 = np.polyfit(np.log2(np.array(insertion_size)), np.log2(np.array(insertion_time)), 1)

test_array = [2**i for i in range(10, 21)]

plt.loglog(np.array(merge_size), merge_time, 'o', basex=2, basey=2, label=f'merge_sort ~ {m1}logN + {b1}', color="red")
plt.loglog(np.array(merge_size), 2 ** (m1 * np.log2(np.array(merge_size)) + b1), basex=2, basey=2, color='red')
plt.loglog(insertion_size, insertion_time, 'o', basex=2, basey=2, label=f'insertion_sort ~ {m2}logN + {b2}', color="blue")
plt.loglog(np.array(insertion_size), 2 ** (m2 * np.log2(np.array(insertion_size)) + b2), basex=2, basey=2, color='blue')

plt.xlabel("logN (size)")
plt.ylabel("logT(N) (seconds)")
plt.title("Reversed Sorted Permutation")

plt.xticks(test_array)

plt.legend(loc=0, prop={'size': 10})
plt.show()



