function [y,ny]=conv_m(x,nx,h,nh)
ny1=nx(1)+nh(1);ny2=nx(length(x))+nh(length(h));
ny=[ny1:ny2];
y=conv(x,h)
