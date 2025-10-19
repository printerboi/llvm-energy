
# Code to optimize sqlit3 for demo purposes

sqlite: create-folder-sql optimize-energy-sql optimize-default-sql default-to-binary-sql energy-to-binary-sql

create-folder-sql:
	@mkdir -p sqlite

optimize-energy-sql:
	../../../build/bin/opt -passes="inline,instcombine" -instcombine-energy-aware -inline-energy-aware -S ../../src/.build/sqlite/sqlite.bc -o sqlite/opt_energy.ll

optimize-default-sql:
	../../../build/bin/opt -passes="inline,instcombine" -S ../../src/.build/sqlite/sqlite.bc -o sqlite/opt_default.ll

optimize-o1-eng-sql:
	../../../build/bin/opt -passes="default<O1>" -instcombine-energy-aware -inline-energy-aware -S ../../src/.build/sqlite/sqlite.bc -o sqlite/opt_o1_eng.ll

optimize-o1-sql:
	../../../build/bin/opt -passes="default<O1>" -S ../../src/.build/sqlite/sqlite.bc -o sqlite/opt_o1.ll

default-to-binary-sql:
	../../../build/bin/llvm-as sqlite/opt_default.ll -o sqlite/default.bc
	../../../build/bin/llc -O0 -filetype=obj sqlite/default.bc -o sqlite/default.o
	../../../build/bin/clang++ -O0 -no-pie sqlite/default.o -o sqlite/default

energy-to-binary-sql:
	../../../build/bin/llvm-as sqlite/opt_energy.ll -o sqlite/energy.bc
	../../../build/bin/llc -O0 -filetype=obj sqlite/energy.bc -o sqlite/energy.o
	../../../build/bin/clang++ -O0 -no-pie sqlite/energy.o -o sqlite/energy


o1-to-binary-sql:
	../../../build/bin/llvm-as sqlite/opt_o1.ll -o sqlite/o1.bc
	../../../build/bin/llc -O0 -filetype=obj sqlite/o1.bc -o sqlite/o1.o
	../../../build/bin/clang++ -O0 -no-pie sqlite/o1.o -o sqlite/o1

o1-eng-to-binary-sql:
	../../../build/bin/llvm-as sqlite/opt_o1_eng.ll -o sqlite/o1_eng.bc
	../../../build/bin/llc -O0 -filetype=obj sqlite/o1_eng.bc -o sqlite/o1_eng.o
	../../../build/bin/clang++ -O0 -no-pie sqlite/o1_eng.o -o sqlite/o1_eng


# Code to optimize zlib program for demo purposes

zlib: create-folder-zlib optimize-energy-zlib optimize-default-zlib default-to-binary-zlib energy-to-binary-zlib testprog-zlib

create-folder-zlib:
	@mkdir -p zlib

optimize-energy-zlib:
	../../../build/bin/opt -passes="inline,instcombine" -instcombine-energy-aware -inline-energy-aware -S ../../src/.build/zlib/zlib.bc -o zlib/opt_energy.ll

optimize-default-zlib:
	../../../build/bin/opt -passes="inline,instcombine" -S ../../src/.build/zlib/zlib.bc -o zlib/opt_default.ll

optimize-o1-eng-zlib:
	../../../build/bin/opt -passes="default<O1>" -instcombine-energy-aware -inline-energy-aware -S ../../src/.build/zlib/zlib.bc -o zlib/opt_o1_eng.ll

optimize-o1-zlib:
	../../../build/bin/opt -passes="default<O1>" -S ../../src/.build/zlib/zlib.bc -o zlib/opt_o1.ll


default-to-binary-zlib:
	../../../build/bin/llvm-as zlib/opt_default.ll -o zlib/default.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj zlib/default.bc -o zlib/default.o
	../../../build/bin/clang -O0 -shared -fPIC zlib/default.o -o zlib/default.so

energy-to-binary-zlib:
	../../../build/bin/llvm-as zlib/opt_energy.ll -o zlib/energy.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj zlib/energy.bc -o zlib/energy.o
	../../../build/bin/clang -O0 -shared -fPIC zlib/energy.o -o zlib/energy.so

o1-to-binary-zlib:
	../../../build/bin/llvm-as zlib/opt_o1.ll -o zlib/o1.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj zlib/o1.bc -o zlib/o1.o
	../../../build/bin/clang++ -O0 -shared -fPIC zlib/o1.o -o zlib/o1.so

