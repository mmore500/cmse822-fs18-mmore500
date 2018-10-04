# Review

## Datatypes

* built-in fundamental datatypes
  * for single values or contiguous sets of values
* custom datatypes: take non-contiguous/complicated and make it simple

* contiguous type
* vector type
  * regularly spaced chunks of data 
* indexed type
  * irregularly spaced chunks of data
* struct type
  * bind together contiguous chunks of different kinds of data
  * you have to do lots of work under the hood
  
packaging: sending one part through the tube at a time

## Communicators
* for specifying between which processes a communication goes
* you get MPI_COMM_WORLD, a null communicator, and a own-process communicator for free
* can make communicators as subsets of available processes
* useful for when all processes don't work together equally (i.e., sets working together on subsets of the problem)
* also useful: making a copy of a communicator to prevent accidental collision between user messaging and library messaging when developing a library

## Proess Management
* for when you don't know the available nodes at compile time, you can dynamically spawn more processes
* MPI_UNIVERSE: all processes and spawned processes
* children can only communicate with parent at first
* you can even do multiple programs (i.e., spawn another executable)

# Questions

Why do you need to commit/free datatypes?
What's going oin under the hood?
Why, besides name conflicts, would you want to free datatypes?

When creating a communicator, what dos process colour (pg 147) mean?
How do you define it?

What is the distinction between indexed and h-indexed?
