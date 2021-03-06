# bfcc

`bfcc` is a very simple and naive compiler from BrainFuck to Linux x64 assembly.

### Usage

`bfcc [in] [out]` where,

- `[in]` is the BrainFuck source to be read (requires the `.bf` extension)
- `[out]` is the file to write the assembly to (requires the `.s` extension, defaults to `out.s`)

The `.s` file emitted by `bfcc` is essentially a C program as it uses functions like `malloc`, `memset`, `free`, `putchar` and `getchar` and has a `main` function. Thus, the resulting assembly needs to be compiled and linked with the CRT, which can be done using a compiler like `gcc` (i.e. `gcc out.s`).

`bfcc` allocates 30k bytes for the array, and there is no bounds checking. There is also no checking for cell overflow/underflow.

### Building

```shell
mkdir build
cd build
cmake ../
make
```