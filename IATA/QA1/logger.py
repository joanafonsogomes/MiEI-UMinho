import csv
import logging
import sys
import argparse
from datetime import date,datetime

##### create csv with no duplicates #####
with open('anexo.csv','r') as infile, open('anexo_norep.csv','w') as outfile:
    seen = set()
    for line in infile:
        if line in seen: continue

        seen.add(line)
        outfile.write(line)


###### set results to print to log file #####
logger = open ("result.log","w")
sys.stdout = logger

###### set dates for beginning of seasons #####
spring = datetime.strftime((datetime.strptime('03-20','%m-%d')),'%m-%d')
summer = datetime.strftime((datetime.strptime('06-20','%m-%d')),'%m-%d')
fall = datetime.strftime((datetime.strptime('09-22','%m-%d')),'%m-%d')
winter = datetime.strftime((datetime.strptime('12-21','%m-%d')),'%m-%d')

###### log file content #####
with open('anexo_norep.csv', 'r') as file:

    reader = csv.reader(file, delimiter = ',')

    listRead = list(reader)

    print()

    for row in listRead[1:]:
        temp = row[4]
        humidity = row[5]
        dateandhour = datetime.strptime(row[0], '%Y-%m-%d %H:%M:%S')
        day_month = datetime.strftime(dateandhour, '%m-%d')
        #if spring
        if (day_month >= spring) and (day_month<summer):
            #Temp
            difTemp = round((23.0 - float(temp)),2)
            if difTemp>0 :
                ac = "airconditioning+" + str(difTemp) + "ºC"
            else:
                ac = "airconditioning-" + str(-difTemp) + "ºC"
            #Humidity
            difHum = 40 - int(humidity)
            if(difHum > 0) :
                hum = "humidifier+" + str(difHum) + "%"
            else:
                hum = "humidifier-" + str(-difHum) + "%"
        #if summer
        if (day_month >= summer) and (day_month<fall):
            #Temp
            difTemp = round((25.0 - float(temp)),2)
            if difTemp>0 :
                ac = "airconditioning+" + str(difTemp) + "ºC"
            else:
                ac = "airconditioning-" + str(-difTemp) + "ºC"
            #Humidity
            difHum = 45 - int(humidity)
            if(difHum > 0) :
                hum = "humidifier+" + str(difHum) + "%"
            else:
                hum = "humidifier-" + str(-difHum) + "%"
        #if fall
        if (day_month >= fall) and (day_month<winter):
            #Temp
            difTemp = round((20.0 - float(temp)),2)
            if difTemp>0 :
                ac = "airconditioning+" + str(difTemp) + "ºC"
            else:
                ac = "airconditioning-" + str(-difTemp) + "ºC"
            #Humidity
            difHum = 40 - int(humidity)
            if(difHum > 0) :
                hum = "humidifier+" + str(difHum) + "%"
            else:
                hum = "humidifier-" + str(-difHum) + "%"
        #if winter
        if (day_month >= winter) or (day_month<spring):
            #Temp
            difTemp = round((17.0 - float(temp)),2)
            if difTemp>0 :
                ac = "airconditioning+" + str(difTemp) + "ºC"
            else:
                ac = "airconditioning-" + str(-difTemp) + "ºC"
            #Humidity
            difHum = 35 - int(humidity)
            if(difHum > 0) :
                hum = "humidifier+" + str(difHum) + "%"
            else:
                hum = "humidifier-" + str(-difHum) + "%"
        #Print line data
        print("%-25s %-4s %s" %(ac, "|" ,hum))
