GHDL=ghdl
GHDLOPTS=
GTKWAVE=gtkwave

all: run

run: cordic.vhd tb.vhd
	$(GHDL) -a cordic.vhd
	$(GHDL) -a tb.vhd
	$(GHDL) -e tb
	$(GHDL) -r tb --stop-time=1000ns --vcd=tb.vcd

view: tb.vcd
	$(GTKWAVE) -f tb.vcd -a tb.sav

clean:
	\rm -f work*.cf
	\rm -f *.o ./tb
	\rm -f tb.vcd

clobber: clean
	\rm -f *~

