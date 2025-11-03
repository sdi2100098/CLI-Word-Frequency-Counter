# CLI-Word-Frequency-Counter
![example workflow](https://github.com/sdi2100098/CLI-Word-Frequency-Counter/actions/workflows/build.yml/badge.svg)

A small command-line tool that counts word frequencies from an input text file and writes the top N words to an output file.

**Features**
- Read words from an input file, remove punctuation, and normalize to lowercase.
- Count frequencies using an associative container.
- Sort results and write top `N` words to an output file.
- Prevents accidental appending to an existing output file by requiring a new filename.
- Unit tests, Makefile, and GitHub Actions (CI) included.

**Optimizations**
- We first stored the pairs of strings-frequency using an std::map but changed it to std::unordered map due to faster lookup times( In general O(1) )
- See all related info on total run time in Benchmark/Times.txt


# build with Makefile
Run <make help> to see commands on how to build the executable and run the code