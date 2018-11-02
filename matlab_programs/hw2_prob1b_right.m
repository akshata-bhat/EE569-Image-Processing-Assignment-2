clc;
clear all;

[Img1] = imread('embedded_middle.png');
%imshow(Img1);

[Img2] = imread('right.png');
%imshow(Img2);

cpselect(Img1,Img2)
%moving points


% Embedded Image
x0=974.000000000000;
x1=1183.93750000000;
x2=979.031250000000;
x3=1111.84375000000;
y0=522.031250000000;
y1=693.781250000000;
y2=860.031250000000;
y3=900.015625000000;

%Left image
u0=53.0312500000000;
u1=258.718750000000;
u2=61.0312500000000;
u3=194.906250000000;
v0=195.906250000000;
v1=368.093750000000;
v2=550.015625000000;
v3=570.210937500000;

A = [u0 v0 1 0 0 0 -(u0*x0) -(v0*x0);
     0 0 0 u0 v0 1 -(u0*y0) -(v0*y0);
     u1 v1 1 0 0 0 -(u1*x1) -(v1*x1);
     0 0 0 u1 v1 1 -(u1*y1) -(v1*y1);
     u2 v2 1 0 0 0 -(u2*x2) -(v2*x2);
     0 0 0 u2 v2 1 -(u2*y2) -(v2*y2);
     u3 v3 1 0 0 0 -(u3*x3) -(v3*x3);
     0 0 0 u3 v3 1 -(u3*y3) -(v3*y3)];

 B = [x0; y0; x1; y1; x2; y2; x3; y3];
 
 H_initial = A\B;
 
 H_final = [H_initial(1) H_initial(2) H_initial(3);
            H_initial(4) H_initial(5) H_initial(6);
            H_initial(7) H_initial(8) 1];
 
format long;
H_inverse = inv(H_final)
