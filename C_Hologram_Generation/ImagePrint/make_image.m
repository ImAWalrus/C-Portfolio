clear
clc

filename = 'test3.csv';
M = csvread(filename)
imwrite(M,'hologram8C.png');

