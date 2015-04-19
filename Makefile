.PHONY: all compile generate symlinks clean-bin clean-symlinks clean


.DEFAULT: all
all: compile symlinks
	@echo -e "Done."


###
### compiling recipes
###
compile: generate
	@make -C bin
generate:
	@mkdir -p bin && cd bin && cmake ../


###
### symlink recipes
###
symlinks: mp4 test_suite data_server
	@echo -e "Making Symlinks..."
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
	@echo -e "Removing Binaries..."
	@rm bin -rf
clean-symlinks:
	@echo -e "Removing Symlinks..."
	@find -type l -delete
clean: clean-bin clean-symlinks
