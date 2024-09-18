libs="src"
includes="$libs/main.cpp $libs/item.cpp"
clang++ -static -I"$libs" $includes -o "main.exe"
