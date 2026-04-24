COMPFLAGS = -Wall -Wpedantic -Winline -Wextra -Wno-unknown-pragmas -Wno-long-long

# Directories
TESTDIR = tests
LIBDIR = libs
DISTDIR = dist
SRCDIR = src
EXAMPLEDIR = examples

# Source and Header files
SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(TESTDIR)/*.c) $(wildcard $(EXAMPLEDIR)/*.c)
HDRS = $(wildcard $(SRCDIR)/*.h)

# Clang-tidy configuration
CLANG_TIDY_CHECKS =
CLANG_TIDY_FLAGS = -I$(SRCDIR)

# Default target
all: libraries examples test

# --- Library Compilation Targets ---

# Rule to compile all libraries
libraries: string bitarray fileutils linkedlist doublylinkedlist graph queue stack permutations arena hash logger bloom set

# Individual library targets (compiling .c files into .o objects in LIBDIR)
string:
	$(CC) $(STD) -c $(SRCDIR)/stringlib.c -o $(LIBDIR)/string-lib.o $(CCFLAGS) $(COMPFLAGS)

bitarray:
	$(CC) $(STD) -c $(SRCDIR)/bitarray.c -o $(LIBDIR)/bitarray-lib.o $(CCFLAGS) $(COMPFLAGS)

fileutils:
	$(CC) $(STD) -c $(SRCDIR)/fileutils.c -o $(LIBDIR)/fileutils-lib.o $(CCFLAGS) $(COMPFLAGS)

linkedlist:
	$(CC) $(STD) -c $(SRCDIR)/llist.c -o $(LIBDIR)/llist-lib.o $(CCFLAGS) $(COMPFLAGS)

doublylinkedlist:
	$(CC) $(STD) -c $(SRCDIR)/dllist.c -o $(LIBDIR)/dllist-lib.o $(CCFLAGS) $(COMPFLAGS)

stack:
	$(CC) $(STD) -c $(SRCDIR)/stack.c -o $(LIBDIR)/stack-lib.o $(CCFLAGS) $(COMPFLAGS)

queue:
	$(CC) $(STD) -c $(SRCDIR)/queue.c -o $(LIBDIR)/queue-lib.o $(CCFLAGS) $(COMPFLAGS)

graph:
	$(CC) $(STD) -c $(SRCDIR)/graph.c -o $(LIBDIR)/graph-lib.o $(CCFLAGS) $(COMPFLAGS)

permutations:
	$(CC) $(STD) -c $(SRCDIR)/permutations.c -o $(LIBDIR)/permutations-lib.o $(CCFLAGS) $(COMPFLAGS)

arena:
	$(CC) $(STD) -c $(SRCDIR)/arena.c -o $(LIBDIR)/arena-lib.o $(CCFLAGS) $(COMPFLAGS)

hash:
	$(CC) $(STD) -c $(SRCDIR)/hash.c -o $(LIBDIR)/hash-lib.o $(CCFLAGS) $(COMPFLAGS)

logger:
	$(CC) $(STD) -c $(SRCDIR)/logger.c -o $(LIBDIR)/logger-lib.o $(CCFLAGS) $(COMPFLAGS)

bloom:
	$(CC) $(STD) -c $(SRCDIR)/bloom.c -o $(LIBDIR)/bloom-lib.o $(CCFLAGS) $(COMPFLAGS)

set:
	$(CC) $(STD) -c $(SRCDIR)/set.c -o $(LIBDIR)/set-lib.o $(CCFLAGS) $(COMPFLAGS)

# --- Build Variants ---

debug: CCFLAGS += -g
debug: all

openmp: CCFLAGS += -fopenmp
openmp: all

# --- Test Compilation Target ---
# Compiles test executables in DISTDIR
test: libraries
	$(CC) $(STD) $(LIBDIR)/string-lib.o $(TESTDIR)/stringlib_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/strlib
	$(CC) $(STD) $(TESTDIR)/timing_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/timing
	$(CC) $(STD) $(TESTDIR)/minunit_test.c $(CCFLAGS) $(COMPFLAGS) -lm -o $(CURDIR)/$(DISTDIR)/minunit
	$(CC) $(STD) $(LIBDIR)/bitarray-lib.o $(TESTDIR)/bitarray_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/bitarray
	$(CC) $(STD) $(LIBDIR)/fileutils-lib.o $(TESTDIR)/fileutils_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/fileutils
	$(CC) $(STD) $(LIBDIR)/llist-lib.o $(TESTDIR)/linked_list_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/linkedlist
	$(CC) $(STD) $(LIBDIR)/dllist-lib.o $(TESTDIR)/doubly_linked_list_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/doublelinkedlist
	$(CC) $(STD) $(LIBDIR)/queue-lib.o $(TESTDIR)/queue_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/queue
	$(CC) $(STD) $(LIBDIR)/stack-lib.o $(TESTDIR)/stack_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/stack
	$(CC) $(STD) $(LIBDIR)/graph-lib.o $(TESTDIR)/graph_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/graph
	$(CC) $(STD) $(LIBDIR)/permutations-lib.o $(TESTDIR)/permutations_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/permutations
	$(CC) $(STD) $(LIBDIR)/bloom-lib.o $(TESTDIR)/bloom_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/bloom -lm
	$(CC) $(STD) $(LIBDIR)/bloom-lib.o $(TESTDIR)/bloom_multi_thread.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/bloom_mt -lm
	$(CC) $(STD) $(LIBDIR)/hash-lib.o $(TESTDIR)/hash_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/hash
	$(CC) $(STD) $(LIBDIR)/hash-lib.o $(TESTDIR)/hash_update_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/hash_update
	$(CC) $(STD) $(LIBDIR)/set-lib.o $(TESTDIR)/set_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/set

# --- Example Compilation Target ---
# Compiles example executables in DISTDIR
examples: libraries
	$(CC) $(STD) $(LIBDIR)/string-lib.o $(EXAMPLEDIR)/stringlib_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_stringlib
	$(CC) $(STD) $(LIBDIR)/bitarray-lib.o $(EXAMPLEDIR)/bitarray_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_bitarray
	$(CC) $(STD) $(LIBDIR)/fileutils-lib.o $(EXAMPLEDIR)/fileutils_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_fileutils
	$(CC) $(STD) $(LIBDIR)/llist-lib.o $(EXAMPLEDIR)/linkedlist_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_linkedlist
	$(CC) $(STD) $(LIBDIR)/dllist-lib.o $(EXAMPLEDIR)/doublylinkedlist_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_doublylinkedlist
	$(CC) $(STD) $(LIBDIR)/queue-lib.o $(EXAMPLEDIR)/queue_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_queue
	$(CC) $(STD) $(LIBDIR)/stack-lib.o $(EXAMPLEDIR)/stack_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_stack
	$(CC) $(STD) $(LIBDIR)/graph-lib.o $(EXAMPLEDIR)/graph_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_graph
	$(CC) $(STD) $(LIBDIR)/permutations-lib.o $(EXAMPLEDIR)/permutations_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_permutations
	$(CC) $(STD) $(LIBDIR)/arena-lib.o $(LIBDIR)/hash-lib.o $(LIBDIR)/logger-lib.o $(EXAMPLEDIR)/arena_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_arena
	$(CC) $(STD) $(LIBDIR)/hash-lib.o $(LIBDIR)/set-lib.o $(EXAMPLEDIR)/hash_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_hash
	$(CC) $(STD) $(LIBDIR)/set-lib.o $(EXAMPLEDIR)/set_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_set
	$(CC) $(STD) $(LIBDIR)/logger-lib.o $(EXAMPLEDIR)/logger_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_logger
	$(CC) $(STD) $(LIBDIR)/bloom-lib.o $(EXAMPLEDIR)/bloom_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_bloom -lm
	$(CC) $(STD) $(EXAMPLEDIR)/timing_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_timing -lm # Note: timing.h is likely a header-only or has a separate compilation unit not listed. Assuming direct inclusion for example.
	$(CC) $(STD) $(EXAMPLEDIR)/vec_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_vec

# --- Run Tests Target ---
# Executes the compiled test executables
runtests:
	@ echo "Running tests..."
	@ if [ -f "$(CURDIR)/$(DISTDIR)/strlib" ]; then echo "--- Running strlib test ---" && $(CURDIR)/$(DISTDIR)/strlib; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/timing" ]; then echo "--- Running timing test ---" && $(CURDIR)/$(DISTDIR)/timing; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/minunit" ]; then echo "--- Running minunit test ---" && $(CURDIR)/$(DISTDIR)/minunit; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/bitarray" ]; then echo "--- Running bitarray test ---" && $(CURDIR)/$(DISTDIR)/bitarray; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/fileutils" ]; then echo "--- Running fileutils test ---" && $(CURDIR)/$(DISTDIR)/fileutils; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/linkedlist" ]; then echo "--- Running linkedlist test ---" && $(CURDIR)/$(DISTDIR)/linkedlist; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/doublelinkedlist" ]; then echo "--- Running doublelinkedlist test ---" && $(CURDIR)/$(DISTDIR)/doublelinkedlist; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/queue" ]; then echo "--- Running queue test ---" && $(CURDIR)/$(DISTDIR)/queue; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/stack" ]; then echo "--- Running stack test ---" && $(CURDIR)/$(DISTDIR)/stack; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/graph" ]; then echo "--- Running graph test ---" && $(CURDIR)/$(DISTDIR)/graph; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/permutations" ]; then echo "--- Running permutations test ---" && $(CURDIR)/$(DISTDIR)/permutations; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/bloom" ]; then echo "--- Running bloom test ---" && $(CURDIR)/$(DISTDIR)/bloom; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/bloom_mt" ]; then echo "--- Running bloom_mt test ---" && $(CURDIR)/$(DISTDIR)/bloom_mt; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/hash" ]; then echo "--- Running hash test ---" && $(CURDIR)/$(DISTDIR)/hash; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/hash_update" ]; then echo "--- Running hash_update test ---" && $(CURDIR)/$(DISTDIR)/hash_update; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/set" ]; then echo "--- Running set test ---" && $(CURDIR)/$(DISTDIR)/set; fi
	@ echo "Tests finished."

# --- Windows-specific targets ---
# These use -D_WIN32 and .exe extension for executables.
windows: CCFLAGS += -D_WIN32
windows: LIBEXT = .exe
windows: windows-libraries windows-test windows-examples

windows-libraries:
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/stringlib.c -o $(LIBDIR)/string-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/bitarray.c -o $(LIBDIR)/bitarray-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/fileutils.c -o $(LIBDIR)/fileutils-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/llist.c -o $(LIBDIR)/llist-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/dllist.c -o $(LIBDIR)/dllist-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/graph.c -o $(LIBDIR)/graph-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/queue.c -o $(LIBDIR)/queue-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/stack.c -o $(LIBDIR)/stack-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/permutations.c -o $(LIBDIR)/permutations-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/arena.c -o $(LIBDIR)/arena-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/hash.c -o $(LIBDIR)/hash-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/logger.c -o $(LIBDIR)/logger-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/bloom.c -o $(LIBDIR)/bloom-lib.o $(CCFLAGS) $(COMPFLAGS)
	$(CC) $(STD) -D_WIN32 -c $(SRCDIR)/set.c -o $(LIBDIR)/set-lib.o $(CCFLAGS) $(COMPFLAGS)

windows-test: windows-libraries
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/string-lib.o $(TESTDIR)/stringlib_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/strlib.exe
	$(CC) $(STD) -D_WIN32 $(TESTDIR)/timing_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/timing.exe
	$(CC) $(STD) -D_WIN32 $(TESTDIR)/minunit_test.c $(CCFLAGS) $(COMPFLAGS) -lm -o $(CURDIR)/$(DISTDIR)/minunit.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/bitarray-lib.o $(TESTDIR)/bitarray_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/bitarray.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/fileutils-lib.o $(TESTDIR)/fileutils_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/fileutils.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/llist-lib.o $(TESTDIR)/linked_list_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/linkedlist.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/dllist-lib.o $(TESTDIR)/doubly_linked_list_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/doublelinkedlist.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/queue-lib.o $(TESTDIR)/queue_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/queue.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/stack-lib.o $(TESTDIR)/stack_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/stack.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/graph-lib.o $(TESTDIR)/graph_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/graph.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/permutations-lib.o $(TESTDIR)/permutations_test.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/permutations.exe
	# Add Windows tests for new modules if they exist in tests/ dir

windows-examples: windows-libraries
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/string-lib.o $(EXAMPLEDIR)/stringlib_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_stringlib.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/bitarray-lib.o $(EXAMPLEDIR)/bitarray_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_bitarray.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/fileutils-lib.o $(EXAMPLEDIR)/fileutils_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_fileutils.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/llist-lib.o $(EXAMPLEDIR)/linkedlist_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_linkedlist.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/dllist-lib.o $(EXAMPLEDIR)/doublylinkedlist_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_doublylinkedlist.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/queue-lib.o $(EXAMPLEDIR)/queue_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_queue.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/stack-lib.o $(EXAMPLEDIR)/stack_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_stack.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/graph-lib.o $(EXAMPLEDIR)/graph_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_graph.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/permutations-lib.o $(EXAMPLEDIR)/permutations_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_permutations.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/arena-lib.o $(LIBDIR)/hash-lib.o $(LIBDIR)/logger-lib.o $(EXAMPLEDIR)/arena_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_arena.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/hash-lib.o $(LIBDIR)/set-lib.o $(EXAMPLEDIR)/hash_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_hash.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/set-lib.o $(EXAMPLEDIR)/set_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_set.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/logger-lib.o $(EXAMPLEDIR)/logger_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_logger.exe
	$(CC) $(STD) -D_WIN32 $(LIBDIR)/bloom-lib.o $(EXAMPLEDIR)/bloom_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_bloom.exe
	$(CC) $(STD) -D_WIN32 $(EXAMPLEDIR)/timing_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_timing.exe # Note: timing.h is likely a header-only or has a separate compilation unit not listed. Assuming direct inclusion for example.
	$(CC) $(STD) -D_WIN32 $(EXAMPLEDIR)/vec_example.c $(CCFLAGS) $(COMPFLAGS) -o $(CURDIR)/$(DISTDIR)/ex_vec.exe

windows-runtests:
	@ echo "Running Windows tests..."
	@ if [ -f "$(CURDIR)/$(DISTDIR)/fileutils.exe" ]; then $(CURDIR)/$(DISTDIR)/fileutils.exe; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/bitarray.exe" ]; then $(CURDIR)/$(DISTDIR)/bitarray.exe; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/strlib.exe" ]; then $(CURDIR)/$(DISTDIR)/strlib.exe; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/timing.exe" ]; then $(CURDIR)/$(DISTDIR)/timing.exe; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/linkedlist.exe" ]; then $(CURDIR)/$(DISTDIR)/linkedlist.exe; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/doublelinkedlist.exe" ]; then $(CURDIR)/$(DISTDIR)/doublelinkedlist.exe; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/queue.exe" ]; then $(CURDIR)/$(DISTDIR)/queue.exe; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/stack.exe" ]; then $(CURDIR)/$(DISTDIR)/stack.exe; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/graph.exe" ]; then $(CURDIR)/$(DISTDIR)/graph.exe; fi
	@ if [ -f "$(CURDIR)/$(DISTDIR)/permutations.exe" ]; then $(CURDIR)/$(DISTDIR)/permutations.exe; fi
	@ echo "Windows tests finished."

# --- Clean Target ---
# Removes generated files
clean:
	@ echo "Cleaning build artifacts..."
	# Remove all files in DISTDIR and LIBDIR
	@ if [ -d "$(CURDIR)/$(DISTDIR)/" ]; then rm -f $(CURDIR)/$(DISTDIR)/*; fi
	@ if [ -d "$(CURDIR)/$(LIBDIR)/" ]; then rm -f $(CURDIR)/$(LIBDIR)/*; fi
	@ echo "Clean complete."

# --- Format files ---
# Ensures all files are formatted accordingly
format:
	clang-format -i $(SRCS) $(HDRS)
	mbake format --config ./.bake.toml Makefile

lint:
	clang-tidy $(CLANG_TIDY_CHECKS) $(SRCS) -- $(CLANG_TIDY_FLAGS)
	mbake validate --config ./.bake.toml Makefile

fix:
	clang-tidy --fix $(CLANG_TIDY_CHECKS) $(SRCS) -- $(CLANG_TIDY_FLAGS)

.PHONY: all libraries string bitarray fileutils linkedlist doublylinkedlist stack queue graph permutations arena hash logger bloom set debug openmp test examples runtests windows windows-libraries windows-test windows-examples windows-runtests clean format lint fix
