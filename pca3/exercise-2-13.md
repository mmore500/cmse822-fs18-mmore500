# prompt

We can formulate strong scaling as a runtime that is inversely proportional to the number of processors:

```
t = c/p.
```

Show that on a log-log plot, that is, you plot the logarithm of the runtime against the logarithm of the number of processors, you will get a straight line with slope -1.
Can you suggest a way of dealing with a non-parallelizable section, that is with a runtime `t = c_1 + c_2/p`?

# response

```
t = c/p
\log{t} = \log{c/p}
\log{t} = \log{c} - \log{p}
```

Compare to `y = mx+b` where
* `y -> \log{t}`,
* `b -> \log{c}`,
* `x -> \log{p}`, and
* `m ->  -1`.

QED.

I'm not sure exactly what the second part of the question is asking about.
What does "dealing with" mean?

If you plot this, `t` will converge to `c_1` as `p -> \infty`.
