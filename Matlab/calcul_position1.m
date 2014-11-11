% -------------------------------
% Calcul position 1
% Written by Luc Fourtinon
% -------------------------------

function[]=calcul_position1(pas)
%calcul des points accessibles par le robot

%longueur des bras
a=17.5;
b=17.5;
c=2.6;

%les angles ont des contraintes en degres

%le premier angle(base) va de 60° à 240°
%le deuxième angle va de -15° à +105°
%le troixième va de -15° à +105°

%%%attention dans matlab les angles sont définis en radian%%%

%Le calcul des coordonnées l,m et n par le modèle direct nous donne les équations
%suivantes :
N1 = floor((105*pi/180+15*pi/180)/pas);
N2 = floor((240*pi/180-60*pi/180)/pas);
mini = min(N1,N2);
l = zeros(N1*N2,1);
m = zeros(N1*N2,1);
n = zeros(N1*N2,1);
i=1;
j=1;
r=1;
j=1;
k=1;
z=0;
for y = -15*pi/180 : pas : 105*pi/180
 for i = j:j+N2   
 %for i=r:N2*k+z
l(i) = c+b*sin(y);
  end
    
    for x= 60*pi/180 : pas : 240*pi/180
    m(j) = cos(x)*(a+b*cos(y));
    n(j) = 4+(a+b*cos(y))*sin(x);j=j+1;
    end
    
 
r=r+N2+z;
   k=k+1;
   z=z+1;
end
length(l)
length(m)

figure();
plot(l);
figure();
plot(m);
figure();
plot(n);
figure();
plot3(l,m,n)
grid;
xlabel('axe x');
ylabel('axe y');
zlabel('axe z');
end