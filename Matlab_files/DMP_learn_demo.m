
close all
clear all
clc

t=0:0.001:1; %movement duration from 0 to 1 sec
target=sin(2*pi*t); %target movement pattern
N=length(target); %number of points in the movement trajectory

figure('name','Target trajectory')
hold on
plot(t,target,'r')

n=20; %number of Gaussian kernels
s=0.025; %width of Gaussian kernels
w=zeros(1,n);%initial weights
lr=0.2; %learning rates
M=100; %number of iterations for learning

lower_limit=45;%joint angle limits
upper_limit=180;

c=linspace(lower_limit,upper_limit,n); %setting centers of kernels within 45 and 180 degrees
alfa=linspace(lower_limit,upper_limit,N); %changing alfa from 45 to 180 by (180-45)/N
for k=1:n %generating gaussian kernels
     psi(k,:)=exp(-(alfa-c(k)).^2/2*s);
end;

figure('name','Gaussian kernels')
plot(alfa,psi)

%Learning weights of Gaussian kernels using Delta rule
ind=round(linspace(1,N,n));
for i=1:M
    y=[psi'*w']'; %calculating motor output
    w=w+lr*(target(ind)-y(ind)); %updating weights
end;

figure('name','Target and learnt trajectories')
hold on
plot(alfa,target,'r')%target trajectory
plot(alfa,y,'b')%learnt trajectory
legend('target','learnt')




