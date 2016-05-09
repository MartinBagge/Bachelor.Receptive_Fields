

close all
clear all
clc


target=csvread('runbot_leftknee_output.log');
N=length(target); %number of points in the movement trajectory

% target=interp1(1:N,target,1:0.05:N,'pchip');
% N=length(target);
% 
% 
% 
% for i=1:9
%     targetNew=(tmp(90:end,i))';
%     NWrite=length(targetNew);
%     targetWrite(:,i)=(interp1(1:NWrite,targetNew,1:0.05:NWrite,'pchip'))';
% end;
% csvwrite('runbot_data_multiplied.log', targetWrite);

 
 figure('name','Target trajectory')
 hold on
 plot(target,'r')
 
n=40; %number of Gaussian kernels
s=0.1; %width of Gaussian kernels
w=zeros(1,n);%initial weights
lr=0.4; %learning rates
M=50000; %number of iterations for learning


c=linspace(1,N,n); %setting centers of kernels within 45 and 180 degrees
t=1:N; %changing alfa from 45 to 180 by (180-45)/N
for k=1:n %generating gaussian kernels
     psi(k,:)=exp((-(t-c(k)).^2/2)*s);
end;
% for i=1:N %normalisation
%     psi(:,i)=psi(:,i)/sum(psi(:,i));
% end;

figure('name','Gaussian kernels')
plot(psi')

%Learning weights of Gaussian kernels using Delta rule
ind=round(linspace(1,N,n));
for i=1:M
    y=[psi'*w']'; %calculating motor output
    w=w+lr*(target(ind)-y(ind)); %updating weights
end;

y=[psi'*w']';

figure('name','Target and learnt trajectories')
hold on
plot(target,'r')%target trajectory
plot(y,'b')%learnt trajectory
legend('target','learnt')
% 
% t=0;
% for k=1:1500
%     t=t+1;
%     psi=exp(-(t-c).^2/2*s);
%     m(k)=psi*w';
%     if t==N
%         t=0;
%     end;
% end;
% 
% figure
% plot(m,'b')
    


