library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity cordic is port (
   CLK   : in std_logic;
   RST   : in std_logic;
   PHI   : in signed(15 downto 0);
   N     : in natural range 0 to 16;
   START : in std_logic;
   R1    : out signed(15 downto 0);
   R2    : out signed(15 downto 0);
   RDY   : out std_logic);
end entity;

architecture RTL of cordic is

   function fp2fix(x: real; M: real) return signed is
   begin
      return to_signed(integer(x*M),16);
   end;
        
   function fix2fp(x: signed(15 downto 0); M: real) return real is
   begin
      return real(to_integer(x))/M;
   end;

   type t_state is (Repos,Calcul);
   signal etat : t_state;

   type t_coef is array(0 to 15) of signed(15 downto 0);
   signal THETA : t_coef := ( 
      to_signed(12150,16), to_signed(7172,16), 
      to_signed(3789,16), to_signed(1923,16), 
      to_signed(965,16), to_signed(483,16), 
      to_signed(241,16), to_signed(120,16), 
      to_signed(60,16), to_signed(30,16), 
      to_signed(15,16), to_signed(7,16), 
      to_signed(3,16), to_signed(1,16), 
      to_signed(0,16), to_signed(0,16));
   signal A : t_coef := (
      to_signed(22627,16),to_signed(20238,16),
      to_signed(19634,16),to_signed(19482,16),
      to_signed(19444,16),to_signed(19435,16),
      to_signed(19432,16),to_signed(19432,16),
      to_signed(19432,16),to_signed(19432,16),
      to_signed(19432,16),to_signed(19432,16),
      to_signed(19432,16),to_signed(19432,16),
      to_signed(19432,16),to_signed(19432,16));

   signal i : natural range 0 to 16;
   signal alpha,x1,y1 : signed(15 downto 0);

begin
   process (CLK,RST)
   begin
      if RST ='1' then 
         etat <= Repos;
         RDY <= '1';
      elsif rising_edge(CLK) then
         case etat is
            when Repos =>
               if START = '1' then
                  RDY <= '0';
                  x1 <= A(N-1);
                  y1 <= to_signed(0,16);
                  alpha <= to_signed(0,16);
                  i <= 0;
                  etat <= Calcul;
               end if;
            
            when Calcul =>
                  if (i < N) then
                     if (alpha < phi) then
                        x1 <= x1 - shift_right(y1, i);
                        y1 <= y1 + shift_right(x1, i);
                        alpha <= alpha + THETA(i);
                     else 
                        x1 <= x1 + shift_right(y1, i);
                        y1 <= y1 - shift_right(x1, i);
                        alpha <= alpha - THETA(i);
                     end if;
                     i <= i + 1;
                        
                  else
                     RDY <= '1';
                     R1 <= x1;
                     R2 <= y1;
                     etat <= Repos;
                  end if;
         end case;
      end if;
   end process;
end architecture;

