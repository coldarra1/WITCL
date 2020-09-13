function Xk=dft(xn,N)
n=[0:N-1];
k=[0:N-1];
Wn=exp(-j*2*pi/N);
nk=n'*k;
Wnnk=Wn.^nk;
Xk=xn*Wnnk;
end