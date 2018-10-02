# Review

irregular data exchange
* don't impose an order on data exchanges
* number of sends and receives in a processor sometimes don't match
* "these are expected incoming messages" without waiting for them in sequence

non-blocking communication downsides
* you have to maintain multiple send/receive buffers (can't immediately de-allocate)
* have to keep track of which messages have actually gone through yourself, might end up with A LOT of buffers

non-blocking communication upsides
* you can do useful work while communication is moving
* overlapping computation and communication aka latency hiding

`MPI_Wiat` wat for a single request

`MPI_Waitall` wait for a number of requests and does not matter in what sequence they are satisfied

`MPI_Waitany` take action as each request is satisfied

feed `MPI_Status` objects into these

message probing: accept a message, but do not copy data; used to allocate a buffer that fits the received data
* can have race condition in multithreaded environment; `MPI_Mprobe` gets around this

can use wildcards to allow flexibility in receiving message source, tag, and count (i.e., data size)

synchronous communication if coordination going on with the other (like blocking)

asynchronous if not (like non-blocking)

persistent communication
* for communication that is repeated many times
* don't have to alllocate/deallocate `MPI_Request` parameters

buffers
* allocate your own buffer space
  * replacement for buffer space inside MPI library
  * have to manually detach
* use `MPI_Bsend`
* can use for persistent communication

# Questions
* Why would you want to manage buffering yourself? This seems like a lot of programmer work. What scenario makes this worthwhile for performance?
* I don't quite understand the figure in 4.4.3. It appears that time progesses along the x axis, but what do the colors of the rectangles and their positions on the y axis mean?
