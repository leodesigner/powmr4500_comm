#ifndef _INV_8851_H
#define _INV_8851_H

#include <cstdint>
#include <string>

#pragma pack(push, 1)

/*
 * Inverter state.
 */

#define INV8851_STATE_PKT_LEN       (154)

typedef struct {
    uint16_t proto;         // 0x8851
    uint16_t command;       // 0x0003 - read ?  0x0010 - write ?
    uint16_t addr;          // 0x0000 - for state , 0x0200 for config

    int16_t t0000;
    int16_t t0001; 
        // схоже на прапор коли вкл 0x3055 коли викл 0x2222 коли вкл байпас 0x3057  виключений кнопкою але під напругою з мережі 0х3050 заряд акумулятора від мережі  0x3088
        // state flags probably:
        // on           0x3055
        // off          0x2222
        // bypass ON    0x3057
        // turned off but grid power is present  0х3050
        // battery charging from Grid            0x3088

    int16_t t0002; 
        // state flags 2
        // схоже на прапор коли вкл 0x0B81 коли викл 0x0080 виключени кнопкою але під напругою з мережі 0x0b80 
        // інколи замість 'B' в момент включення тут 'A' коли включаєтся кнопкою але при тому був під напругою з мережі
    int16_t t0003;
    int16_t t0004;
    int16_t t0005; // flags probably
    int16_t t0006;
    int16_t t0007;
    int16_t t0008;
    int16_t t0009;
    int16_t t0010;
    int16_t t0011;
    int16_t t0012;
    int16_t t0013;
    int16_t t0014;
    int16_t t0015;
    int16_t t0016;
    int16_t t0017;
    int16_t t0018;
    int16_t t0019;
    int16_t t0020;
    int16_t t0021;
    int16_t inv_voltage;    // 0,1 Volt
    int16_t inv_current;    // 0.01 A
    int16_t inv_freq;       // 0.01 Hz
    int16_t inv_va;         // 1 VA
    int16_t load_va;        // 1 VA
    int16_t t0027;          // те саме що й inv_va тільки із знаком "-", співпадає з t0033, інколи є робіжність в 2-3 одиниці, це схоже на потужність яку воно споживає з мережі є думка що це повна потужність
    int16_t load_power;     // 1 W
    int16_t t0029;          // це дуже схоже на струм але помноженй на 1000 і що це за струм складно сказати інколи співдаладє з load_current
    int16_t t0030;          // це дуже схоже на струм але помноженй на 1000 і що це за струм складно сказати інколи співдаладє з load_current а інколи є сумою load_current
    int16_t load_current;   // 0.01 A
    int16_t t0032;
    int16_t t0033;          // те саме що й inv_va тільки із знаком "-" співпадає  з t0027, інколи є робіжність в 2-3 одиниці, це схоже на потужність яку воно спожива з мережи є думка що це аквна потужність
    int16_t grid_voltage;   // 0.1 V
    int16_t grid_current;   // 0.01 A
    int16_t grid_freq ;     // 0.01 Hz                                  
    int16_t t0037;
    int16_t t0038;
    int16_t t0039;
    int16_t batt_voltage;   // 0.01 V
    int16_t batt_charge_current; //  0.1 A, negative if battery is discharging  
    int16_t t0042;
    int16_t t0043;
    int16_t pv_voltage;     // 0.1 V
    int16_t pv_current;     // 0.01 A
    int16_t pv_power;       // 1 W 
    int16_t bus_voltage;    // 0.1 V
    int16_t t0048;
    int16_t t0049; // ще теж схоже на яксь струм, коли включається мережа і починається заряд значення плавно наростає від 0 до уставки. Коли вимикається мережа - плавно падає до нуля.
    int16_t t0050;
    int16_t t0051;
    int16_t t0052;
    int16_t t0053; // probably energy counter, only increases over the time / це схоже на якись лічильник енергії, завжди збільшується....
    int16_t t0054;
    int16_t t0055;
    int16_t t0056;
    int16_t t0057;
    int16_t t0058;
    int16_t t0059;
    int16_t t0060;
    int16_t t0061;
    int16_t t0062;
    int16_t t0063;
    int16_t t0064;
    int16_t t0065;
    int16_t t0066;
    int16_t t0067;
    int16_t t0068;
    int16_t t0069;
    int16_t t0070;
    int16_t t0071;
    int16_t t0072;

    uint16_t crc;   // Modbus CRC16

} inv8851_state_t;


#define INV8851_CONFIG_PKT_LEN          (100)
#define INV8851_CONFIG_CMD_WRITE        0x1000 

/*
 * Inverter config. 100 bytes len
 */

typedef struct {

    uint16_t proto;         // 0x8851
    uint16_t command;       // 0x0003 - read ?  0x0010 - write ?
    uint16_t addr;          // 0x0000 - for state , 0x0200 for config

    int16_t t0000;          // 0x5a00
    int16_t energy_priority;     // Output Energy Priority / Charger priority
        // 0x10a0 - PV-GRID-BATTERY (SUB)  bit 2 = 0
        // 0x10a4 - PV-BATTERY-GRID (SBU)  bit 2 = 1
        // 0x1084 - SBU + SNU charge mode
        // 0x10a0 - - charge only from Solar  (OSO) a 
        // 0x1080 - - charge from PV and Grid (SNU) 8
        // 0x1090 - pv > grid charge (CSO)          9
        // Output source пріоріті (01) 0x2010-SUB  0x2410-SBU це мабуть регістер прапорів 11-й біт схоже залежить від параметра (01)
        // старша 2 буда коли параметр (16) був OSO, як включив SNU змінилась на 0
    int16_t t0002;
    int16_t t0003;
    int16_t output_voltage;     // output voltage (08)
    int16_t output_freq;        // Output frequency (09)
    int16_t t0006;
    int16_t t0007;
    int16_t t0008;
    int16_t t0009;
    int16_t t0010;
    int16_t t0011;
    int16_t t0012;
    int16_t t0013;
    int16_t t0014;
    int16_t t0015;
    int16_t batt_cut_off_voltage;           //  Low DC cut-off voltage (29)  0.01 V
    int16_t t0017;
    int16_t t0018;
    int16_t t0019;
    int16_t t0020;
    int16_t batt_bulk_chg_voltage;          // bulk charge voltage (26)   0.01 V                 
    int16_t t0022;
    int16_t batt_float_chg_voltage;         // floating charge voltage (27)            0.01 V
    int16_t batt_pont_back_to_util_volt;    // Voltage point back to utility (13)      0.01 V
    int16_t util_chg_current;               // Maximum utilty charge current (11)      0.1 A  112 offset
    int16_t total_chg_current;              // Maximum charge current (02)             0.1 A  114
    int16_t batt_chg_cut_off_current;       // Battery charge cut-off current (12)     0.1 A   
    int16_t t0028;
    int16_t t0029;
    int16_t t0030;
    int16_t t0031;
    int16_t t0032;
    int16_t t0033;
    int16_t t0034;
    int16_t t0035;
    int16_t t0036;
    int16_t t0037;
    int16_t t0038;
    int16_t t0039;
    int16_t t0040;
    int16_t t0041;
    int16_t batt_eq_voltage;                // Battery equalization voltage (34)       0.01 V
    int16_t batt_eq_time;                   // Battery equalization time (35)
    int16_t batt_eq_timeout;                // Battery equalization timeout (36)
    int16_t batt_eq_interval;               // Equalization interval(37)

    uint16_t crc;   // Modbus CRC16


} inv8851_config_t;

#pragma pack(pop)


#endif // _INV_8851_H
