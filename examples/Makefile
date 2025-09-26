
LIBSODIUM_INCLUDES=-Isrc/libsodium/src/libsodium/include/sodium -Isrc/libsodium/src/libsodium/include

build-sql:
	../build/bin/clang -O0 -Xclang -disable-O0-optnone -emit-llvm -S src/sqlite/sqlite3.c -o src/.build/sqlite/sqlite3.ll
	../build/bin/clang -O0 -Xclang -disable-O0-optnone -emit-llvm -S src/sqlite/shell.c -o src/.build/sqlite/shell.ll
	../build/bin/llvm-link src/.build/sqlite/sqlite3.ll src/.build/sqlite/shell.ll -o src/.build/sqlite/default.bc

build-zlib:
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/adler32.c  -o src/.build/zlib/adler32.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/crc32.c    -o src/.build/zlib/crc32.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/deflate.c  -o src/.build/zlib/deflate.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/infback.c  -o src/.build/zlib/infback.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/inffast.c  -o src/.build/zlib/inffast.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/inflate.c  -o src/.build/zlib/inflate.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/inftrees.c -o src/.build/zlib/inftrees.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/trees.c    -o src/.build/zlib/trees.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/zutil.c    -o src/.build/zlib/zutil.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/compress.c -o src/.build/zlib/compress.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/uncompr.c  -o src/.build/zlib/uncompr.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/gzclose.c  -o src/.build/zlib/gzclose.ll
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/gzlib.c -o src/.build/zlib/gzlib.ll -DHAVE_UNISTD_H -D_LARGEFILE64_SOURCE=1 -D_FILE_OFFSET_BITS=64
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/gzread.c -o src/.build/zlib/gzread.ll -DHAVE_UNISTD_H -D_LARGEFILE64_SOURCE=1 -D_FILE_OFFSET_BITS=64
	../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S src/zlib/gzwrite.c  -o src/.build/zlib/gzwrite.ll -DHAVE_UNISTD_H -D_LARGEFILE64_SOURCE=1 -D_FILE_OFFSET_BITS=64

	../build/bin/llvm-link src/.build/zlib/*.ll -o src/.build/zlib/zlib.bc

build-libsodium:
	find src/libsodium -name '*.c' -not -path '*/test/*' | while read file; do \
		out=src/.build/libsodium/$$(basename $$file .c).ll; \
		../build/bin/clang -O0 -fPIC -Xclang -disable-O0-optnone -emit-llvm -S $$file $(LIBSODIUM_INCLUDES) -o $$out; \
	done
	../build/bin/llvm-link src/.build/libsodium/*.ll -o src/.build/libsodium/libsodium.bc
