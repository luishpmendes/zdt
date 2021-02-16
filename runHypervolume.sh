#!/bin/bash

mkdir -p hypervolume;
mkdir -p capturedHypervolume;

./bin/exec/Hypervolume_Calculator_Exec \
    --pareto-0 pareto/nsga2-zdt1-run1.txt \
    --pareto-1 pareto/nspso-zdt1-run1.txt \
    --pareto-2 pareto/nsbrkga-zdt1-run1.txt \
    --pareto-3 pareto/optimal-zdt1-run1.txt \
    --pareto-4 pareto/nsga2-zdt1-run2.txt \
    --pareto-5 pareto/nspso-zdt1-run2.txt \
    --pareto-6 pareto/nsbrkga-zdt1-run2.txt \
    --pareto-7 pareto/optimal-zdt1-run2.txt \
    --pareto-8 pareto/nsga2-zdt1-run3.txt \
    --pareto-9 pareto/nspso-zdt1-run3.txt \
    --pareto-10 pareto/nsbrkga-zdt1-run3.txt \
    --pareto-11 pareto/optimal-zdt1-run3.txt \
    --captured-paretos-0 capturedParetos/nsga2-zdt1-run1 \
    --captured-paretos-1 capturedParetos/nspso-zdt1-run1 \
    --captured-paretos-2 capturedParetos/nsbrkga-zdt1-run1 \
    --captured-paretos-3 capturedParetos/optimal-zdt1-run1 \
    --captured-paretos-4 capturedParetos/nsga2-zdt1-run2 \
    --captured-paretos-5 capturedParetos/nspso-zdt1-run2 \
    --captured-paretos-6 capturedParetos/nsbrkga-zdt1-run2 \
    --captured-paretos-7 capturedParetos/optimal-zdt1-run2 \
    --captured-paretos-8 capturedParetos/nsga2-zdt1-run3 \
    --captured-paretos-9 capturedParetos/nspso-zdt1-run3 \
    --captured-paretos-10 capturedParetos/nsbrkga-zdt1-run3 \
    --captured-paretos-11 capturedParetos/optimal-zdt1-run3 \
    --hypervolume-0 hypervolume/nsga2-zdt1-run1.txt \
    --hypervolume-1 hypervolume/nspso-zdt1-run1.txt \
    --hypervolume-2 hypervolume/nsbrkga-zdt1-run1.txt \
    --hypervolume-3 hypervolume/optimal-zdt1-run1.txt \
    --hypervolume-4 hypervolume/nsga2-zdt1-run2.txt \
    --hypervolume-5 hypervolume/nspso-zdt1-run2.txt \
    --hypervolume-6 hypervolume/nsbrkga-zdt1-run2.txt \
    --hypervolume-7 hypervolume/optimal-zdt1-run2.txt \
    --hypervolume-8 hypervolume/nsga2-zdt1-run3.txt \
    --hypervolume-9 hypervolume/nspso-zdt1-run3.txt \
    --hypervolume-10 hypervolume/nsbrkga-zdt1-run3.txt \
    --hypervolume-11 hypervolume/optimal-zdt1-run3.txt \
    --captured-hypervolumes-0 capturedHypervolume/nsga2-zdt1-run1 \
    --captured-hypervolumes-1 capturedHypervolume/nspso-zdt1-run1 \
    --captured-hypervolumes-2 capturedHypervolume/nsbrkga-zdt1-run1 \
    --captured-hypervolumes-3 capturedHypervolume/optimal-zdt1-run1 \
    --captured-hypervolumes-4 capturedHypervolume/nsga2-zdt1-run2 \
    --captured-hypervolumes-5 capturedHypervolume/nspso-zdt1-run2 \
    --captured-hypervolumes-6 capturedHypervolume/nsbrkga-zdt1-run2 \
    --captured-hypervolumes-7 capturedHypervolume/optimal-zdt1-run2 \
    --captured-hypervolumes-8 capturedHypervolume/nsga2-zdt1-run3 \
    --captured-hypervolumes-9 capturedHypervolume/nspso-zdt1-run3 \
    --captured-hypervolumes-10 capturedHypervolume/nsbrkga-zdt1-run3 \
    --captured-hypervolumes-11 capturedHypervolume/optimal-zdt1-run3;

