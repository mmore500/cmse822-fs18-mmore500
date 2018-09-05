# prompt

Can you come up with at least two reasons why using the `j`-index as the inner loop (for C) possibly improves performance?

# response

1. You use all the contents of the cacheline, avoiding wasted use of cache bandwidth.

2. You are using a nice memory sequence, so processor can make some guesses and perhaps pre-fetch data for you.