------------------------------------------------------------------------------------------------
--
-- Copyright (C) 2010-: Madhav P. Desai
-- All Rights Reserved.
--  
-- Permission is hereby granted, free of charge, to any person obtaining a
-- copy of this software and associated documentation files (the
-- "Software"), to deal with the Software without restriction, including
-- without limitation the rights to use, copy, modify, merge, publish,
-- distribute, sublicense, and/or sell copies of the Software, and to
-- permit persons to whom the Software is furnished to do so, subject to
-- the following conditions:
-- 
--  * Redistributions of source code must retain the above copyright
--    notice, this list of conditions and the following disclaimers.
--  * Redistributions in binary form must reproduce the above
--    copyright notice, this list of conditions and the following
--    disclaimers in the documentation and/or other materials provided
--    with the distribution.
--  * Neither the names of the AHIR Team, the Indian Institute of
--    Technology Bombay, nor the names of its contributors may be used
--    to endorse or promote products derived from this Software
--    without specific prior written permission.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
-- OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
-- MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
-- IN NO EVENT SHALL THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR
-- ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
-- TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
-- SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE SOFTWARE.
------------------------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

library ahir;
use ahir.Types.all;
use ahir.Subprograms.all;
use ahir.Utilities.all;

entity InputPortLevel is
  
  generic (name: string;
	num_reqs: integer := 5; 
	data_width: integer := 8;  
	no_arbitration: boolean := false);
  port (
    -- ready/ready interface with the requesters
    req       : in  std_logic_vector(num_reqs-1 downto 0);
    ack       : out std_logic_vector(num_reqs-1 downto 0);
    data      : out std_logic_vector((num_reqs*data_width)-1 downto 0);
    -- ready/ready interface with outside world
    oreq       : out std_logic;
    oack       : in  std_logic;
    odata      : in  std_logic_vector(data_width-1 downto 0);
    clk, reset : in  std_logic);
  
end InputPortLevel;

architecture default_arch of InputPortLevel is

  
  type IPWArray is array(integer range <>) of std_logic_vector(data_width-1 downto 0);
  signal data_final, data_reg : IPWArray(num_reqs-1 downto 0);
  signal req_active, ack_sig  : std_logic_vector(num_reqs-1 downto 0); 
  
  
begin  -- default_arch

  oreq <= OrReduce(req_active);

  NoArb: if no_arbitration generate
    req_active <= req;
  end generate NoArb;

  Arb: if not no_arbitration generate
    req_active <= PriorityEncode(req);
  end generate Arb;

  process(data_final)
    variable ldata: std_logic_vector((num_reqs*data_width)-1 downto 0);
  begin

    for J in 0 to num_reqs-1 loop
       ldata(((J+1)*data_width)-1 downto (J*data_width)) := data_final(J);
    end loop;

    data <= ldata;
  end process;

  gen: for I in num_reqs-1 downto 0 generate

    SingleReq: if (num_reqs = 1) generate 
    	ack_sig(I) <=  oack; 
    end generate SingleReq;

    MultipleReqs: if (num_reqs > 1) generate
    	ack_sig(I) <= req_active(I) and oack; 
    end generate MultipleReqs;
    
    ack(I) <= ack_sig(I);
    
    data_final(I) <= odata;
    
  end generate gen;

end default_arch;