./bin/exec/Hypervolume_Calculator_Exec \
    --pareto-0 pareto/nsga2-zdt2-run1.txt \
    --pareto-1 pareto/nspso-zdt2-run1.txt \
    --pareto-2 pareto/nsbrkga-zdt2-run1.txt \
    --pareto-3 pareto/optimal-zdt2-run1.txt \
    --pareto-4 pareto/nsga2-zdt2-run2.txt \
    --pareto-5 pareto/nspso-zdt2-run2.txt \
    --pareto-6 pareto/nsbrkga-zdt2-run2.txt \
    --pareto-7 pareto/optimal-zdt2-run2.txt \
    --pareto-8 pareto/nsga2-zdt2-run3.txt \
    --pareto-9 pareto/nspso-zdt2-run3.txt \
    --pareto-10 pareto/nsbrkga-zdt2-run3.txt \
    --pareto-11 pareto/optimal-zdt2-run3.txt \
    --captured-paretos-0 capturedParetos/nsga2-zdt2-run1 \
    --captured-paretos-1 capturedParetos/nspso-zdt2-run1 \
    --captured-paretos-2 capturedParetos/nsbrkga-zdt2-run1 \
    --captured-paretos-3 capturedParetos/optimal-zdt2-run1 \
    --captured-paretos-4 capturedParetos/nsga2-zdt2-run2 \
    --captured-paretos-5 capturedParetos/nspso-zdt2-run2 \
    --captured-paretos-6 capturedParetos/nsbrkga-zdt2-run2 \
    --captured-paretos-7 capturedParetos/optimal-zdt2-run2 \
    --captured-paretos-8 capturedParetos/nsga2-zdt2-run3 \
    --captured-paretos-9 capturedParetos/nspso-zdt2-run3 \
    --captured-paretos-10 capturedParetos/nsbrkga-zdt2-run3 \
    --captured-paretos-11 capturedParetos/optimal-zdt2-run3 \
    --hypervolume-0 hypervolume/nsga2-zdt2-run1.txt \
    --hypervolume-1 hypervolume/nspso-zdt2-run1.txt \
    --hypervolume-2 hypervolume/nsbrkga-zdt2-run1.txt \
    --hypervolume-3 hypervolume/optimal-zdt2-run1.txt \
    --hypervolume-4 hypervolume/nsga2-zdt2-run2.txt \
    --hypervolume-5 hypervolume/nspso-zdt2-run2.txt \
    --hypervolume-6 hypervolume/nsbrkga-zdt2-run2.txt \
    --hypervolume-7 hypervolume/optimal-zdt2-run2.txt \
    --hypervolume-8 hypervolume/nsga2-zdt2-run3.txt \
    --hypervolume-9 hypervolume/nspso-zdt2-run3.txt \
    --hypervolume-10 hypervolume/nsbrkga-zdt2-run3.txt \
    --hypervolume-11 hypervolume/optimal-zdt2-run3.txt \
    --captured-hypervolumes-0 capturedHypervolume/nsga2-zdt2-run1 \
    --captured-hypervolumes-1 capturedHypervolume/nspso-zdt2-run1 \
    --captured-hypervolumes-2 capturedHypervolume/nsbrkga-zdt2-run1 \
    --captured-hypervolumes-3 capturedHypervolume/optimal-zdt2-run1 \
    --captured-hypervolumes-4 capturedHypervolume/nsga2-zdt2-run2 \
    --captured-hypervolumes-5 capturedHypervolume/nspso-zdt2-run2 \
    --captured-hypervolumes-6 capturedHypervolume/nsbrkga-zdt2-run2 \
    --captured-hypervolumes-7 capturedHypervolume/optimal-zdt2-run2 \
    --captured-hypervolumes-8 capturedHypervolume/nsga2-zdt2-run3 \
    --captured-hypervolumes-9 capturedHypervolume/nspso-zdt2-run3 \
    --captured-hypervolumes-10 capturedHypervolume/nsbrkga-zdt2-run3 \
    --captured-hypervolumes-11 capturedHypervolume/optimal-zdt2-run3;