o1-eng-to-binary-zlib:
	../../../build/bin/llvm-as zlib/opt_o1_eng.ll -o zlib/o1_eng.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj zlib/o1_eng.bc -o zlib/o1_eng.o
	../../../build/bin/clang++ -O0 -shared -fPIC zlib/o1_eng.o -o zlib/o1_eng.so

testprog-zlib:
	../../../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S test/zlib.c -o zlib/testprog.ll
	../../../build/bin/llvm-as zlib/testprog.ll -o zlib/testprog.bc
	../../../build/bin/opt -S zlib/testprog.bc -o zlib/testprog_energy.ll
	../../../build/bin/opt -S zlib/testprog.bc -o zlib/testprog_default.ll
	../../../build/bin/opt -S zlib/testprog.bc -o zlib/o1_eng.ll
	../../../build/bin/opt -S zlib/testprog.bc -o zlib/o1.ll
	../../../build/bin/llvm-as zlib/testprog_energy.ll -o zlib/testprog_energy.bc
	../../../build/bin/llvm-as zlib/testprog_default.ll -o zlib/testprog_default.bc
	../../../build/bin/llvm-as zlib/o1_eng.ll -o zlib/testprog_o1_eng.bc
	../../../build/bin/llvm-as zlib/o1.ll -o zlib/testprog_o1.bc
	../../../build/bin/llc -O0 -filetype=obj zlib/testprog_energy.bc -o zlib/testprog_energy.o
	../../../build/bin/llc -O0 -filetype=obj zlib/testprog_default.bc -o zlib/testprog_default.o
	../../../build/bin/llc -O0 -filetype=obj zlib/testprog_o1_eng.bc -o zlib/testprog_o1_eng.o
	../../../build/bin/llc -O0 -filetype=obj zlib/testprog_o1.bc -o zlib/testprog_o1.o
	export LD_LIBRARY_PATH=/home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib:$LD_LIBRARY_PATH
	../../../build/bin/clang -O0 -no-pie zlib/testprog_energy.o -I../../src/zlib /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib/energy.so -o zlib/testprog_energy
	../../../build/bin/clang -O0 -no-pie zlib/testprog_default.o -I../../src/zlib /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib/default.so -o zlib/testprog_default
	../../../build/bin/clang -O0 -no-pie zlib/testprog_o1_eng.o -I../../src/zlib /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib/o1_eng.so -o zlib/testprog_o1_eng
	../../../build/bin/clang -O0 -no-pie zlib/testprog_o1.o -I../../src/zlib /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib/o1.so -o zlib/testprog_o1



# Code to optimize libsodium program for demo purposes

libsodium: create-folder-libsodium optimize-energy-libsodium optimize-default-libsodium default-to-binary-libsodium energy-to-binary-libsodium testprog-libsodium

create-folder-libsodium:
	@mkdir -p libsodium

optimize-energy-libsodium:
	../../../build/bin/opt -passes="inline,instcombine" -instcombine-energy-aware -inline-energy-aware -S ../../src/.build/libsodium/libsodium.bc -o libsodium/opt_energy.ll

optimize-default-libsodium:
	../../../build/bin/opt -passes="inline,instcombine" -S ../../src/.build/libsodium/libsodium.bc -o libsodium/opt_default.ll

default-to-binary-libsodium:
	../../../build/bin/llvm-as libsodium/opt_default.ll -o libsodium/default.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj libsodium/default.bc -o libsodium/default.o
	../../../build/bin/clang -O0 -shared -fPIC libsodium/default.o -o libsodium/default.so

energy-to-binary-libsodium:
	../../../build/bin/llvm-as libsodium/opt_energy.ll -o libsodium/energy.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj libsodium/energy.bc -o libsodium/energy.o
	../../../build/bin/clang -O0 -shared -fPIC libsodium/energy.o -o libsodium/energy.so

testprog-libsodium:
	export LD_LIBRARY_PATH=/home/max/Documents/repos/llvm-energy/examples/optimizations/combine/libsodium:$LD_LIBRARY_PATH
	../../../build/bin/clang -O0 test/libsodium.c -I../../src/libsodium/src/libsodium/include /home/max/Documents/repos/llvm-energy/examples/optimizations/combine/libsodium/energy.so -o libsodium/testprog_energy
	../../../build/bin/clang -O0 test/libsodium.c -I../../src/libsodium/src/libsodium/include /home/max/Documents/repos/llvm-energy/examples/optimizations/combine/libsodium/default.so -o libsodium/testprog_default


