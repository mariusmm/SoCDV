project new -name Timer
solution file add ./Slave.cpp
go analyze
go compile
solution library add nangate-45nm_beh -- -rtlsyntool DesignCompiler -vendor Nangate -technology 045nm
solution library add ram_nangate-45nm-register-file_beh
directive set -CLOCKS {clk_i {-CLOCK_PERIOD 20 -CLOCK_HIGH_TIME 10 -CLOCK_OFFSET 0.000000 -CLOCK_UNCERTAINTY 0.0}}
go extract
project save
flow run /DesignAnalyzer/launch
