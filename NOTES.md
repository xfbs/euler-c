# ToDo

## Problems

  - [ ] problem 26 still needs to be solved in C and rust
  - [ ] problems 37 and 41 still need to be solved in ruby
  - [ ] a lot of problems need to be solved in python
  - [ ] a lot of problems need to be optimised
  - [ ] problem `022` and `042` share code (`weight()` function), export?
  - [ ] change implementation of euler/prime.h and other prime generators to use
        a prime sieve internally to generates the primes faster.

## General

  - [ ] install and run `pfff` as static code analyzer
  - [ ] add `make fmt` targets to makefiles
  - [ ] run formatters over all of the code
  - [ ] run valgrind on the solutions to catch memory allocation bugs
  - [ ] problem 049, change algorithm to be more efficient
  - [ ] remove `euler/bitvec.h` dependencies in C solutions if not necessary
  - [ ] comment and clean up all solutions
  - [ ] implement tests for all problems
  - [ ] improve execution speed on some ruby/python solutions
  - [ ] change from `python3` to `pypy3` for a little speed boost
      - probably not a good idea, stock python3 should do us okay
  - [ ] add `sieve.h` from problem `010/c`
  - [ ] problems 30 and 34 are quite similar, export library code?
  - [ ] don't symlink for shared code, make libraries own their code
  - [ ] consider porting to `premake` to allow for IDE compatibility?
  - [ ] solve all problems up to problem 100
  - [ ] add solutions in another language (scheme, ocaml, cpp)
  - [ ] port all of crystal solution's minitest to specs (because builtin)

## Project

  - [ ] come up with a mechanism to record performance data
  - [ ] restructute files. into: `lib/` (shared libraries),
        `src/c/`, `src/ruby`, etc. (one folder per language) for solutions,
        `doc/problems/000-problem-name.md` for each problem, have a dedicated
        checker with built-in solutions to check the answers.
