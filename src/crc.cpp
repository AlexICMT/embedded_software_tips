/* help_cpp
 * /help_cpp/src/crc.cpp
 * crc.cpp
 * 
 *  Created on: 14 мар. 2022 г.
 *  	  Time: 15:39:03
 *      Author: AlexICMT
 */

#include <iostream>
#include <vector>
#include <cstdint>
#include <type_traits>
#include <initializer_list>
#include <iterator>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <tuple>
#include <string>

using namespace std;

struct RAM_Settings
	{
			uint32_t Password = 0x5555AAAA;			  			  	///< (1)кодовое слово для сохранения настроек(всех)
			uint32_t Cbat = 200;									///< (3)Емкость АКБ, А*ч
			uint32_t Nmax_Tnan = 8;									///< (5)Number_cells = 20;          	///< Всего яйчеек АКБ
			uint32_t Power = 4000;         							///< (7)максимальная мощность ИБП
			uint32_t Slave_Address = 1;								///< (9)адрес в сети
			uint32_t Reserve9 = 0;				    				///< (11)default init в кострукторе; максимально допустимое кол-во отказов DS1820, для работоспособности системы.если 20 - не контролируем!
			uint32_t Reserve10 = 0;									///< (13)
			uint32_t Reserve11 = 1770;				///< 0xXXXXADC7 - старшие 16бит резерв; ADC7 - средняя точка в разрядах АЦП, для коррекции опорного напряжения АЦП = 3.3В(см. схему КИП5)
			float Kch1 = 0.0751231;
			float Cch1 = -155.1234567;
			float Kch2 = 0.0751231;
			float Cch2 = -155.1234567;
			float Kch3 = 0.0751231;
			float Cch3 = -155.1234567;
			float Kch4 = 0.0088031;
			float Cch4 = 0.1083489;
			float Kch5 = 0.0088031;
			float Cch5 = 0.1083489;
			float Kch6 = 0.0088031;
			float Cch6 = 0.1083489;
			float Kch8 = 0.1334356;
			float Cch8 = -265.5904908;
			float temperFactor = 0.0;				///< (45) -0.003 * 12;Коэффициент термокомпенсации, В/°C; 2.275В/элемент при 20 гр.С или 27,3В(12 эл-ов. это буф. режим); если цикл. режим работы, то 4мв на гр. С
			float Ucharge_par = 24.0;				///< (47) Номанальное напряжение КАН, В
			float Ucharge_min = 19.0; 				///< (49) Минимальное напряжение КАН, В
			float Ucharge_max = 27.6; 				///< (51) Номинальное напряжение буферизации при 25 гр. С
			float Uhigh = (Ucharge_max + 1.0);		///< (53) Максимальное напряжение КАН, В. Uhigh+0.5 - напряжение срабатывания защиты от перенапряжения.
			float UbatMin = 21.5;					///< (55) Минимальное напряжение АКБ, В(сигнализация); 24.0 ni-ca;
			float Icharge = 6.0;					///< (57) Ток заряда АКБ, А
			float Icharge2 = 5.0;					///< (59) Ток заряда АКБ, А
			float Icharge3 = 0.6;					///< (61) Ток заряда АКБ, А
			float IloadMax = 135.0;					///< (63) Максимальный ток нагрузки, А
			float Tcase_min = -20.0;					///< (17) Минимальная температура корпуса
			float Tcase_max = 50.0;					///< (17) Максимальная температура корпуса
			float Tbat_min = -15.0;					///< (17) Минимальная температура АКБ
			float Tbat_max = 50.0;					///< (17) Максимальная температура АКБ
			float Reserve12 = 0.0;
			float UbatFailure = 21.0;				///< (17) Полный разряд АКБ, В. отключение АКБ
			float Reserve14 = 0.0;
			float Reserve15 = 0.0;
			uint32_t Number_cells = 1;				///< (17)  Всего яйчеек КАN5000(<=10)
			uint32_t U_out_set = 100;				///< (17)  уставка выходного напряжения(*10 В)
			uint32_t I_out_set = 100; 				///< (17)  уставка выходного тока(*100 А)
			uint32_t Mode_set = 1;	  				///< (17)  режим в котором после старта (U)
			uint32_t Type_KAP = 0x15303330;			///< (17)  TODO тип КАН-ов используемым в системе// свободен под тип КАН-ов
			uint32_t Mask_Range = 0x00000201;		///< (17)  байт - void; 2 байт-маска; 1 байт-конеч. адрес(1-31); 0 байт-первый. адрес(1-31);
		    uint32_t Umax = 300;					///< одного КАН-а
			uint32_t Imax = 16600;					///< одного КАН-а
			uint32_t Reserve16 = 0;					///< (17) на всякий пожарный
			uint32_t Reserve17 = 0;					///< (17) на всякий пожарный под вторую группу
			uint32_t Reserve18 = 0;					///< (17)
			uint32_t Reserve19 = 0;					///< (17)
			uint32_t Reserve20 = 0;					///< (17)
			uint32_t Reserve21 = 0;					///< (17)
			uint32_t Reserve22 = 0;					///< (17)
			uint32_t Reserve23 = 0;					///< (17)
			uint32_t Reserve24 = 0;					///< (17)
			uint32_t Reserve25 = 0;					///< (17) на всякий пожарный под вторую группу
	}Coefficient;


	int REG_TYPE_SUBBOARD = 41;
	int REG_PASSWORD_L = 43;

	int REG_FLOAT_T_NODE_H			= 174;

	int REG_FLOAT_CAP_SUM_L			= 175;
	int REG_FLOAT_CAP_SUM_H			= 176;
	 int REG_FLOAT_T_NODE_L 		= 173;

	 constexpr uint32_t NUMBER_DS1820 = 8;

	 union DS1820
	 {
	 	uint32_t ArreyForSave[NUMBER_DS1820*4];
	 	uint32_t Sensor[NUMBER_DS1820][4];
	 	uint8_t Byte[NUMBER_DS1820 * 4 * 4];
	 };

	 union SlaveRegsUnion1
	 {
	 	uint32_t data_int[88];
	 	uint16_t data_short[176] = {0};
	 };

