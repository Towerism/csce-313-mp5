.PHONY: mp4 test generate mp4 test clean

default: mp4
all: default test

generate:
	cd bin && cmake ../
mp4:
	cd bin && $(MAKE) -s mp4 && mv bin/mp4 ../
test:
	cd bin && $(MAKE) -s bin test_suite && mv test/test_suite ../
clean:
	cd bin && $(MAKE) -s clean
