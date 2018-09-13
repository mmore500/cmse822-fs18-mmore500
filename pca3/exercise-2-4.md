# prompt

Consider the case of summing 8 elements with 4 processors.
Show that some of the edges in the graph of figure 2.3 no longer correspond to actual communications.
Now consider summing 16 elements with, again, 4 processors.
What is the number of communication edges this time?

# response

```
PROC1   PROC2   PROC3   PROC4
-----   -----   -----   -----
1 + 2 + 3 + 4 + 5 + 6 + 7 + 8
|___|   |___|   |___|   |___|
3       7       11      15
|_______|        |______|
10               26
|________________|
36
```

Now, the diagonal lines from 2 to 3, from 4 to 7, from 6 to 11 and from 8 to 15 all occur on the same processor so they aren't communication lines

```
    PROC1           PROC2           PROC3           PROC4
-------------   -------------   -------------   -------------
1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10+ 11+ 12+ 13+ 14+ 15+ 16
|___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|
3       7       11      15      19      23      27      31
|_______|        |______|       |_______|        |______|
10               26             42               58
|________________|              |________________|
36                              100
|_______________________________|
136
```

Now, there are only 3 communication lines.
