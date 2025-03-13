module adder (A,B,CI,S,CO);
input A,B,CI;
output S,CO;
// 行为描述
always @(A or B or CI) begin
    {CO, S} = A + B + C
end


// 数据流描述
// S = A ⊕ B ⊕ CI
assign S = A ^ B ^ CI;

// CO = AB + (A+B)CI
assign CO = (A & B) | ((A ^ B) & CI);


// 基元例化描述
wire w1, w2, w3
xor g1(w1, A, B)
xor g2(S, w1, CI)
and g3(w2, A, B)
and g4(w3, w1, CI)
or  g5(CO, w2, w3)

endmodule