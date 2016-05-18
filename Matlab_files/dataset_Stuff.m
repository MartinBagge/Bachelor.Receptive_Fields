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
lefthip = csvread('runbot_lefthip_output.log');
righthip = csvread('runbot_righthip_output.log');
leftknee = csvread('runbot_leftknee_output.log');
rightknee = csvread('runbot_rightknee_output.log');
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
lefthipOut=interp1(1:length(lefthip(:,1082:1139)),lefthip(:,1082:1139),1:0.05:length(lefthip(:,1082:1139)),'pchip');
righthipOut=interp1(1:length(righthip(:,1250:1303)),righthip(:,1250:1303),1:0.05:length(righthip(:,1250:1303)),'pchip');
leftkneeOut=interp1(1:length(leftknee(:,1331:1388)),leftknee(:,1331:1388),1:0.05:length(leftknee(:,1331:1388)),'pchip');
rightkneeOut=interp1(1:length(rightknee(:,1590:1650)),rightknee(:,1590:1650),1:0.05:length(rightknee(:,1590:1650)),'pchip');

csvwrite('runbot_lefthip_cycle', lefthipOut);
csvwrite('runbot_righthip_cycle', righthipOut);
csvwrite('runbot_leftknee_cycle', leftkneeOut);
csvwrite('runbot_rightknee_cycle', rightkneeOut);


% 
% lefthip_output_target = csvread('lefthip_target-output.csv');
% righthip_output_target = csvread('righthip_target-output.csv');
% leftknee_output_target = csvread('leftknee_target-output.csv');
% rightknee_output_target = csvread('rightknee_target-output.csv');
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
% plot(lefthip_output, 'r');
% plot(lefthip_target, 'b');
% 
% figure('name','righthip_output_target')
% hold on
% plot(righthip_output, 'r');
% plot(righthip_target, 'b');
% 
% figure('name','leftknee_output_target')
% hold on
% plot(leftknee_output, 'r');
% plot(leftknee_target, 'b');
% 
% figure('name','rightknee_output_target')
% hold on
% plot(rightknee_output, 'r');
% plot(rightknee_target, 'b');