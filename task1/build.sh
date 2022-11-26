mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../.
make -j 8
mv task1 ../
cd ..