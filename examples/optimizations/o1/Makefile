
# Code to optimize sqlit3 for demo purposes

sqlite: create-folder-sql optimize-o1-eng-sql optimize-o1-sql o1-to-binary-sql o1-eng-to-binary-sql

create-folder-sql:
	@mkdir -p sqlite

optimize-o1-eng-sql:
	../../../build/bin/opt -passes="default<O1>" -instcombine-energy-aware -instsimplify-energy-aware -simplifycfg-energy-aware -S ../../src/.build/sqlite/sqlite.bc -o sqlite/opt_o1_eng.ll

optimize-o1-sql:
	../../../build/bin/opt -passes="default<O1>" -S ../../src/.build/sqlite/sqlite.bc -o sqlite/opt_o1.ll

o1-to-binary-sql:
	../../../build/bin/llvm-as sqlite/opt_o1.ll -o sqlite/o1.bc
	../../../build/bin/llc -O0 -filetype=obj sqlite/o1.bc -o sqlite/o1.o
	../../../build/bin/clang++ -O0 -no-pie sqlite/o1.o -o sqlite/o1

o1-eng-to-binary-sql:
	../../../build/bin/llvm-as sqlite/opt_o1_eng.ll -o sqlite/o1_eng.bc
	../../../build/bin/llc -O0 -filetype=obj sqlite/o1_eng.bc -o sqlite/o1_eng.o
	../../../build/bin/clang++ -O0 -no-pie sqlite/o1_eng.o -o sqlite/o1_eng


# Code to optimize zlib program for demo purposes

zlib: create-folder-zlib optimize-o1-eng-zlib optimize-o1-zlib o1-to-binary-zlib o1-eng-to-binary-zlib testprog-zlib

create-folder-zlib:
	@mkdir -p zlib

optimize-o1-eng-zlib:
	../../../build/bin/opt -passes="default<O1>" -instcombine-energy-aware -instsimplify-energy-aware -simplifycfg-energy-aware -S ../../src/.build/zlib/zlib.bc -o zlib/opt_o1_eng.ll

optimize-o1-zlib:
	../../../build/bin/opt -passes="default<O1>" -S ../../src/.build/zlib/zlib.bc -o zlib/opt_o1.ll


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
	../../../build/bin/opt -S zlib/testprog.bc -o zlib/o1_eng.ll
	../../../build/bin/opt -S zlib/testprog.bc -o zlib/o1.ll
	../../../build/bin/llvm-as zlib/o1_eng.ll -o zlib/testprog_o1_eng.bc
	../../../build/bin/llvm-as zlib/o1.ll -o zlib/testprog_o1.bc
	../../../build/bin/llc -O0 -filetype=obj zlib/testprog_o1_eng.bc -o zlib/testprog_o1_eng.o
	../../../build/bin/llc -O0 -filetype=obj zlib/testprog_o1.bc -o zlib/testprog_o1.o
	export LD_LIBRARY_PATH=/home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib:$LD_LIBRARY_PATH
	../../../build/bin/clang -O0 -no-pie zlib/testprog_o1_eng.o -I../../src/zlib /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib/o1_eng.so -o zlib/testprog_o1_eng
	../../../build/bin/clang -O0 -no-pie zlib/testprog_o1.o -I../../src/zlib /home/max/Documents/repos/llvm-energy/examples/optimizations/both/zlib/o1.so -o zlib/testprog_o1



# Code to optimize libsodium program for demo purposes

libsodium: create-folder-libsodium optimize-o1-eng-libsodium optimize-o1-libsodium o1-to-binary-libsodium o1-eng-to-binary-libsodium testprog-libsodium

create-folder-libsodium:
	@mkdir -p libsodium

optimize-o1-eng-libsodium:
	../../../build/bin/opt -passes="default<O1>" -instcombine-energy-aware -instsimplify-energy-aware -simplifycfg-energy-aware -S ../../src/.build/libsodium/libsodium.bc -o libsodium/opt_o1_eng.ll

optimize-o1-libsodium:
	../../../build/bin/opt -passes="default<O1>" -S ../../src/.build/libsodium/libsodium.bc -o libsodium/opt_o1.ll

o1-to-binary-libsodium:
	../../../build/bin/llvm-as libsodium/opt_o1.ll -o libsodium/default.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj libsodium/default.bc -o libsodium/default.o
	../../../build/bin/clang -O0 -shared -fPIC libsodium/default.o -o libsodium/default.so

o1-eng-to-binary-libsodium:
	../../../build/bin/llvm-as libsodium/opt_o1_eng.ll -o libsodium/energy.bc
	../../../build/bin/llc -O0 -relocation-model=pic -filetype=obj libsodium/energy.bc -o libsodium/energy.o
	../../../build/bin/clang -O0 -shared -fPIC libsodium/energy.o -o libsodium/energy.so

testprog-libsodium:
	export LD_LIBRARY_PATH=/home/max/Documents/repos/llvm-energy/examples/optimizations/combine/libsodium:$LD_LIBRARY_PATH
	../../../build/bin/clang -O0 test/libsodium.c -I../../src/libsodium/src/libsodium/include /home/max/Documents/repos/llvm-energy/examples/optimizations/combine/libsodium/energy.so -o libsodium/testprog_o1_eng
	../../../build/bin/clang -O0 test/libsodium.c -I../../src/libsodium/src/libsodium/include /home/max/Documents/repos/llvm-energy/examples/optimizations/combine/libsodium/default.so -o libsodium/testprog_o1


# Code to optimize lz4 program for demo purposes

lz4: create-folder-lz4 optimize-o1-eng-lz4 optimize-o1-lz4 o1-to-binary-lz4 o1-eng-to-binary-lz4

create-folder-lz4:
	@mkdir -p lz4

optimize-o1-eng-lz4:
	../../../build/bin/opt -passes="default<O1>" -instcombine-energy-aware -instsimplify-energy-aware -simplifycfg-energy-aware -S ../../src/.build/lz4/lz4.bc -o lz4/opt_o1_eng.ll

optimize-o1-lz4:
	../../../build/bin/opt -passes="default<O1>" -S ../../src/.build/lz4/lz4.bc -o lz4/opt_o1.ll

o1-to-binary-lz4:
	../../../build/bin/llvm-as lz4/opt_o1.ll -o lz4/default.bc
	../../../build/bin/llc -O0 -filetype=obj lz4/default.bc -o lz4/default.o
	../../../build/bin/clang++ -O0 -no-pie lz4/default.o -o lz4/o1

o1-eng-to-binary-lz4:
	../../../build/bin/llvm-as lz4/opt_o1_eng.ll -o lz4/energy.bc
	../../../build/bin/llc -O0 -filetype=obj lz4/energy.bc -o lz4/energy.o
	../../../build/bin/clang++ -O0 -no-pie lz4/energy.o -o lz4/o1_eng
