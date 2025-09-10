
build:
	../../build/bin/clang++ -O0 -Xclang -disable-O0-optnone  -emit-llvm -S example.cpp -o default.ll

optimize-energy:
	../../build/bin/opt -passes="instcombine" -instcombine-energy-aware  -S default.ll -o opt_energy.ll

optimize-default:
	../../build/bin/opt -passes="instcombine"  -S default.ll -o opt_default.ll

default-to-binary:
	../../build/bin/llvm-as opt_default.ll -o default.bc
	../../build/bin/llc -filetype=obj default.bc -o default.o
	../../build/bin/clang++ -O0 -no-pie default.o -o default


energy-to-binary:
	../../build/bin/llvm-as opt_energy.ll -o energy.bc
	../../build/bin/llc -filetype=obj energy.bc -o energy.o
	../../build/bin/clang++ -O0 -no-pie energy.o -o energy