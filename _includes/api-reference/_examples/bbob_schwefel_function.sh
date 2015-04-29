#!/bin/sh
if [[ "$(uname -o)" = "Msys" ]]; then
  c++ -std=c++11 bbob_schwefel_function.cpp -LC:/Programme/OpenBLAS/lib -lopenblas -IC:/Programme/Armadillo/include -IC:/Programme/Mantella/include -o bbob_schwefel_function
  ./bbob_schwefel_function.exe
  rm bbob_schwefel_function.exe
else
  ./bbob_schwefel_function.core.sh
  rm bbob_schwefel_function
fi

rm bbob_schwefel_function_surface.png bbob_schwefel_function_contour.png 2> /dev/null 
matlab -nodisplay -nosplash -nodesktop -r "run('./bbob_schwefel_function.m');exit;"

while [[ ! -s bbob_schwefel_function_surface.png || ! -s bbob_schwefel_function_contour.png ]]; do
  sleep 2
done
sleep 5

rm X.mat Y.mat Z.mat
mv bbob_schwefel_function_surface.png bbob_schwefel_function_contour.png ../../../assets/images/api-reference/