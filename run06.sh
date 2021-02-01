#!/bin/bash

timeLimit=15;

mkdir -p statistics;
mkdir -p solutions;
mkdir -p pareto;
mkdir -p capturedParetos;

./bin/exec/NSGA2_Solver_Exec --zdt 1 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nsga2-zdt1-run6.txt \
                             --solution solutions/nsga2-zdt1-run6.txt \
                             --pareto pareto/nsga2-zdt1-run6.txt \
                             --captured-paretos \
                                capturedParetos/nsga2-zdt1-run6;

./bin/exec/NSPSO_Solver_Exec --zdt 1 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nspso-zdt1-run6.txt \
                             --solutions solutions/nspso-zdt1-run6 \
                             --pareto pareto/nspso-zdt1-run6.txt \
                             --captured-paretos \
                                capturedParetos/nspso-zdt1-run6;

./bin/exec/NSBRKGA_MP_IPR_Solver_Exec --zdt 1 \
                                      --time-limit $timeLimit \
                                      --capture-enabled \
                                      --statistics \
                                        statistics/nsbrkga-zdt1-run6.txt \
                                      --solutions \
                                        solutions/nsbrkga-zdt1-run6.txt \
                                      --pareto \
                                        pareto/nsbrkga-zdt1-run6.txt \
                                      --captured-paretos \
                                        capturedParetos/nsbrkga-zdt1-run6;

./bin/exec/Optimal_Solver_Exec --zdt 1 \
                               --time-limit $timeLimit \
                               --max-num-solutioons 1000 \
                               --statistics statistics/optimal-zdt1-run6.txt \
                               --solutions solutions/optimal-zdt1-run6.txt \
                               --pareto pareto/optimal-zdt1-run6.txt \
                               --captured-paretos \
                                    capturedParetos/optimal-zdt1-run6;

./bin/exec/NSGA2_Solver_Exec --zdt 2 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nsga2-zdt2-run6.txt \
                             --solutions solutions/nsga2-zdt2-run6.txt \
                             --pareto pareto/nsga2-zdt2-run6.txt \
                             --captured-paretos \
                                capturedParetos/nsga2-zdt2-run6;

./bin/exec/NSPSO_Solver_Exec --zdt 2 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nspso-zdt2-run6.txt \
                             --solutions solutions/nspso-zdt2-run6.txt \
                             --pareto pareto/nspso-zdt2-run6.txt \
                             --captured-paretos \
                                capturedParetos/nspso-zdt2-run6;

./bin/exec/NSBRKGA_MP_IPR_Solver_Exec --zdt 2 \
                                      --time-limit $timeLimit \
                                      --capture-enabled \
                                      --statistics \
                                        statistics/nsbrkga-zdt2-run6.txt \
                                      --solutions \
                                        solutions/nsbrkga-zdt2-run6.txt \
                                      --pareto \
                                        pareto/nsbrkga-zdt2-run6.txt \
                                      --captured-paretos \
                                        capturedParetos/nsbrkga-zdt2-run6;

./bin/exec/Optimal_Solver_Exec --zdt 2 \
                               --time-limit $timeLimit \
                               --max-num-solutioons 1000 \
                               --statistics statistics/optimal-zdt2-run6.txt \
                               --solutions solutions/optimal-zdt2-run6.txt \
                               --pareto pareto/optimal-zdt2-run6.txt \
                               --captured-paretos \
                                    capturedParetos/optimal-zdt2-run6;

./bin/exec/NSGA2_Solver_Exec --zdt 3 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nsga2-zdt3-run6.txt \
                             --solutions solutions/nsga2-zdt3-run6.txt \
                             --pareto pareto/nsga2-zdt3-run6.txt \
                             --captured-paretos \
                                capturedParetos/nsga2-zdt3-run6;

./bin/exec/NSPSO_Solver_Exec --zdt 3 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nspso-zdt3-run6.txt \
                             --solutions solutions/nspso-zdt3-run6.txt \
                             --pareto pareto/nspso-zdt3-run6.txt \
                             --captured-paretos \
                                capturedParetos/nspso-zdt3-run6;

