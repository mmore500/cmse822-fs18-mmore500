import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
dfs = []

for config in ["blocking", "nonblocking"]:
    for node in ["1node", "2node"]:
        df = pd.read_csv("pingpong_"+config+"_"+node+".log")
        df['config'] = config
        df['node'] = node
        dfs.append(df)

df = pd.concat(dfs)

ax = sns.lineplot(x='m', y=' sec', hue='config', style='node', data=df)
ax.set_xscale("log")
ax.set_yscale("log")

plt.gcf().set_size_inches(12,9)
plt.savefig('log-log.png')
plt.clf()

ax = sns.lineplot(x='m', y=' sec', hue='config', style='node', data=df)

plt.gcf().set_size_inches(12,9)
plt.savefig('linear-linear.png')
