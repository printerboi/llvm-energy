
# Code to optimize sqlit3 for demo purposes

sqlite: create-folder-sql optimize-energy-sql optimize-default-sql default-to-binary-sql energy-to-binary-sql

create-folder-sql:
	@mkdir -p sqlite

optimize-energy-sql:
	../../../build/bin/opt -passes="inline,instcombine" -instcombine-energy-aware -S ../../src/.build/sqlite/sqlite.bc -o sqlite/opt_energy.ll

optimize-default-sql:
	../../../build/bin/opt -passes="inline,instcombine" -S ../../src/.build/sqlite/sqlite.bc -o sqlite/opt_default.ll


default-to-binary-sql:
	../../../build/bin/llvm-as sqlite/opt_default.ll -o sqlite/default.bc
	../../../build/bin/llc -O0 -filetype=obj sqlite/default.bc -o sqlite/default.o
	../../../build/bin/clang++ -O0 -no-pie sqlite/default.o -o sqlite/default

energy-to-binary-sql:
	../../../build/bin/llvm-as sqlite/opt_energy.ll -o sqlite/energy.bc
	../../../build/bin/llc -O0 -filetype=obj sqlite/energy.bc -o sqlite/energy.o
	../../../build/bin/clang++ -O0 -no-pie sqlite/energy.o -o sqlite/energy


# Code to optimize zlib program for demo purposes

zlib: create-folder-zlib optimize-energy-zlib optimize-default-zlib default-to-binary-zlib energy-to-binary-zlib testprog-zlib

create-folder-zlib:
	@mkdir -p zlib

optimize-energy-zlib:
	../../../build/bin/opt -passes="inline,instcombine" -instcombine-energy-aware -S ../../src/.build/zlib/zlib.bc -o zlib/opt_energy.ll

optimize-default-zlib:
	../../../build/bin/opt -passes="inline,instcombine" -S ../../src/.build/zlib/zlib.bc -o zlib/opt_default.ll

default-to-binary-zlib:
	../../../build/bin/llvm-as zlib/opt_default.ll -o zlib/default.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj zlib/default.bc -o zlib/default.o
	../../../build/bin/clang -O0 -shared -fPIC zlib/default.o -o zlib/default.so

energy-to-binary-zlib:
	../../../build/bin/llvm-as zlib/opt_energy.ll -o zlib/energy.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj zlib/energy.bc -o zlib/energy.o
	../../../build/bin/clang -O0 -shared -fPIC zlib/energy.o -o zlib/energy.so

testprog-zlib:
	../../../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S test/zlib.c -o zlib/testprog.ll
	../../../build/bin/llvm-as zlib/testprog.ll -o zlib/testprog.bc
	../../../build/bin/opt -S zlib/testprog.bc -o zlib/testprog_energy.ll
	../../../build/bin/opt -S zlib/testprog.bc -o zlib/testprog_default.ll
	../../../build/bin/llvm-as zlib/testprog_energy.ll -o zlib/testprog_energy.bc
	../../../build/bin/llvm-as zlib/testprog_default.ll -o zlib/testprog_default.bc
	../../../build/bin/llc -O0 -filetype=obj zlib/testprog_energy.bc -o zlib/testprog_energy.o
	../../../build/bin/llc -O0 -filetype=obj zlib/testprog_default.bc -o zlib/testprog_default.o
	export LD_LIBRARY_PATH=/home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib:$LD_LIBRARY_PATH
	../../../build/bin/clang -O0 -no-pie zlib/testprog_energy.o -I../../src/zlib /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib/energy.so -o zlib/testprog_energy
	../../../build/bin/clang -O0 -no-pie zlib/testprog_default.o -I../../src/zlib /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib/default.so -o zlib/testprog_default


# Code to optimize libsodium program for demo purposes

libsodium: create-folder-libsodium optimize-energy-libsodium optimize-default-libsodium default-to-binary-libsodium energy-to-binary-libsodium testprog-libsodium

create-folder-libsodium:
	@mkdir -p libsodium

optimize-energy-libsodium:
	../../../build/bin/opt -passes="inline,instcombine" -instcombine-energy-aware -S ../../src/.build/libsodium/libsodium.bc -o libsodium/opt_energy.ll

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
