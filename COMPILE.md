

### Compile custom LLVM using:

```
cmake --build . -j8
```


../build/bin/clang++ -O3 -march=native -ffast-math -Rpass=energy-loop-vectorize -Rpass-missed=energy-loop-vectorize -Rpass-analysis=energy-loop-vectorize vectorize_exmp.cpp -o vectorize_energy