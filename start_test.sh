cd 'check-0.15.2'
./configure
make
make check
make install
cd ..
make fclean
make test
./test
