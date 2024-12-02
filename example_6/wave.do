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
add wave -noupdate /top/reset_n
add wave -noupdate /top/device_req
add wave -noupdate /top/device_we
add wave -noupdate /top/device_addr
add wave -noupdate /top/device_wdata
add wave -noupdate /top/device_rvalid
add wave -noupdate /top/device_rdata
add wave -noupdate /top/device_err
add wave -noupdate /top/device_intr
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
WaveRestoreZoom {187 ns} {222 ns}
