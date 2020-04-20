echo "Making input files"
rm forplot plot.png
nfdump -r nfcapd.202002251200 > data
echo -e "ip: 217.15.20.194\nk: 1\nfirstfree: 1000" > tarif
echo -e "Installing dependencies for plotting"
echo "Compiling"
g++ -o lab2.out main.cpp
echo "Computing"
./lab2.out
