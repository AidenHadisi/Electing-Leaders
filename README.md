# Electing Leaders

## Electing leaders in a ring topology

This algorithm selects two leaders, called president and vice-president, using ring topology. The president is the largest odd value and the vice-president is the largest even value.

## Concurrency

The two election run concurrently.

## Compile

```bash
mpic++ election.cpp
```

## Run

```bash
mpirun --oversubscribe -n 10 ./a.out
```
