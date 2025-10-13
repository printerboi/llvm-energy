
LIBSODIUM_INCLUDES=-Isrc/libsodium/src/libsodium/include/sodium -Isrc/libsodium/src/libsodium/include

build-sql:
	../build/bin/clang -O0 -Xclang -disable-O0-optnone -emit-llvm -S src/sqlite/sqlite3.c -o src/.build/sqlite/sqlite3.ll
	../build/bin/clang -O0 -Xclang -disable-O0-optnone -emit-llvm -S src/sqlite/shell.c -o src/.build/sqlite/shell.ll
	../build/bin/llvm-link src/.build/sqlite/sqlite3.ll src/.build/sqlite/shell.ll -o src/.build/sqlite/sqlite.bc

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

build-lz4:
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/lib/lz4.c         -o src/.build/lz4/lz4.ll
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/lib/lz4hc.c       -o src/.build/lz4/lz4hc.ll
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/lib/lz4frame.c    -o src/.build/lz4/lz4frame.ll
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/lib/xxhash.c      -o src/.build/lz4/xxhash.ll
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/programs/lz4io.c      -o src/.build/lz4/lz4io.ll
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/programs/bench.c      -o src/.build/lz4/bench.ll
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/programs/lz4cli.c     -o src/.build/lz4/lz4cli.ll
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/programs/timefn.c     -o src/.build/lz4/timefn.ll
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/programs/threadpool.c -o src/.build/lz4/threadpool.ll
	../build/bin/clang -O0 -fPIC -I src/lz4/lib -Xclang -disable-O0-optnone -emit-llvm -S src/lz4/programs/lorem.c      -o src/.build/lz4/lorem.ll
	../build/bin/llvm-link src/.build/lz4/*.ll -o src/.build/lz4/lz4.bc

build-lua:
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lapi.c      -o src/.build/lua/lapi.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lauxlib.c   -o src/.build/lua/lauxlib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lbaselib.c  -o src/.build/lua/lbaselib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lcode.c     -o src/.build/lua/lcode.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lcorolib.c  -o src/.build/lua/lcorolib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lctype.c    -o src/.build/lua/lctype.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/ldblib.c    -o src/.build/lua/ldblib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/ldebug.c    -o src/.build/lua/ldebug.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/ldo.c       -o src/.build/lua/ldo.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/ldump.c     -o src/.build/lua/ldump.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lfunc.c     -o src/.build/lua/lfunc.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lgc.c       -o src/.build/lua/lgc.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/linit.c     -o src/.build/lua/linit.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/liolib.c    -o src/.build/lua/liolib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/llex.c      -o src/.build/lua/llex.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lmathlib.c  -o src/.build/lua/lmathlib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lmem.c      -o src/.build/lua/lmem.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/loadlib.c   -o src/.build/lua/loadlib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lobject.c   -o src/.build/lua/lobject.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lopcodes.c  -o src/.build/lua/lopcodes.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/loslib.c    -o src/.build/lua/loslib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lparser.c   -o src/.build/lua/lparser.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lstate.c    -o src/.build/lua/lstate.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lstring.c   -o src/.build/lua/lstring.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lstrlib.c   -o src/.build/lua/lstrlib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/ltable.c    -o src/.build/lua/ltable.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/ltablib.c   -o src/.build/lua/ltablib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/ltm.c       -o src/.build/lua/ltm.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lua.c      -o src/.build/lua/lua.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lundump.c   -o src/.build/lua/lundump.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lutf8lib.c  -o src/.build/lua/lutf8lib.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lvm.c      -o src/.build/lua/lvm.ll
	../build/bin/clang -O0 -g -fPIC -I src/lua/src -Xclang -disable-O0-optnone -emit-llvm -S src/lua/src/lzio.c     -o src/.build/lua/lzio.ll

	../build/bin/llvm-link src/.build/lua/*.ll -o src/.build/lua/lua.bc
