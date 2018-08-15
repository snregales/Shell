###################################################################################################################
# This Makefile is for the Shell project 
###################################################################################################################

PROJECT = Shell
CONFIG = Debug
STD = c++14

SRC = src
INC = inc
OBJ = obj
BIN = bin
TST = test
MSC = misc
DIR = |-

NC = \033[1;0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m

CFLS = $(wildcard $(SRC)/*.cpp)
TFLS = $(wildcard $(TST)/$(SRC)/*.cpp)
OBJS = $(patsubst %,$(OBJ)/%, $(notdir $(CFLS:.cpp=.o)))
TOBJS = $(patsubst %,$(TST)/$(OBJ)/%, $(notdir $(TFLS:.cpp=.o)))
EXE = $(BIN)/$(PROJECT).exe
TEXE = $(TST)/tested.exe
TINC = $(TST)/$(MSC)/testing.hpp

CC = g++
CFLAGS = -std=$(STD) -Wall -g -I$(INC)
RFLAG = -lreadline

$(EXE) : $(OBJS)
	@echo "$(YELLOW)Linking...$(NC)"
	$(CC) -o $@ $^ $(RFLAG)
	@echo "$(GREEN)Finished!$(NC)"

$(OBJ)/%.o : $(CFLS)
	@echo "$(RED)Compiling...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

$(TEXE): $(TOBJS)
	@echo "$(YELLOW)Linking Test...$(NC)"
	$(CC) -o $@ $^
	@echo "$(GREEN)Finished Test!$(NC)"

$(TST)/$(OBJ)%.o : $(TFLS)
	@echo "$(RED)Compiling Test...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: help run clean test tclean

prerun :
	touch $(INC)/testing.hpp

pretest :
	cp -f $(TINC) $(INC)

run : prerun $(EXE)
	$(EXE)

test : pretest $(TEXE)
	$(TEXE)

crun : clean run

ctest : tclean test

clean : 
	rm -f $(OBJS) $(EXE) $(INC)/testing.hpp

tclean : 
	rm -f $(TOBJS) $(TEXE)

help :
	@echo "$(GREEN)Project: $(BLUE)$(PROJECT)$(NC)"
	@echo "$(GREEN)File System Hierarchy:$(NC)"
	@echo "$(RED)$(PROJECT):$(NC)"
	@echo "$(DIR)$(RED)$(SRC):$(NC)\t*.cpp, *.c and .cc files"
	@echo "$(DIR)$(RED)$(INC):$(NC)\t*.h  and *.hpp files"
	@echo "$(DIR)$(RED)$(OBJ):$(NC)\t*.o and *.obj files"
	@echo "$(DIR)$(RED)$(SRC):$(NC)\t*.exe and *.dll files"
	@echo "$(DIR)$(RED)$(TST):$(NC)\tTest driven files"
	@echo "  $(DIR)$(RED)$(SRC):$(NC)\tTest scripts"
	@echo "  $(DIR)$(RED)$(OBJ):$(NC)\t*.o and *obj for compiled tests"
	@echo "  $(DIR)$(RED)$(MSC):$(NC)\tAny and all miscellaneous files"
	@echo "$(YELLOW)run: $(NC) compiles, links, and executes the program"
	@echo "$(YELLOW)clean: $(NC) clean file system; obj and bin folder"
	@echo "$(YELLOW)crun: $(NC) clean than run"	
	@echo "$(YELLOW)test: $(NC) compiles, links, and executes the program test units"
	@echo "$(YELLOW)tclean: $(NC) clean file system; tests folder"
	@echo "$(YELLOW)ctest: $(NC) clean than test"	