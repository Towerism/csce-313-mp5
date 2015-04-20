.PHONY: all test compile generate \
	submodule-init submodule-update \
	symlinks clean-bin clean-symlinks \
	clean

BIN_DIR = bin
MAKE = make -C $(BIN_DIR)
CMAKE = @mkdir -p $(BIN_DIR) && cd $(BIN_DIR) && cmake

CLIENT = client
TEST_SUITE = test_suite
DATA_SERVER = data_server

.DEFAULT: all
all: compile symlinks
	@echo "-- Done"
all-test: compile-test symlinks-test
	@echo "-- Done"

###
### testing recipes
###
test: all-test
	@./test_suite


###
### compiling recipes
###
compile: submodules generate
	@$(MAKE)
compile-test: submodules generate-test
	@$(MAKE)
generate:
	@mkdir -p $(BIN_DIR) && cd $(BIN_DIR) && cmake ..
generate-test:
	@mkdir -p $(BIN_DIR) && cd $(BIN_DIR) && cmake -DTestSuite=ON ..

###
### submodule recipes
###
submodules: submodule-init submodule-update
submodule-init:
	@echo "-- Initializing submodules"
	@git submodule init > /dev/null
submodule-update:
	@echo "-- Updating submodules"
	@git submodule update > /dev/null


###
### symlink recipes
###
symlinks: client data_server
	@echo "-- Making Symlinks"
symlinks-test: client data_server test_suite
	@echo "-- Making Symlinks"
client: data_server
	@ln -sf $(BIN_DIR)/$(CLIENT) $(CLIENT)
test_suite: compile
	@ln -sf $(BIN_DIR)/$(TEST_SUITE) $(TEST_SUITE) 
data_server: compile
	@ln -sf $(BIN_DIR)/$(DATA_SERVER) $(DATA_SERVER) 


###
### cleaning recipes
###
clean-bin:
	@echo "-- Removing Binaries"
	@rm -rf $(BIN_DIR)
clean-symlinks:
	@echo "-- Removing Symlinks"
	@find -type l -delete
clean: clean-bin clean-symlinks
