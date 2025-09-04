

### Compile custom LLVM using:

```
cmake --build . -j8
```


../build/bin/clang++ -O3 -march=native -ffast-math -Rpass=energy-loop-vectorize -Rpass-missed=energy-loop-vectorize -Rpass-analysis=energy-loop-vectorize vectorize_exmp.cpp -o vectorize_energy


../build/bin/clang++ -mllvm -enable-energy-aware -O3 -march=native -ffast-math -Rpass=energy-loop-vectorize -Rpass-missed=energy-loop-vectorize -Rpass-analysis=energy-loop-vectorize  vectorize_exmp.cpp -o vectorize_energy



### working

../build/bin/clang++ -S -emit-llvm -O1 -fno-unroll-loops -g vectorize_exmp.cpp -o vectorize.ll

../build/bin/opt -ffast-math  -passes='function(sroa,early-cse,loop-simplify,lcssa,loop-rotate,loop-mssa(licm),indvars),energy-loop-vectorize,function(loop-simplify,lcssa)'  -enable-energy-aware   vectorize.ll -o output_energy.ll

../build/bin/opt -ffast-math  -passes='function(sroa,early-cse,loop-simplify,lcssa,loop-rotate,loop-mssa(licm),indvars),energy-loop-vectorize,function(loop-simplify,lcssa)'  -enable-energy-aware   vectorize.ll -o output.ll
