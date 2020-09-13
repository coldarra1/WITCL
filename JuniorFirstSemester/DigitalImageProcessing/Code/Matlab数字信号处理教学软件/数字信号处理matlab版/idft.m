function  xn=idft(Xk,N)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
n=[0:1:N-1];
k=[0:1:N-1];
Wn=exp(-j*2*pi/N);
nk=n'*k;
Wnnk=Wn.^(-nk);
xn=Xk*Wnnk/N;

end

