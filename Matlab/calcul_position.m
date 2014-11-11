% -------------------------------
% Calcul position 
% Written by Luc Fourtinon
% -------------------------------

function[]=calcul_position()

%pas=0;
N=100;
s=zeros(1,N);
s(1)=1;
for i = 2 : N
   s(i) = s(i-1)+1;
end

x=[0,1,0];
x1=[2,2,2];
y=[0,1,1];
z=[0,1,0];
subplot(2,1,1);
plot(s)
subplot(2,1,2);
plot3(x,y,z)
end