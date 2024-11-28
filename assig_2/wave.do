onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -divider Bus
add wave -noupdate /top/Master/clk_i.m_cur_val
add wave -noupdate /top/reset_n
add wave -noupdate /top/Master/device_addr
add wave -noupdate /top/Master/device_req
add wave -noupdate /top/Master/device_we
add wave -noupdate /top/Master/device_wdata
add wave -noupdate -divider Timer
add wave -noupdate -radix hexadecimal /top/Slave/mtime_q
add wave -noupdate -radix hexadecimal /top/Slave/mtime_d
add wave -noupdate -radix hexadecimal /top/Slave/mtime_inc
add wave -noupdate /top/Slave/timer_rvalid_o
add wave -noupdate /top/Slave/timer_rdata_o
add wave -noupdate /top/Slave/rdata_d
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {205 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ns} {58 ns}