./bin/exec/Hypervolume_Calculator_Exec \
    --pareto-0 pareto/nsga2-zdt3-run1.txt \
    --pareto-1 pareto/nspso-zdt3-run1.txt \
    --pareto-2 pareto/nsbrkga-zdt3-run1.txt \
    --pareto-3 pareto/optimal-zdt3-run1.txt \
    --pareto-4 pareto/nsga2-zdt3-run2.txt \
    --pareto-5 pareto/nspso-zdt3-run2.txt \
    --pareto-6 pareto/nsbrkga-zdt3-run2.txt \
    --pareto-7 pareto/optimal-zdt3-run2.txt \
    --pareto-8 pareto/nsga2-zdt3-run3.txt \
    --pareto-9 pareto/nspso-zdt3-run3.txt \
    --pareto-10 pareto/nsbrkga-zdt3-run3.txt \
    --pareto-11 pareto/optimal-zdt3-run3.txt \
    --captured-paretos-0 capturedParetos/nsga2-zdt3-run1 \
    --captured-paretos-1 capturedParetos/nspso-zdt3-run1 \
    --captured-paretos-2 capturedParetos/nsbrkga-zdt3-run1 \
    --captured-paretos-3 capturedParetos/optimal-zdt3-run1 \
    --captured-paretos-4 capturedParetos/nsga2-zdt3-run2 \
    --captured-paretos-5 capturedParetos/nspso-zdt3-run2 \
    --captured-paretos-6 capturedParetos/nsbrkga-zdt3-run2 \
    --captured-paretos-7 capturedParetos/optimal-zdt3-run2 \
    --captured-paretos-8 capturedParetos/nsga2-zdt3-run3 \
    --captured-paretos-9 capturedParetos/nspso-zdt3-run3 \
    --captured-paretos-10 capturedParetos/nsbrkga-zdt3-run3 \
    --captured-paretos-11 capturedParetos/optimal-zdt3-run3 \
    --hypervolume-0 hypervolume/nsga2-zdt3-run1.txt \
    --hypervolume-1 hypervolume/nspso-zdt3-run1.txt \
    --hypervolume-2 hypervolume/nsbrkga-zdt3-run1.txt \
    --hypervolume-3 hypervolume/optimal-zdt3-run1.txt \
    --hypervolume-4 hypervolume/nsga2-zdt3-run2.txt \
    --hypervolume-5 hypervolume/nspso-zdt3-run2.txt \
    --hypervolume-6 hypervolume/nsbrkga-zdt3-run2.txt \
    --hypervolume-7 hypervolume/optimal-zdt3-run2.txt \
    --hypervolume-8 hypervolume/nsga2-zdt3-run3.txt \
    --hypervolume-9 hypervolume/nspso-zdt3-run3.txt \
    --hypervolume-10 hypervolume/nsbrkga-zdt3-run3.txt \
    --hypervolume-11 hypervolume/optimal-zdt3-run3.txt \
    --captured-hypervolumes-0 capturedHypervolume/nsga2-zdt3-run1 \
    --captured-hypervolumes-1 capturedHypervolume/nspso-zdt3-run1 \
    --captured-hypervolumes-2 capturedHypervolume/nsbrkga-zdt3-run1 \
    --captured-hypervolumes-3 capturedHypervolume/optimal-zdt3-run1 \
    --captured-hypervolumes-4 capturedHypervolume/nsga2-zdt3-run2 \
    --captured-hypervolumes-5 capturedHypervolume/nspso-zdt3-run2 \
    --captured-hypervolumes-6 capturedHypervolume/nsbrkga-zdt3-run2 \
    --captured-hypervolumes-7 capturedHypervolume/optimal-zdt3-run2 \
    --captured-hypervolumes-8 capturedHypervolume/nsga2-zdt3-run3 \
    --captured-hypervolumes-9 capturedHypervolume/nspso-zdt3-run3 \
    --captured-hypervolumes-10 capturedHypervolume/nsbrkga-zdt3-run3 \
    --captured-hypervolumes-11 capturedHypervolume/optimal-zdt3-run3;

