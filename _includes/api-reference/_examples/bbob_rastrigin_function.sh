#!/bin/sh
if [[ "$(uname -o)" = "Msys" ]]; then
  c++ -std=c++11 bbob_rastrigin_function.cpp -LC:/Programme/OpenBLAS/lib -lopenblas -IC:/Programme/Armadillo/include -IC:/Programme/Mantella/include -o bbob_rastrigin_function
  ./bbob_rastrigin_function.exe
  rm bbob_rastrigin_function.exe
else
  ./bbob_rastrigin_function.core.sh
  rm bbob_rastrigin_function
fi

rm bbob_rastrigin_function_surface.png bbob_rastrigin_function_contour.png 2> /dev/null 
matlab -nodisplay -nosplash -nodesktop -r "run('./bbob_rastrigin_function.m');exit;"

while [[ ! -s bbob_rastrigin_function_surface.png || ! -s bbob_rastrigin_function_contour.png ]]; do
  sleep 2
done
sleep 5

rm X.mat Y.mat Z.mat
mv bbob_rastrigin_function_surface.png bbob_rastrigin_function_contour.png ../../../assets/images/api-reference/