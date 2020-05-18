#! /usr/bin/env python
# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
from openpyxl import load_workbook
import datetime
from num2words import num2words
import os

# Загружаем данные из файлов 

list_prices = []

with open('lab1_output.txt') as f:
    for i in f.readlines():
        list_prices.append(float(i.split(' ')[-2]))

with open('lab2_output.txt') as f:
    for i in f.readlines():
        list_prices.append(float(i.split(' ')[-2]))


# Меняем excel 

wb = load_workbook('template.xlsx')
sheet = wb.active


sheet['B2'].value='ПАО "Банк "Санкт-Петербург", г. Санкт-Петербург'
sheet['E5'].value='1234875853423' # иНН
sheet['O5'].value='59245982347598' # КПП
sheet['AD2'].value='2458249505' # БИК
sheet['B6'].value='Иванов Иван Иванович'
sheet['AD3'].value='2354245432'
sheet['AD5'].value='4325346235'
sheet['G14'].value='Иванов Иван Иванович, ИНН: 1234875853423, КПП: 59245982347598,\n141980, г.Дубна, ул. Мичурина, 29'
sheet['G17'].value= 'Петров Петр Петрович, ИНН: 34562456135, КПП: 4123537457357,\n141980, г.Дубна, ул. Сахарова, 23'
sheet['B10'].value= 'Счет на оплату № 38 от '+ str(datetime.datetime.now().strftime("%d-%m-%Y"))

sheet['Y23'].value='1'
sheet['Y24'].value='1'
sheet['Y25'].value='1'
sheet['AC23'].value='шт'
sheet['AC24'].value='шт'
sheet['AC25'].value='шт'
sheet['D23'].value='Звонки'
sheet['D24'].value='СМС'
sheet['D25'].value='Интернет'
sheet['AF23'].value=list_prices[0]
sheet['AF24'].value=list_prices[1]
sheet['AF25'].value=list_prices[3]
sheet['AK23'].value=list_prices[0]
sheet['AK24'].value=list_prices[1]
sheet['AK25'].value=list_prices[3]

summ = list_prices[0] + list_prices[1] + list_prices[3]

sheet['AL27'].value=str(round(summ, 2))+" руб."
sheet['AL28'].value=str(round(summ*0.2, 2))+" руб."
sheet['AL29'].value=str(round(summ*1.2, 2))+" руб."

sheet['M39'].value='Сидоров И.О.'
sheet['AJ39'].value='Сидорова К. Н.'

sheet['B30'].value='Всего наименований 3, на сумму {} руб.'.format(round(summ*1.2, 2))
sheet['B31'].value=num2words(int((summ*1.2)), lang='ru') + ' рублей, ' + num2words(str(int(round(summ*1.2, 2)*100%100)), lang='ru') + ' копеек'

wb.save('result.xlsx')

# для работы нужен libreoffice calc
# на ubuntu он ставится такой командой
# sudo apt-get install libreoffice-calc

os.system("libreoffice --headless --invisible --convert-to pdf result.pdf result.xlsx >/dev/null 2>&1 ") 

