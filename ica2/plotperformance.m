clear 
close all
clc
p1=load('data_naive_1.csv');
p2=load('data_O3.csv');
N=size(p1,1);
reps=15;
n=N/reps;
z1=zeros(n,2);
z2=zeros(n,2);
for i=1:n
    s1=reps*(i-1)+1;
    s2=reps*i;
    z1(i,1)=p1(s1,1);
    z1(i,2)=mean(p1(s1:s2,2));
    z1(i,2)=2*z1(i,1)^3./z1(i,2);
end
for i=1:n
    s1=reps*(i-1)+1;
    s2=reps*i;
    z2(i,1)=p2(s1,1);
    z2(i,2)=mean(p2(s1:s2,2));
    z2(i,2)=2*z2(i,1)^3./z2(i,2);
    z2(i,1)=z2(i,1);
end
z1(:,2)=z1(:,2)./1000000;
z2(:,2)=z2(:,2)./1000000;

plot(z1(:,1),z1(:,2),'--og')
grid on
grid on
hold on 
plot(z2(:,1),z2(:,2),'-ob');
legend('O0','O3')
hold off
title('Matrix-Matrix Multiplication Performance');
xlabel('Dimensions of Matrices(N)')
ylabel('MFLops')
