close all
clear all
clc

% data = csvread('dataset.csv');
% 
% i = data(:,1);
% output = data(:,2);
% target = data(:,3);
% 
% % figure('name','data')
% % hold on
% % plot(output,'r')%target trajectory
% % plot(target,'b')%learnt trajectory
% 
% kernels = csvread('datasetKernels.csv');
% 
% figure('name','kernels')
% hold on
% plot(kernels','r')%kernels
% 
% lefthip = csvread('runbot_lefthip_output.log');
% righthip = csvread('runbot_righthip_output.log');
% leftknee = csvread('runbot_leftknee_output.log');
% rightknee = csvread('runbot_rightknee_output.log');
% 
% figure('name','lefthip')
% hold on
% plot(lefthip);
% 
% figure('name','righthip')
% hold on
% plot(righthip);
% 
% figure('name','leftknee')
% hold on
% plot(leftknee);
% 
% figure('name','rightknee')
% hold on
% plot(rightknee);
% % 
% lefthipOut = lefthip(:,1082:1139);
% righthipOut = righthip(:,1250:1303);
% leftkneeOut = leftknee(:,1331:1388);
% rightkneeOut = rightknee(:,1590:1650);
% 
% figure('name','lefthipOut')
% hold on
% plot(lefthipOut);
% 
% figure('name','righthipOut')
% hold on
% plot(righthipOut);
% 
% figure('name','leftkneeOut')
% hold on
% plot(leftkneeOut);
% 
% figure('name','rightkneeOut')
% hold on
% plot(rightkneeOut);
% 
% lefthipOut=interp1(1:length(lefthip(:,1082:1139)),lefthip(:,1082:1139),1:0.05:length(lefthip(:,1082:1139)),'pchip');
% righthipOut=interp1(1:length(righthip(:,1250:1303)),righthip(:,1250:1303),1:0.05:length(righthip(:,1250:1303)),'pchip');
% leftkneeOut=interp1(1:length(leftknee(:,1331:1388)),leftknee(:,1331:1388),1:0.05:length(leftknee(:,1331:1388)),'pchip');
% rightkneeOut=interp1(1:length(rightknee(:,1590:1650)),rightknee(:,1590:1650),1:0.05:length(rightknee(:,1590:1650)),'pchip');
% 
% csvwrite('runbot_lefthip_cycle', lefthipOut);
% csvwrite('runbot_righthip_cycle', righthipOut);
% csvwrite('runbot_leftknee_cycle', leftkneeOut);
% csvwrite('runbot_rightknee_cycle', rightkneeOut);


% 
% lefthip_output_target = csvread('interp_lefthip_10times.csv');
% righthip_output_target = csvread('interp_righthip_10times.csv');
% leftknee_output_target = csvread('interp_leftknee_10times.csv');
% rightknee_output_target = csvread('interp_rightknee_10times.csv');
% 
% lefthip_output = lefthip_output_target(:,2);
% righthip_output = righthip_output_target(:,2);
% leftknee_output = leftknee_output_target(:,2);
% rightknee_output = rightknee_output_target(:,2);
% 
% lefthip_target = lefthip_output_target(:,3);
% righthip_target = righthip_output_target(:,3);
% leftknee_target = leftknee_output_target(:,3);
% rightknee_target = rightknee_output_target(:,3);
% 
% figure('name','lefthip_output_target')
% hold on
% plot(1:10*10:10*10*length(lefthip_output),lefthip_output, 'r');
% plot(1:10*10:10*10*length(lefthip_target),lefthip_target, 'b');
% title('Left hip CPU');
% xlabel('time/ms');
% ylabel('Motor output');
% legend('Resulting Trajectory','Target Trajectory');
% 
% figure('name','righthip_output_target')
% hold on
% plot(1:10*10:10*10*length(righthip_output),righthip_output, 'r');
% plot(1:10*10:10*10*length(righthip_target),righthip_target, 'b');
% title('Right hip CPU');
% xlabel('time/ms');
% ylabel('Motor output');
% legend('Resulting Trajectory','Target Trajectory');
% 
% figure('name','leftknee_output_target')
% hold on
% plot(1:10*10:10*10*length(leftknee_output),leftknee_output, 'r');
% plot(1:10*10:10*10*length(leftknee_target),leftknee_target, 'b');
% title('Left knee CPU');
% xlabel('time/ms');
% ylabel('Motor output');
% legend('Resulting Trajectory','Target Trajectory');
% 
% figure('name','rightknee_output_target')
% hold on
% plot(1:10*10:10*10*length(rightknee_output),rightknee_output, 'r');
% plot(1:10*10:10*10*length(rightknee_target),rightknee_target, 'b');
% title('Right knee CPU');
% xlabel('time/ms');
% ylabel('Motor output');
% legend('Resulting Trajectory','Target Trajectory');
%kernels/width(100/2,200/2,300/2,400/2,500/2,600/2,700/2,800/2,900/2,1000/2)
% cputime = [5.91,11.66,17.04,24.48,31.17,38.45,55.37,70.53,84.13];
% gputime = [2.08,3.60,4.78,6.27,8.67,10.54,12.67,14.28,15.95];
% kernels = [100,200,300,400,500,600,700,800,900];
% 
% % figure('name','rightknee_output_target')
% % hold on
% % plot(kernels,cputime, 'r');
% % plot(kernels,gputime, 'b');
% % title('Runtime of CPU vs GPU');
% % xlabel('Number of kernels');
% % ylabel('Runtime/s');
% % legend('CPU','GPU');
% 
% figure('name','plot')
% hold on
% scatter(kernels,cputime, 'r');
% scatter(kernels,gputime, 'b');
% fplot(@(x) 8.917e-05*x^2+0.007514*x+5.643, 'r');
% fplot(@(x) 3.38e-06*x^2+0.01455*x+0.4155, 'b');
% title('Runtime of CPU vs GPU');
% xlabel('Number of kernels');
% ylabel('Runtime/s');
% legend('CPU','GPU','f(x)=8.917e-05*x^2+0.007514*x+5.643','f(x)=3.38e-06*x^2+0.01455*x+0.4155');

lefthip_output_target = csvread('repeatingPattern.csv');

lefthip_output = lefthip_output_target(:,2);

figure('name','lefthip_output_target')
hold on
plot(1:10:10*length(lefthip_output),lefthip_output, 'r');
title('Left hip CPU repeating pattern');
xlabel('time/ms');
ylabel('Motor output');
legend('Framework output');


