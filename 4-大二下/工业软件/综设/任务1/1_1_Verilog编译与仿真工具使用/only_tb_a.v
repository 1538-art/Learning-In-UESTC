`timescale 1ns/1ns

module justinv (a1,q1);
input a1;
output reg q1;
always @(a1)
    q1 = ~a1 ;
endmodule
 
module a_tb_main;
	reg	a;
  wire q;
    
initial begin	
	a = 0;
	#200	
		$stop(0);			
end
 
always #10 a = {$random} % 2;
	
initial
begin            
    $dumpfile("wave.vcd");        //生成的vcd文件名称
    $dumpvars(0, a_tb_main);    //tb模块名称
end

justinv f1(
            .a1(a),
            .q1(q)
           );

endmodule

