.DEFAULT_GOAL := build
.PHONY: build all clean compile-all run test
build all clean compile-all:
	$(MAKE) -C src $@
run: build
	./src/course1.out
test:
	python3 tests/verify.py
%:
	$(MAKE) -C src $@