./bin/exec/Hypervolume_Calculator_Exec \
    --pareto-0 pareto/nsga2-zdt4-run1.txt \
    --pareto-1 pareto/nspso-zdt4-run1.txt \
    --pareto-2 pareto/nsbrkga-zdt4-run1.txt \
    --pareto-3 pareto/optimal-zdt4-run1.txt \
    --pareto-4 pareto/nsga2-zdt4-run2.txt \
    --pareto-5 pareto/nspso-zdt4-run2.txt \
    --pareto-6 pareto/nsbrkga-zdt4-run2.txt \
    --pareto-7 pareto/optimal-zdt4-run2.txt \
    --pareto-8 pareto/nsga2-zdt4-run3.txt \
    --pareto-9 pareto/nspso-zdt4-run3.txt \
    --pareto-10 pareto/nsbrkga-zdt4-run3.txt \
    --pareto-11 pareto/optimal-zdt4-run3.txt \
    --captured-paretos-0 capturedParetos/nsga2-zdt4-run1 \
    --captured-paretos-1 capturedParetos/nspso-zdt4-run1 \
    --captured-paretos-2 capturedParetos/nsbrkga-zdt4-run1 \
    --captured-paretos-3 capturedParetos/optimal-zdt4-run1 \
    --captured-paretos-4 capturedParetos/nsga2-zdt4-run2 \
    --captured-paretos-5 capturedParetos/nspso-zdt4-run2 \
    --captured-paretos-6 capturedParetos/nsbrkga-zdt4-run2 \
    --captured-paretos-7 capturedParetos/optimal-zdt4-run2 \
    --captured-paretos-8 capturedParetos/nsga2-zdt4-run3 \
    --captured-paretos-9 capturedParetos/nspso-zdt4-run3 \
    --captured-paretos-10 capturedParetos/nsbrkga-zdt4-run3 \
    --captured-paretos-11 capturedParetos/optimal-zdt4-run3 \
    --hypervolume-0 hypervolume/nsga2-zdt4-run1.txt \
    --hypervolume-1 hypervolume/nspso-zdt4-run1.txt \
    --hypervolume-2 hypervolume/nsbrkga-zdt4-run1.txt \
    --hypervolume-3 hypervolume/optimal-zdt4-run1.txt \
    --hypervolume-4 hypervolume/nsga2-zdt4-run2.txt \
    --hypervolume-5 hypervolume/nspso-zdt4-run2.txt \
    --hypervolume-6 hypervolume/nsbrkga-zdt4-run2.txt \
    --hypervolume-7 hypervolume/optimal-zdt4-run2.txt \
    --hypervolume-8 hypervolume/nsga2-zdt4-run3.txt \
    --hypervolume-9 hypervolume/nspso-zdt4-run3.txt \
    --hypervolume-10 hypervolume/nsbrkga-zdt4-run3.txt \
    --hypervolume-11 hypervolume/optimal-zdt4-run3.txt \
    --captured-hypervolumes-0 capturedHypervolume/nsga2-zdt4-run1 \
    --captured-hypervolumes-1 capturedHypervolume/nspso-zdt4-run1 \
    --captured-hypervolumes-2 capturedHypervolume/nsbrkga-zdt4-run1 \
    --captured-hypervolumes-3 capturedHypervolume/optimal-zdt4-run1 \
    --captured-hypervolumes-4 capturedHypervolume/nsga2-zdt4-run2 \
    --captured-hypervolumes-5 capturedHypervolume/nspso-zdt4-run2 \
    --captured-hypervolumes-6 capturedHypervolume/nsbrkga-zdt4-run2 \
    --captured-hypervolumes-7 capturedHypervolume/optimal-zdt4-run2 \
    --captured-hypervolumes-8 capturedHypervolume/nsga2-zdt4-run3 \
    --captured-hypervolumes-9 capturedHypervolume/nspso-zdt4-run3 \
    --captured-hypervolumes-10 capturedHypervolume/nsbrkga-zdt4-run3 \
    --captured-hypervolumes-11 capturedHypervolume/optimal-zdt4-run3;

