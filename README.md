# dSFMT and ranlux APIs

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.581067.svg)](https://doi.org/10.5281/zenodo.581067)

This repo contains an API to ease the interaction with `ranlux` and
`dSFMT`, which are libraries for pseudo-random numbers generation.

There also are some examples and benchmarks.

## Info

Compile with

```.bash
./complile.sh
```

Content:

* `api-ov`: it shows how to use the APIs. Run with `run-ov.sh`
* `api-ov-bis`: it shows how to use the APIs separating the allocation from the generation. Run with `run-ov-bis.sh`
* `bench-ram`: monitors the permormance of `ranlux` and `dSFMT` by generating a large random array. Run with `run-ram.sh`
* `bench-disk`: similar to `random-test-ram`, but uses smaller arrays and saves them to the disk. Run with `run-disk.sh`
* `bench-disk-repeat`: repeats the test a certain number of times. Run with `run-disk-repeat.sh`.
* `bench-ram-repeat`: repeats the test a certain number of times. Run with `bench-ram-repeat.sh`.

## References

Libraries source code can be found

* `ranlux`: http://luscher.web.cern.ch/luscher/ranlux/
* `dSFMT` : http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/

Compiling dSFMT

inspired by http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/howto-compile.html


## Disclaimer

I do not own the copyright of `ranlux` and `dSFMT`. I included their
source code here accordingly to their license.
I only wrote the `*-api` libraries and the examples, which are distributed with GPLv3.
I included everything in a single repo to have a solid base to include
in my projects that require solid PRNGs.
