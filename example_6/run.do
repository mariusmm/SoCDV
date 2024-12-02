vlib work
vlog Timer/Slave.v1/rtl.v
scgenmod -map "scalar=bool" -sc_uint -bool Slave > Slave.h
sccom Master.cpp
sccom top.cpp
sccom -link
vopt +acc top -o top_opt
vsim top_opt
do wave.do
run 300 ns