./bin/exec/Hypervolume_Calculator_Exec \
    --pareto-0 pareto/nsga2-zdt6-run1.txt \
    --pareto-1 pareto/nspso-zdt6-run1.txt \
    --pareto-2 pareto/nsbrkga-zdt6-run1.txt \
    --pareto-3 pareto/optimal-zdt6-run1.txt \
    --pareto-4 pareto/nsga2-zdt6-run2.txt \
    --pareto-5 pareto/nspso-zdt6-run2.txt \
    --pareto-6 pareto/nsbrkga-zdt6-run2.txt \
    --pareto-7 pareto/optimal-zdt6-run2.txt \
    --pareto-8 pareto/nsga2-zdt6-run3.txt \
    --pareto-9 pareto/nspso-zdt6-run3.txt \
    --pareto-10 pareto/nsbrkga-zdt6-run3.txt \
    --pareto-11 pareto/optimal-zdt6-run3.txt \
    --captured-paretos-0 capturedParetos/nsga2-zdt6-run1 \
    --captured-paretos-1 capturedParetos/nspso-zdt6-run1 \
    --captured-paretos-2 capturedParetos/nsbrkga-zdt6-run1 \
    --captured-paretos-3 capturedParetos/optimal-zdt6-run1 \
    --captured-paretos-4 capturedParetos/nsga2-zdt6-run2 \
    --captured-paretos-5 capturedParetos/nspso-zdt6-run2 \
    --captured-paretos-6 capturedParetos/nsbrkga-zdt6-run2 \
    --captured-paretos-7 capturedParetos/optimal-zdt6-run2 \
    --captured-paretos-8 capturedParetos/nsga2-zdt6-run3 \
    --captured-paretos-9 capturedParetos/nspso-zdt6-run3 \
    --captured-paretos-10 capturedParetos/nsbrkga-zdt6-run3 \
    --captured-paretos-11 capturedParetos/optimal-zdt6-run3 \
    --hypervolume-0 hypervolume/nsga2-zdt6-run1.txt \
    --hypervolume-1 hypervolume/nspso-zdt6-run1.txt \
    --hypervolume-2 hypervolume/nsbrkga-zdt6-run1.txt \
    --hypervolume-3 hypervolume/optimal-zdt6-run1.txt \
    --hypervolume-4 hypervolume/nsga2-zdt6-run2.txt \
    --hypervolume-5 hypervolume/nspso-zdt6-run2.txt \
    --hypervolume-6 hypervolume/nsbrkga-zdt6-run2.txt \
    --hypervolume-7 hypervolume/optimal-zdt6-run2.txt \
    --hypervolume-8 hypervolume/nsga2-zdt6-run3.txt \
    --hypervolume-9 hypervolume/nspso-zdt6-run3.txt \
    --hypervolume-10 hypervolume/nsbrkga-zdt6-run3.txt \
    --hypervolume-11 hypervolume/optimal-zdt6-run3.txt \
    --captured-hypervolumes-0 capturedHypervolume/nsga2-zdt6-run1 \
    --captured-hypervolumes-1 capturedHypervolume/nspso-zdt6-run1 \
    --captured-hypervolumes-2 capturedHypervolume/nsbrkga-zdt6-run1 \
    --captured-hypervolumes-3 capturedHypervolume/optimal-zdt6-run1 \
    --captured-hypervolumes-4 capturedHypervolume/nsga2-zdt6-run2 \
    --captured-hypervolumes-5 capturedHypervolume/nspso-zdt6-run2 \
    --captured-hypervolumes-6 capturedHypervolume/nsbrkga-zdt6-run2 \
    --captured-hypervolumes-7 capturedHypervolume/optimal-zdt6-run2 \
    --captured-hypervolumes-8 capturedHypervolume/nsga2-zdt6-run3 \
    --captured-hypervolumes-9 capturedHypervolume/nspso-zdt6-run3 \
    --captured-hypervolumes-10 capturedHypervolume/nsbrkga-zdt6-run3 \
    --captured-hypervolumes-11 capturedHypervolume/optimal-zdt6-run3;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt1-run1 \
    --captured-metrics-1 capturedHypervolume/nsga2-zdt1-run2 \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt1-run3 \
    --median-captured-metrics capturedHypervolume/nsga2-zdt1-median.txt \
    --mean-std-metric capturedHypervolume/nsga2-zdt1-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt2-run1 \
    --captured-metrics-1 capturedHypervolume/nsga2-zdt2-run2 \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt2-run3 \
    --median-captured-metrics capturedHypervolume/nsga2-zdt2-median.txt \
    --mean-std-metric capturedHypervolume/nsga2-zdt2-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt3-run1 \
    --captured-metrics-1 capturedHypervolume/nsga2-zdt3-run2 \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt3-run3 \
    --median-captured-metrics capturedHypervolume/nsga2-zdt3-median.txt \
    --mean-std-metric capturedHypervolume/nsga2-zdt3-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt4-run1 \
    --captured-metrics-1 capturedHypervolume/nsga2-zdt4-run2 \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt4-run3 \
    --median-captured-metrics capturedHypervolume/nsga2-zdt4-median.txt \
    --mean-std-metric capturedHypervolume/nsga2-zdt4-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt6-run1 \
    --captured-metrics-1 capturedHypervolume/nsga2-zdt6-run2 \
    --captured-metrics-0 capturedHypervolume/nsga2-zdt6-run3 \
    --median-captured-metrics capturedHypervolume/nsga2-zdt6-median.txt \
    --mean-std-metric capturedHypervolume/nsga2-zdt6-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nspso-zdt1-run1 \
    --captured-metrics-1 capturedHypervolume/nspso-zdt1-run2 \
    --captured-metrics-0 capturedHypervolume/nspso-zdt1-run3 \
    --median-captured-metrics capturedHypervolume/nspso-zdt1-median.txt \
    --mean-std-metric capturedHypervolume/nspso-zdt1-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nspso-zdt2-run1 \
    --captured-metrics-1 capturedHypervolume/nspso-zdt2-run2 \
    --captured-metrics-0 capturedHypervolume/nspso-zdt2-run3 \
    --median-captured-metrics capturedHypervolume/nspso-zdt2-median.txt \
    --mean-std-metric capturedHypervolume/nspso-zdt2-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nspso-zdt3-run1 \
    --captured-metrics-1 capturedHypervolume/nspso-zdt3-run2 \
    --captured-metrics-0 capturedHypervolume/nspso-zdt3-run3 \
    --median-captured-metrics capturedHypervolume/nspso-zdt3-median.txt \
    --mean-std-metric capturedHypervolume/nspso-zdt3-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nspso-zdt4-run1 \
    --captured-metrics-1 capturedHypervolume/nspso-zdt4-run2 \
    --captured-metrics-0 capturedHypervolume/nspso-zdt4-run3 \
    --median-captured-metrics capturedHypervolume/nspso-zdt4-median.txt \
    --mean-std-metric capturedHypervolume/nspso-zdt4-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nspso-zdt6-run1 \
    --captured-metrics-1 capturedHypervolume/nspso-zdt6-run2 \
    --captured-metrics-0 capturedHypervolume/nspso-zdt6-run3 \
    --median-captured-metrics capturedHypervolume/nspso-zdt6-median.txt \
    --mean-std-metric capturedHypervolume/nspso-zdt6-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt1-run1 \
    --captured-metrics-1 capturedHypervolume/nsbrkga-zdt1-run2 \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt1-run3 \
    --median-captured-metrics capturedHypervolume/nsbrkga-zdt1-median.txt \
    --mean-std-metric capturedHypervolume/nsbrkga-zdt1-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt2-run1 \
    --captured-metrics-1 capturedHypervolume/nsbrkga-zdt2-run2 \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt2-run3 \
    --median-captured-metrics capturedHypervolume/nsbrkga-zdt2-median.txt \
    --mean-std-metric capturedHypervolume/nsbrkga-zdt2-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt3-run1 \
    --captured-metrics-1 capturedHypervolume/nsbrkga-zdt3-run2 \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt3-run3 \
    --median-captured-metrics capturedHypervolume/nsbrkga-zdt3-median.txt \
    --mean-std-metric capturedHypervolume/nsbrkga-zdt3-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt4-run1 \
    --captured-metrics-1 capturedHypervolume/nsbrkga-zdt4-run2 \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt4-run3 \
    --median-captured-metrics capturedHypervolume/nsbrkga-zdt4-median.txt \
    --mean-std-metric capturedHypervolume/nsbrkga-zdt4-mean.txt;

./bin/exec/Metric_Aggregator_Exec \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt6-run1 \
    --captured-metrics-1 capturedHypervolume/nsbrkga-zdt6-run2 \
    --captured-metrics-0 capturedHypervolume/nsbrkga-zdt6-run3 \
    --median-captured-metrics capturedHypervolume/nsbrkga-zdt6-median.txt \
    --mean-std-metric capturedHypervolume/nsbrkga-zdt6-mean.txt;

