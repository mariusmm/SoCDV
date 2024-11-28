vlib work
vlog timer.sv
scgenmod -map "scalar=bool" -sc_uint -bool timer > timer.h
sccom Master.cpp
sccom top.cpp
sccom -link
vopt +acc top -o top_opt
vsim top_opt
do wave.do
run 300 ns
