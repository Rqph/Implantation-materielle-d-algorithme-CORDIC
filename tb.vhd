library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb is
end tb;

architecture seq of tb is

	signal CLK  : std_logic;
  signal RST  : std_logic;
	signal PHI  : signed(15 downto 0);
	signal N    : natural range 0 to 16;
	signal START: std_logic;
  signal R1   : signed(15 downto 0);
  signal R2   : signed(15 downto 0);
  signal RDY  : std_logic;

begin

  UUT: entity work.cordic port map(CLK,RST,PHI,N,START,R1,R2,RDY);

  CLOCK: process
  begin
    CLK <= '1';
    wait for 5 ns;
    CLK <= '0';
    wait for 5 ns;
    end process;

  INITIALISATION: process
  begin
    PHI <= to_signed(60*270,16);
    N <= 16;
    wait for 50 ns;
    START <= '1';
    wait for 10 ns;
    START <= '0';
    wait ;
  end process;
  
  RAZ: process
  begin
    RST <= '1';
    wait for 10 ns;
    RST <= '0';
    wait;
  end process;

end architecture;

