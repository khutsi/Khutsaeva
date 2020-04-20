#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

/*
 * get_tarif() - читает файл с описанием тарифа и возвращает структуру с данными о нем.
 * Пример файла:
 * ip: 217.15.20.194
 * k: 1
 * firstfree: 1000
 */

struct s_tarif{
    string ip;
    int k;
    int firstfree;
};

s_tarif get_tarif(ifstream* stream){
    s_tarif tarif;
    string a;
    {
        getline(*stream, a);
        std::istringstream buf(a);
        std::istream_iterator<std::string> beg(buf), end;
        std::vector<std::string> tokens(beg, end);
        tarif.ip = tokens[1];
    }
    {
        getline(*stream, a);
        std::istringstream buf(a);
        std::istream_iterator<std::string> beg(buf), end;
        std::vector<std::string> tokens(beg, end);
        tarif.k = stoi(tokens[1]);
    }
    {
        getline(*stream, a);
        std::istringstream buf(a);
        std::istream_iterator<std::string> beg(buf), end;
        std::vector<std::string> tokens(beg, end);
        tarif.firstfree = stoi(tokens[1])*128;
    }
    return tarif;
}

/*
 * process() читает строку из файла и возвращает 0 если ip не совпадает с данным в тарифе,
 * количество байт в пакете если совпадает и -1 если файл закончился
 */

int process(ifstream* stream, string* target_ip, ofstream* forpython){
    string str;
    if(getline(*stream, str)) {
        std::istringstream buf(str);
        std::istream_iterator<std::string> beg(buf), end;
        std::vector<std::string> tokens(beg, end);
        if (tokens[0]=="Summary:")
            return -1;
        string ip = tokens[7].substr(0, tokens[7].find_first_of(':'));
//        std::cout << '"' << ip << " " << tokens[11] << '"' << '\n';
        int bytes = stoi(tokens[11]);
//        std::cout << '"' << ip << " " << bytes << '"' << '\n';
        if (ip == *target_ip) {
	    *forpython << tokens[0] << " " << tokens[1] << " ";
            return bytes;
        } else {
            return 0;
        }
    }else{
        return -1;
    }
}

int main() {
    string s;
    ifstream inf("data");
    ofstream forpython("forplot");
    ifstream tarif_file("tarif");
    s_tarif tarif = get_tarif(&tarif_file);
    getline(inf, s);
    int fullsumm = 0;
    int firstfree = 0;
    int counter = 0;
    while(true) {
        int packet_size = process(&inf, &tarif.ip, &forpython);
        if (packet_size == -1) {
            break;
        }
	fullsumm += packet_size;
        if (firstfree == -1) {
            counter += packet_size;
	    if(packet_size>0)
	        forpython << packet_size<< endl;

        } else {
            firstfree += packet_size;
	    if(packet_size>0)
	        forpython << packet_size << endl;
        }
        if (firstfree >= tarif.firstfree) {
            firstfree = -1;
        }
    }
    cout << (double) counter / 131072 * tarif.k << endl;
    system("python3 plot.py");
    inf.close();
    forpython.close();
    tarif_file.close();
    return 0;
}
