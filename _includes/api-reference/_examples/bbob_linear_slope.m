% Loading samples
X = dlmread('X.mat');
Y = dlmread('Y.mat');
Z = dlmread('Z.mat');

% Generates a surface plot
surf(X, Y, Z);
shading interp;
title('BBOB Linear slope - surface plot');
xlabel('x_1');
ylabel('x_2');
zlabel('f(x_1, x_2)');
view(-35, 35);
colorbar;
print('bbob_linear_slope_surface','-dpng');

% Generates a contour plot
contour(X, Y, Z);
title('BBOB Linear slope - contour plot');
xlabel('x_1');
ylabel('x_2');
colorbar;
print('bbob_linear_slope_contour','-dpng');