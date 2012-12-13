CC		 = g++
CFLAGS	 = -Wall -I'/usr/include'
LDFLAGS  = -L'/usr/local/lib' -lm -lgflags -lprotobuf
PRG		 = software
SRC_DIR  = ./src
INC_DIR  = ./inc
OBJ_DIR	 = obj

SRC_FILES := $(shell ls $(SRC_DIR)/*.cpp;)
OBJ_FILES := ${SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o}

all: $(OBJ_DIR) $(OBJ_FILES)
	@$(CC) $(LDFLAGS) -o $(PRG) $(OBJ_FILES)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@$(CC) -I$(INC_DIR) -c $< $(CFLAGS) -o $@

gen:
	@protoc ./taskgraph.proto --cpp_out=.
	@mv taskgraph.pb.h inc/
	@mv taskgraph.pb.cc src/taskgraph.pb.cpp

clean:
	@rm -f $(PRG)
	@rm -Rf $(OBJ_DIR)

