import matplotlib
matplotlib.use('Agg')

import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv')

df = df[df['divvy']==1]

df['nrounds'] = df['rounds'].apply(lambda x: str(x)+" rounds")

df['nproc'] = df['n']

print(df)

ax = sns.lineplot(x='nproc',y='walltime',hue='nrounds',data=df)

ax.set(xscale="log",yscale="log")

plt.savefig('results.png')
