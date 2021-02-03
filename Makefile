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

$(BIN)/exec/NSPSO_Solver_Exec : $(BIN)/solver/Solver.o \
                                $(BIN)/solver/nspso/NSPSO_Solver.o \
                                $(BIN)/utils/ArgumentParser.o \
                                $(BIN)/exec/NSPSO_Solver_Exec.o 
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo

NSPSO_Solver_Exec : clean $(BIN)/exec/NSPSO_Solver_Exec

$(BIN)/test/MOEAD_Solver_Test : $(BIN)/solver/Solver.o \
                                $(BIN)/solver/moead/MOEAD_Solver.o \
                                $(BIN)/test/MOEAD_Solver_Test.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/MOEAD_Solver_Test
	@echo

MOEAD_Solver_Test : clean $(BIN)/test/MOEAD_Solver_Test

$(BIN)/exec/MOEAD_Solver_Exec : $(BIN)/solver/Solver.o \
                                $(BIN)/solver/moead/MOEAD_Solver.o \
                                $(BIN)/utils/ArgumentParser.o \
                                $(BIN)/exec/MOEAD_Solver_Exec.o 
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo

MOEAD_Solver_Exec : clean $(BIN)/exec/MOEAD_Solver_Exec

$(BIN)/test/MHACO_Solver_Test : $(BIN)/solver/Solver.o \
                                $(BIN)/solver/mhaco/MHACO_Solver.o \
                                $(BIN)/test/MHACO_Solver_Test.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/MHACO_Solver_Test
	@echo

MHACO_Solver_Test : clean $(BIN)/test/MHACO_Solver_Test

$(BIN)/exec/MHACO_Solver_Exec : $(BIN)/solver/Solver.o \
                                $(BIN)/solver/mhaco/MHACO_Solver.o \
                                $(BIN)/utils/ArgumentParser.o \
                                $(BIN)/exec/MHACO_Solver_Exec.o 
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo

MHACO_Solver_Exec : clean $(BIN)/exec/MHACO_Solver_Exec

$(BIN)/test/NSBRKGA_MP_IPR_Solver_Test : $(BIN)/solver/Solver.o \
                                         $(BIN)/solver/nsbrkga_mp_ipr/Decoder.o \
                                         $(BIN)/solver/nsbrkga_mp_ipr/NSBRKGA_MP_IPR_Solver.o \
                                         $(BIN)/test/NSBRKGA_MP_IPR_Solver_Test.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/NSBRKGA_MP_IPR_Solver_Test
	@echo

NSBRKGA_MP_IPR_Solver_Test : clean $(BIN)/test/NSBRKGA_MP_IPR_Solver_Test

$(BIN)/exec/NSBRKGA_MP_IPR_Solver_Exec : $(BIN)/solver/Solver.o \
                                         $(BIN)/solver/nsbrkga_mp_ipr/Decoder.o \
                                         $(BIN)/solver/nsbrkga_mp_ipr/NSBRKGA_MP_IPR_Solver.o \
                                         $(BIN)/utils/ArgumentParser.o \
                                         $(BIN)/exec/NSBRKGA_MP_IPR_Solver_Exec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo

NSBRKGA_MP_IPR_Solver_Exec : clean $(BIN)/exec/NSBRKGA_MP_IPR_Solver_Exec

$(BIN)/test/Optimal_Solver_Test : $(BIN)/solver/Solver.o \
                                  $(BIN)/solver/optimal/Optimal_Solver.o \
                                  $(BIN)/test/Optimal_Solver_Test.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/Optimal_Solver_Test
	@echo

Optimal_Solver_Test : clean $(BIN)/test/Optimal_Solver_Test

$(BIN)/exec/Optimal_Solver_Exec : $(BIN)/solver/Solver.o \
                                  $(BIN)/solver/optimal/Optimal_Solver.o \
                                  $(BIN)/utils/ArgumentParser.o \
                                  $(BIN)/exec/Optimal_Solver_Exec.o 
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS) $(PAGMOINC)
	@echo

Optimal_Solver_Exec : clean $(BIN)/exec/Optimal_Solver_Exec

tests: NSGA2_Solver_Test \
       NSPSO_Solver_Test \
       MOEAD_Solver_Test \
       MHACO_Solver_Test \
       NSBRKGA_MP_IPR_Solver_Test \
       Optimal_Solver_Test

execs: NSGA2_Solver_Exec \
       NSPSO_Solver_Exec \
       MOEAD_Solver_Exec \
       MHACO_Solver_Exec \
       NSBRKGA_MP_IPR_Solver_Exec \
       Optimal_Solver_Exec

all: tests execs

