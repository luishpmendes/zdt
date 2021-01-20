CPP=g++
CARGS=-std=c++17 -Wall -Werror -O0 -g3 -m64
BRKGAINC=-I ../nsbrkga_mp_ipr/nsbrkga_mp_ipr
PAGMOINC=-pthread -lpagmo -lboost_serialization -ltbb -I /opt/pagmo/include -I /opt/boost/include -L /opt/pagmo/lib -L /opt/boost/lib -Wl,-R/opt/pagmo/lib
MKDIR=mkdir -p
RM=rm -rf
SRC=$(PWD)/src
BIN=$(PWD)/bin

clean:
	@echo "--> Cleaning compiled..."
	$(RM) $(BIN)
	@echo

$(BIN)/%.o: $(SRC)/%.cpp
	@echo "--> Compiling $<..."
	$(MKDIR) $(@D)
	$(CPP) $(CARGS) -c $< -o $@ $(BRKGAINC) $(PAGMOINC)
	@echo

$(BIN)/test/NSGA2_Solver_Test : $(BIN)/solver/Solver.o \
                                $(BIN)/solver/nsga2/NSGA2_Solver.o \
                                $(BIN)/test/NSGA2_Solver_Test.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/NSGA2_Solver_Test
	@echo

NSGA2_Solver_Test : clean $(BIN)/test/NSGA2_Solver_Test

$(BIN)/exec/NSGA2_Solver_Exec : $(BIN)/solver/Solver.o \
                                $(BIN)/solver/nsga2/NSGA2_Solver.o \
                                $(BIN)/utils/ArgumentParser.o \
                                $(BIN)/exec/NSGA2_Solver_Exec.o 
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo

NSGA2_Solver_Exec : clean $(BIN)/exec/NSGA2_Solver_Exec

$(BIN)/test/NSPSO_Solver_Test : $(BIN)/solver/Solver.o \
                                $(BIN)/solver/nspso/NSPSO_Solver.o \
                                $(BIN)/test/NSPSO_Solver_Test.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/NSPSO_Solver_Test
	@echo

NSPSO_Solver_Test : clean $(BIN)/test/NSPSO_Solver_Test

tests: NSGA2_Solver_Test \
       NSPSO_Solver_Test

execs: NSGA2_Solver_Exec

all: tests execs

