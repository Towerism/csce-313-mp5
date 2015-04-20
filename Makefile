.PHONY: all test compile generate symlinks clean-bin clean-symlinks clean


.DEFAULT: all
all: compile symlinks
	@echo "Done."


###
### testing recipes
###
test: all
	@./test_suite


###
### compiling recipes
###
compile: generate
	@make -C bin
generate:
	@mkdir -p bin && cd bin && cmake ..


###
### symlink recipes
###
symlinks: mp4 test_suite data_server
	@echo "Making Symlinks..."
mp4: data_server
	@ln -sf bin/mp4 mp4
test_suite: compile
	@ln -sf bin/test_suite test_suite
data_server: compile
	@ln -sf bin/data_server data_server


###
### cleaning recipes
###
clean-bin:
	@echo "Removing Binaries..."
	@rm -rf bin
clean-symlinks:
	@echo "Removing Symlinks..."
	@find -type l -delete
clean: clean-bin clean-symlinks
