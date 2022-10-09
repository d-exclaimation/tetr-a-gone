# Tetragone (Test)

Testing directory for the program
> **PLEASE DON'T MARK THIS DIRECTORY :), THESE ARE JUST FOR TESTING PURPOSES**

## Running test

### Run the phony target for test
```sh
make test
```

## Outputs

1. Each individual test result:
    - `OK`: Test passed
    - `FAIL`: Test failed, but continue
    - `FATAL`: Test failed and stop
2. The amount of tests passed from the total amount of tests given

### Example

```sh
Running test:

[TEST]: Running "Test #0" ....OK
[TEST]: Running "Test #1" ....OK
[TEST]: Running "Test #2" ....FAIL
[TEST]: Running "Test #3" ....OK

Success: 3/4
```

## Limitation

- Test runs under `gcc` not `avr-gcc` (No clue on how to show the tests result under `avr-gcc` and the fun kit)
- Passing tests might not immediately translate to a working program
- Tests mostly check for logical errors 
