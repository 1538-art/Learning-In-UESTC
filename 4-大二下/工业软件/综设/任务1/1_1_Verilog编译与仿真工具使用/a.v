module justinv (a1,q1);
input a1;
output reg q1;
always @(a1)
    q1 = ~a1 ;
endmodule