./bin/exec/NSBRKGA_MP_IPR_Solver_Exec --zdt 3 \
                                      --time-limit $timeLimit \
                                      --capture-enabled \
                                      --statistics \
                                        statistics/nsbrkga-zdt3-run6.txt \
                                      --solutions \
                                        solutions/nsbrkga-zdt3-run6.txt \
                                      --pareto \
                                        pareto/nsbrkga-zdt3-run6.txt \
                                      --captured-paretos \
                                        capturedParetos/nsbrkga-zdt3-run6;

./bin/exec/Optimal_Solver_Exec --zdt 3 \
                               --time-limit $timeLimit \
                               --max-num-solutioons 1000 \
                               --statistics statistics/optimal-zdt3-run6.txt \
                               --solutions solutions/optimal-zdt3-run6.txt \
                               --pareto pareto/optimal-zdt3-run6.txt \
                               --captured-paretos \
                                    capturedParetos/optimal-zdt3-run6;

./bin/exec/NSGA2_Solver_Exec --zdt 4 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nsga2-zdt4-run6.txt \
                             --solutions solutions/nsga2-zdt4-run6.txt \
                             --pareto pareto/nsga2-zdt4-run6.txt \
                             --captured-paretos \
                                capturedParetos/nsga2-zdt4-run6;

./bin/exec/NSPSO_Solver_Exec --zdt 4 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nspso-zdt4-run6.txt \
                             --solutions solutions/nspso-zdt4-run6.txt \
                             --pareto pareto/nspso-zdt4-run6.txt \
                             --captured-paretos \
                                capturedParetos/nspso-zdt4-run6;

./bin/exec/NSBRKGA_MP_IPR_Solver_Exec --zdt 4 \
                                      --time-limit $timeLimit \
                                      --capture-enabled \
                                      --statistics \
                                        statistics/nsbrkga-zdt4-run6.txt \
                                      --solutions \
                                        solutions/nsbrkga-zdt4-run6.txt \
                                      --pareto \
                                        pareto/nsbrkga-zdt4-run6.txt \
                                      --captured-paretos \
                                        capturedParetos/nsbrkga-zdt4-run6;

./bin/exec/Optimal_Solver_Exec --zdt 4 \
                               --time-limit $timeLimit \
                               --max-num-solutioons 1000 \
                               --statistics statistics/optimal-zdt4-run6.txt \
                               --solutions solutions/optimal-zdt4-run6.txt \
                               --pareto pareto/optimal-zdt4-run6.txt \
                               --captured-paretos \
                                    capturedParetos/optimal-zdt4-run6;

./bin/exec/NSGA2_Solver_Exec --zdt 6 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nsga2-zdt6-run6.txt \
                             --solutions solutions/nsga2-zdt6-run6.txt \
                             --pareto pareto/nsga2-zdt6-run6.txt \
                             --captured-paretos \
                                capturedParetos/nsga2-zdt6-run6;

./bin/exec/NSPSO_Solver_Exec --zdt 6 \
                             --time-limit $timeLimit \
                             --capture-enabled \
                             --statistics statistics/nspso-zdt6-run6.txt \
                             --solutions solutions/nspso-zdt6-run6.txt \
                             --pareto pareto/nspso-zdt6-run6.txt \
                             --captured-paretos \
                                capturedParetos/nspso-zdt6-run6;

./bin/exec/NSBRKGA_MP_IPR_Solver_Exec --zdt 6 \
                                      --time-limit $timeLimit \
                                      --capture-enabled \
                                      --statistics \
                                        statistics/nsbrkga-zdt6-run6.txt \
                                      --solutions \
                                        solutions/nsbrkga-zdt6-run6.txt \
                                      --pareto \
                                        pareto/nsbrkga-zdt6-run6.txt \
                                      --captured-paretos \
                                        capturedParetos/nsbrkga-zdt6-run6;

./bin/exec/Optimal_Solver_Exec --zdt 6 \
                               --time-limit $timeLimit \
                               --max-num-solutioons 1000 \
                               --statistics statistics/optimal-zdt6-run6.txt \
                               --solutions solutions/optimal-zdt6-run6.txt \
                               --pareto pareto/optimal-zdt6-run6.txt \
                               --captured-paretos \
                                    capturedParetos/optimal-zdt6-run6;

