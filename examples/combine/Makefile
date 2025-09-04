
build:
	../../build/bin/clang++ -O0 -Xclang -disable-O0-optnone  -emit-llvm -S example.cpp -o default.ll

optimize-energy:
	../../build/bin/opt -passes="instcombine" -instcombine-energy-aware  -S default.ll -o opt_energy.ll

optimize-default:
	../../build/bin/opt -passes="instcombine"  -S default.ll -o opt_default.ll