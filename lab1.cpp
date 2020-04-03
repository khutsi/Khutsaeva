#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;
int main()
{
	string id = "968247916";
	float in = 1;  // объявление стоимости услуг в соотвествии с вариантом 
	float out = 3;
	float sms = 1;
	float cost_tel = 0;  // конечная стоимость звонков 
	float cost_sms = 0;
	ifstream file("data.csv"); // чтение данных из файла
	string str;
    getline(file, str);    // запись из файла в str
	while(true) { 
		string datetime; 
                string origin;
		string target;
		string time_str;
		string count_sms_str;
		float time;
		int count_sms;
		getline(file,datetime,','); 
		getline(file,origin,',');  // запись из файла в origin до запятой
		getline(file,target,',');
		getline(file,time_str,',');
		getline(file,count_sms_str);
    	if(!file.eof()){
			time = stof(time_str);
			count_sms = stoi(count_sms_str);
			if(origin == id){
				cost_sms += count_sms*sms;  // стоимость смс
				cost_tel += time*out;      // стоимость исходящих звонков
			}
			if(target == id){
				cost_tel += time*in;     // стоимость входящих звонков 
			}
		}
    	else break;
    }
    cout << "Стоимость звонков: " << cost_tel << " руб." << endl;
    cout << "Стоимость СМС: " << cost_sms << " руб." << endl;
    cout << "Сумма по счету равна: " << cost_tel + cost_sms << " руб." << endl;


   ofstream result;  //  вывод результа в отдельный файл result.txt
   result.open("resut.txt");
     {
       result << "Сумма по счету равна: " << cost_tel + cost_sms << " руб." << endl;
        
     }

	return 0;
 
}