uint16_t Crc16(uint8_t  *pcBlock, uint32_t  len, uint16_t init)
{
    uint16_t crc = init;//0xFFFF;
    while( len-- )
    {
        crc ^= *pcBlock++ << 8;

        for(uint32_t i = 0; i < 8; i++ )
	    crc = crc & 0x8000 ? ( crc << 1 ) ^ 0x1021 : crc << 1;
    }

    return crc;
}



int no_main_10()
{
	SlaveRegsUnion1 slaveRegsUnion1;
	for(uint32_t i; i << 88; i++)
		slaveRegsUnion1.data_int[i] = i;
	DS1820 Sensor_T_AB, Sensor_T_NODE;

	uint32_t i, j, addr=0;//addr как флаг входа в процедуру записи
	uint16_t crc_ab;
	//crc_ab = Crc16((uint8_t*)(Sensor_T_AB), sizeof(Sensor_T_AB), 0xFFFF);

	cout << "crc_ab = " << crc_ab << endl;

	i = sizeof(Sensor_T_AB)/sizeof(uint32_t);
	addr = 0;
	j=0;//***

	addr = (sizeof(Sensor_T_AB)/sizeof(uint32_t));
	uint32_t temp = addr;
	i = sizeof(Sensor_T_NODE)/sizeof(uint32_t);
	j=0;

	addr = (sizeof(Sensor_T_AB) + sizeof(Sensor_T_NODE))/sizeof(uint32_t); // 32 + 32
	i = sizeof(Coefficient)/sizeof(uint32_t);
	j = (REG_PASSWORD_L - 1)/2;
	while(i--)
	{
		cout << "addr = " << addr << endl;
		crc_ab = Crc16((uint8_t*)(&slaveRegsUnion1.data_int[j]), sizeof(uint32_t), crc_ab);
		cout << "crc_ab = " << crc_ab << endl;
		addr++;
		j++;
	}

	cout << &Sensor_T_AB.Sensor << endl;
	cout << &Sensor_T_AB.Sensor[1] << endl;
	cout << &Sensor_T_AB.Sensor[4] << endl;

	i = (sizeof(Sensor_T_AB)/sizeof(uint32_t)) * 2;
		addr = 0;
		j=0;//***
		while(i--)
		{
			cout << (addr >> 2) << "  " << j << endl;
			j++;j&=0x3l;//***
			addr++;
		}

	return 0;
}


