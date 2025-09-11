
build:
	../../build/bin/clang++ -O0 -Xclang -disable-O0-optnone -emit-llvm -S example.cpp -o default.ll

build-sql:
	../../build/bin/clang -O0 -Xclang -disable-O0-optnone -emit-llvm -S sqlite3.c -o sqlite3.ll
	../../build/bin/clang -O0 -Xclang -disable-O0-optnone -emit-llvm -S shell.c -o shell.ll
	../../build/bin/llvm-link sqlite3.ll shell.ll -o default.bc

optimize-energy:
	../../build/bin/opt -passes="instcombine" -instcombine-energy-aware -S default.bc -o opt_energy.ll

optimize-default:
	../../build/bin/opt -passes="instcombine" -S default.bc -o opt_default.ll

default-to-binary:
	../../build/bin/llvm-as opt_default.ll -o default.bc
	../../build/bin/llc -filetype=obj default.bc -o default.o
	../../build/bin/clang++ -O0 -no-pie default.o -o default


energy-to-binary:
	../../build/bin/llvm-as opt_energy.ll -o energy.bc
	../../build/bin/llc -filetype=obj energy.bc -o energy.o
	../../build/bin/clang++ -O0 -no-pie energy.o -o energy