# Code to optimize lz4 program for demo purposes

lz4: create-folder-lz4 optimize-energy-lz4 optimize-default-lz4 default-to-binary-lz4 energy-to-binary-lz4

create-folder-lz4:
	@mkdir -p lz4

optimize-energy-lz4:
	../../../build/bin/opt -passes="inline,instcombine" -instcombine-energy-aware -inline-energy-aware -S ../../src/.build/lz4/lz4.bc -o lz4/opt_energy.ll

optimize-default-lz4:
	../../../build/bin/opt -passes="inline,instcombine" -S ../../src/.build/lz4/lz4.bc -o lz4/opt_default.ll

default-to-binary-lz4:
	../../../build/bin/llvm-as lz4/opt_default.ll -o lz4/default.bc
	../../../build/bin/llc -O0 -filetype=obj lz4/default.bc -o lz4/default.o
	../../../build/bin/clang++ -O0 -no-pie lz4/default.o -o lz4/default

energy-to-binary-lz4:
	../../../build/bin/llvm-as lz4/opt_energy.ll -o lz4/energy.bc
	../../../build/bin/llc -O0 -filetype=obj lz4/energy.bc -o lz4/energy.o
	../../../build/bin/clang++ -O0 -no-pie lz4/energy.o -o lz4/energy


zlib-cmp: create-folder-zlib-cmp optimize-energy-zlib-cmp optimize-default-zlib-cmp default-to-binary-zlib-cmp energy-to-binary-zlib-cmp testprog-zlib-cmp

create-folder-zlib-cmp:
	@mkdir -p zlib-cmp

optimize-energy-zlib-cmp:
	../../../build/bin/opt -passes="inline,instcombine" -instcombine-energy-aware -inline-energy-aware -S ../../src/.build/zlib-cmp/zlib.bc -o zlib-cmp/opt_energy.ll

optimize-default-zlib-cmp:
	../../../build/bin/opt -passes="inline,instcombine" -S ../../src/.build/zlib-cmp/zlib.bc -o zlib-cmp/opt_default.ll

default-to-binary-zlib-cmp:
	../../../build/bin/llvm-as zlib-cmp/opt_default.ll -o zlib-cmp/default.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj zlib-cmp/default.bc -o zlib-cmp/default.o
	../../../build/bin/clang -O0 -shared -fPIC zlib-cmp/default.o -o zlib-cmp/default.so

energy-to-binary-zlib-cmp:
	../../../build/bin/llvm-as zlib-cmp/opt_energy.ll -o zlib-cmp/energy.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj zlib-cmp/energy.bc -o zlib-cmp/energy.o
	../../../build/bin/clang -O0 -shared -fPIC zlib-cmp/energy.o -o zlib-cmp/energy.so

testprog-zlib-cmp:
	../../../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S test/zlib.c -o zlib-cmp/testprog.ll
	../../../build/bin/llvm-as zlib-cmp/testprog.ll -o zlib-cmp/testprog.bc
	../../../build/bin/opt -S zlib-cmp/testprog.bc -o zlib-cmp/testprog_energy.ll
	../../../build/bin/opt -S zlib-cmp/testprog.bc -o zlib-cmp/testprog_default.ll
	../../../build/bin/llvm-as zlib-cmp/testprog_energy.ll -o zlib-cmp/testprog_energy.bc
	../../../build/bin/llvm-as zlib-cmp/testprog_default.ll -o zlib-cmp/testprog_default.bc
	../../../build/bin/llc -O0 -filetype=obj zlib-cmp/testprog_energy.bc -o zlib-cmp/testprog_energy.o
	../../../build/bin/llc -O0 -filetype=obj zlib-cmp/testprog_default.bc -o zlib-cmp/testprog_default.o
	export LD_LIBRARY_PATH=/home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib-cmp:$LD_LIBRARY_PATH
	../../../build/bin/clang -O0 -no-pie zlib-cmp/testprog_energy.o -I../../src/zlib-cmp /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib-cmp/energy.so -o zlib-cmp/testprog_energy
	../../../build/bin/clang -O0 -no-pie zlib-cmp/testprog_default.o -I../../src/zlib-cmp /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib-cmp/default.so -o zlib-cmp/testprog_default

