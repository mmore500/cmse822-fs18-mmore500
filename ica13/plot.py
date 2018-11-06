import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("data.csv",)

df['Runtime (seconds)'] = df['time']
df['Thread Count'] = df['T']

# categorical variables
palette = sns.color_palette("mako_r", 3)

ax = sns.lineplot(x='Thread Count',y='Runtime (seconds)',hue='N',data=df,palette=palette)

ax.set(xscale="log",yscale="log")

plt.savefig('results.png')
