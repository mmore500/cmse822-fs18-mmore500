*oops! checked for a pca, but pulled from master not from upstream!*

# Review

topologies: schemes to connect the processors in a parallel machine

ethernet
* doesn't scale up
* all machines on a network are on a single cable

fully connected
* each processor has one wire for the comunications with each other processor
* as more processors added, the network interface gets more and more wires
* cost of machine increases faster than linearly with the number of processors

## Graph Theory

degree of a node in a graph: the number of other nodes it is connected to

diameter of the graph: the maximum shortest distance between any two nodes

more links = smaller chance of congestion/contention

bisection width: the minimum number of linkx that have to be removed to partition the graph into two unconnected graphs
* how many messages can, guaranteed, be under way simultaneously in a parallel computer
* decreases congestion, increases redundancy (e.g., reliability under faults)

bisection bandwidth: the bandwidth across the bisection width
* product of bisection width and capacity of connections
* more realistic than aggregate bandwidth

## Busses

everyone on the same bus: limited scalability
* only one processor at a time can access
* can maybe overcome by cache coherence/snooping

## Linear arrays and rings

yup, it's a ring

## 2D and 3D arrays

aka cartesian mesh

wraparound connections aka torus

grids of higher dimensionality are possible

## Hypercubes

number via `d` bits, each processor connected to all other that have an address that differs by exactly one bit

advantage: small diameter and large capacity for traffic through the network

disadvantage: processor design is dependent on the total machine size
* also, can only extend a given machine by doubling it

can embed lower dimensional meshes in a hypercube

## Switched networks

each switch has a limited inbound/outbound elements, but through multiple switches you can connect any two processors by a path thru the network

crossbar: a grid, where processors are the sides and intersections are switches
* number of switches scales as `n^2`, though

butterfly: hierarchical-ish (but without high vs low level asymmetries), `log(n)` jumps

fat tree: hierarchical, with higher bandwidth at the root
* can build from simple elements, looks like  butterfly network


## examples

stampede: fat tree

bluegene: torus-based cluster

## bandwidth and latency

* as before
* number of hops is usually small, so can be neglected

## locality
* between cores, private cache
* between cores, shared cache
* between sockets
* through network structure

# Your Questions

1. Define _bisection width_.

bisection width: the number of connections you have to clip to break a graph into two identical sub-graphs

2. Define the _diameter_ of a network.

diameter: the maximum number of hops to get from one node to another

3. Do a little internet searching and determine what type of network MSU's HPCC utilizes.

The HPCC uses *Infiniband*.
The text seems to imply that *Infiniband* relies on fat tree principles.

However, according to Wikipedia the *Infiniband* uses "switched fabric topology" which, according to [this blog post](https://etherealmind.com/what-is-the-definition-of-switch-fabric/) is along the lines of a crossbar switch.

# My Questions

To what extent are "flagship" supercomputers funded/constructed for a single application versus less specialized, (i.e., funded/constructed via a consortium for use by researchers from many domains)?
Realistically, to what extent would domain specialization/generality be reflected in the topology of a supercomputer?
