# Prompt

What is the total time for a broadcast involving `p` processes?
Give `\alpha` and `\beta` terms separately, where
* `\alpha` is latency,
* `\beta` is the time-per-byte (inverse of bandwidth), and
* `n` is the number of bytes sent.

# Response

We can model latency as a function of `p`, `f(p)`, because, due to spatial constraints, the more processors you have the further apart they are so the longer the "ping" time will be.
If the processors are linearly connected, we might have `f(p) \propto p`.

```
\alpha = f(p) \approx a \times p
```
where `a` is a constant.

Assuming that the processors are all connected with equivalent bandwidth "pipes", the bandwidth should be constant.
```
\beta = c
```
where `c` is a constant

Putting this together,
```
broadcast total time = p \times (\alpha + \beta \times n)
  = p \times (a \times p + c \times n)
```
