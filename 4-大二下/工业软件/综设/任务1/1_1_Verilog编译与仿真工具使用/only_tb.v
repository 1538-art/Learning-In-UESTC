`timescale 1ns/1ns
 
module a_tb_main;
	reg	a;
  
initial begin	
	a = 0;
	#200	
		$stop(0);			
end
 
always #10 a = {$random} % 2;
	
initial
begin            
    $dumpfile("wave.vcd");        //���ɵ�vcd�ļ�����
    $dumpvars(0, a_tb_main);    //tbģ������
end

endmodule