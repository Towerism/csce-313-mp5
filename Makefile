.PHONY: all compile symlinks rmbin rmsymlinksclean

.DEFAULT: all
all: compile symlinks
	@echo -e "Done."

###
### compiling recipes
###
compile:
	@mkdir -p bin && cd bin && cmake ../ && make


###
### symlink recipes
###
symlinks: mp4 test_suite data_server
	@echo -e "Making Symlinks..."

mp4: compile
	@ln -sf bin/mp4 mp4

test_suite: compile
	@ln -sf bin/test_suite test_suite

data_server: compile
	@ln -sf bin/data_server data_server


###
### cleaning recipes
###
rmbin:
	@echo -e "Removing Binaries..."
	@rm bin -rf

rmsymlinks:
	@echo -e "Removing Symlinks..."
	@find -type l -delete

clean: rmbin rmsymlinks
