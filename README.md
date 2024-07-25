# Storr

The Storr programming language

Named after Gottlieb Conrad Christian Storr; a German physician, chemist, and
naturalist.
Storr is a taxonomic authority of 6 genera: Mellivora, Nasua, Phalanger,
Procavia, Procyon, and Tarsius.
The logo is a tree of the taxonomic ranks of these taxa.

Storr is a statically-typed, functional, general purpose programming language.
Typing is inferred and the language is designed to be simple and expressive.
The syntax is inspired by Python, Haskell, and Rust.

[//]: # (## Installation)

[//]: # ()
[//]: # (```bash)

[//]: # ($ git clone https://github.com/storr-lang/storr.git)

[//]: # ($ cd storr)

[//]: # ($ make)

[//]: # ($ sudo make install)

[//]: # (```)

[//]: # (## Usage)

[//]: # ()
[//]: # (In `fib.storr`:)

[//]: # ()
[//]: # (```storr)

[//]: # (from storr/io import println)

[//]: # (from storr/list import map)

[//]: # ()
[//]: # ()
[//]: # (main = map&#40;[0 .. 11], println . fib&#41;)

[//]: # ()
[//]: # ()
[//]: # (/// Returns the nth element of the Fibonacci sequence.)

[//]: # (/// Returns `0` if `n < 0`.)

[//]: # (///)

[//]: # (fib&#40;n : Int&#41; : Int = _fib&#40;n, 0, 0, 1&#41;)

[//]: # (_fib&#40;n : Int, i : Int, a : Int, b : Int&#41; : Int = match i < n {)

[//]: # (    True , _fib&#40;n, i + 1, b, a + b&#41;)

[//]: # (    _    , a)

[//]: # (})

[//]: # (```)

[//]: # ()
[//]: # (```bash)

[//]: # ($ storr run fib.storr)

[//]: # (0)

[//]: # (1)

[//]: # (1)

[//]: # (2)

[//]: # (3)

[//]: # (5)

[//]: # (8)

[//]: # (13)

[//]: # (21)

[//]: # (34)

[//]: # (55)

[//]: # (89)

[//]: # (```)

## Support

For bug reports and feature requests for the language, please open a new issue
[here](./issues/new/choose).
