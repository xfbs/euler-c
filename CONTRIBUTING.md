# Contributing

Do you want to run the solutions to check if they work, or improve them?
Improvements to the code are welcome, also feel free to fork this project to
find your own solutions, you may reuse any part of this project.

## Getting started

The base dependencies of this project are just a few:

  - make, `GNU make 3.81` compatible
  - ruby `2.3` or later
  - bcrypt ruby gem, version `3.1` or later

Since there are quite a number of programming languages involved in this
project, this project depends on a lot of other compilers and interpreters.
However, these are optional as you can just not run the solutions for languages
for which you haven't installed the tooling.

  - python `3.6` or later
  - crystal `0.24.1` or later
  - clang or gcc implementing `c99`
  - clang++ or g++ implementing `c++17`
  - rust `1.19.0` with cargo

```bash
gem install bcrypt
```

### On macOS

Use homebrew to install all the essentials, and then use rubygems to install the
ruby dependency:

```bash
$ brew install ruby python3 crystal-lang rust
$ gem install bcrypt
```

### On Ubuntu

*TODO*, check `.travis.yml` for how I set up the ubuntu CI machines.

### Caveat

On macOS, at least on 10.11 El Capitan, the version of `clang++` that is shipped
by Apple does not fully support `c++17`. There are two ways of mitigating that:
You can install a newer version by running this:

```bash
$ brew install llvm --with-toolchain
```

However, this may take quite a while. The faster option is to download the
pre-built library from [the LLVM releases
website](http://releases.llvm.org/download.html), extract that somewhere, and to
then put something like

```
export CXX="/path/to/prebuilt/llvm/bin/clang++"
```

In your `.bashrc` or `.zshrc` so that `make` knows which compiler to use. This
method should also work for Linux and Windows systems (although I haven't
tested).

## Run Solutions

The [`Makefile`](Makefile) in the project root, in conjunction with the 
[`euler.rb`](euler.rb) script, offer some ways of running the solutions and
showing some statistics. To build, test, verify and time all solutions (this
could take a while), run:

```bash
make check
```

If you want to see how many problems are solved in a more concise manner, run:

```bash
make overview
```

Read the source code of the [`Makefile`](Makefile) for more details.

## Structure

The structure of the project is as follows:
  - [`Makefile`](Makefile), to build, clean, test and verify all solutions.
  - [`euler.rb`](euler.rb), a helper script to check solutions
  - [`src/`](src/), a folder with all the solutions, named as such:
      - [`001-multiples-of-3-and-5/`](src/001-multiples-of-3-and-5), an example 
        of a problem folder
          - [`problem.md`](src/001-multiples-of-3-and-5/problem.md), the
            explanation of the problem
          - [`ruby/`](src/001-multiples-of-3-and-5/ruby/), a ruby implementation
            of the solution
              - [`Makefile`](src/001-multiples-of-3-and-5/ruby/Makefile), the
                Makefile to build, test, run and clean the ruby solution
              - `...` ruby code and files
          - [`rust/`](src/001-multiples-of-3-and-5/rust), a rust implementation of the solution
              - [`Makefile`](src/001-multiples-of-3-and-5/rust/Makefile), the
                Makefile to build, test, run and clean the rust solution
              - `...` rust code and files
          - [`.solution.bcrypt`](src/001-multiples-of-3-and-5/.solution.bcrypt),
            a [bcrypt](https://en.wikipedia.org/wiki/Bcrypt)ed hash of the
            solution
      - `...` other problems
  - [`lib/`](lib/) — libraries and data shared between solutions
  - [`doc/`](doc/) — folder where, at some point, documentation for my solutions
    can be found or generated.

Every solution needs to contain a
[`Makefile`](src/001-multiples-of-3-and-5/ruby/Makefile) that responds to four
commands:
  - `make build` — to build the solution
  - `make solve` — to solve the problem, which should return the solution on
    `stdout` (and no other text)
  - `make test` — to build and run the unit test suite, returning nonzero on
    failure
  - `make clean` — to clean intermediate files, build targets and caches

Some solutions may have a `DISABLED` file inside their folder. This tells my
euler.rb script to ignore them, which usually means that the solution doesn't
work or is too slow, but I have committed it anyways because I feel that I get
get it to work or optimize it.

### Coding Styles

*TODO*
