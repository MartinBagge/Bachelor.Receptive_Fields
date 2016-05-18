
close all
clear all
clc

t=0:0.001:0.5; %movement duration from 0 to 1 sec
yt=sin(2*pi*t+1.5*pi)+1; %target movement pattern
yt=[yt 2*ones(1,1000) 2-yt];
target=diff(yt);

N=length(target); %number of points in the movement trajectory

figure('name','Target trajectory')
hold on
plot(yt,'r')

n=5000; %number of Gaussian kernels
s=0.5; %width of Gaussian kernels
w=zeros(1,n);%initial weights
lr=2; %learning rates
M=20000; %number of iterations for learning

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

y=[psi'*w']';

figure('name','Target and learnt trajectories')
hold on
plot(alfa,cumsum(target),'r')%target trajectory
plot(alfa,cumsum(y),'b')%learnt trajectory
legend('target','learnt')


a=45;
m(1)=0;
ph=1;
for k=1:50000
    psi=exp(-(a-c).^2/2*s);
    m(k+1)=m(k)+psi*w';
    a = a+ph*(upper_limit-lower_limit)/N;    
    if a>=180
        ph=ph*(-1);
    end;
    if a<=45
        ph=ph*(-1);
    end;
    

end;

figure
plot(m,'b')

    



