#ifndef _inv_8851_h
#define _inv_8851_h

#include <cstdint>


// можливі значення для різних режимів
// inverter topology 0-10
// llc topology  0-2,5,8
// pv topology 0-3,8,9,10- підписано як shutdown mode, 11 - normal mode
// buck topology 0-2
// не плодив сутності хоча по феншую треба...

enum  run_mode
{
    standby_mode              = 0,
    fault_mode                = 1,
    shutdown_mode             = 2,
    normal_mode               = 3,
    no_battery_mode           = 4,
    discharge_mode            = 5,
    parallel_discharge        = 6,
    bypass_mode               = 7,
    charge_mode               = 8,
    grid_discharge_mode       = 9,
    micro_grid_discharge_mode = 10,
    // далі йдуть числові значення 11,12,13,14,15
};

/*
 * Inverter state.
 */
// це ж с++... по феншую так а не #define
const int  inv8851_state_pkt_len = 154; 
#define INV8851_STATE_PKT_LEN       (154)

#pragma pack(push, 1)
struct inv8851_state_s  {
    uint16_t proto;         // 0x8851
    uint16_t command;       // 0x0003 - read ?  0x0010 - write ?
    uint16_t addr;          // 0x0000 - for state , 0x0200 for config
    uint16_t data_size;     // кількість байт з даними, подібно до модбас тут завжди 144 / 2 = 72 розмір words

    union
    {
        uint16_t words[72];
        struct
        {
            union // t0000
            {
                uint16_t run_mode; // тут чотири поля по чотир біти
                struct
                {
                  enum run_mode inverter_topology:4;
                  enum run_mode llc_topology:4;
                  enum run_mode pv_topology:4;
                  enum run_mode buck_topology:4;
                } ;
            };
            struct // t0001
            {
                uint8_t system_power:1;
                uint8_t charge_finish:1;
                uint8_t bus_ok:1;
                uint8_t bus_n_grid_voltage_match:1;
                uint8_t no_battery:1;
                uint8_t pv_excess:1;
                uint8_t floating_charge:1;
                uint8_t system_initial_finished:1;

                uint8_t inverter_topology_initial_finished:1;
                uint8_t llc_topology_initial_finished:1;
                uint8_t pv_topology_initial_finished:1;
                uint8_t buck_topology_initial_finished:1;
                uint8_t eq_charge_start:1;
                uint8_t eq_charge_ready:1;
                uint8_t w6:2;
            };
            int16_t t0002; //  maybe warning flags
            int16_t t0003; //  maybe warning flags
            struct // t0004  flags probably
            {
                uint8_t grid_pll_ok:1;
                uint8_t lo0004:7; // unused, maybe warning flags

                uint8_t hi0004:1; // unused, maybe warning flags
                uint8_t disable_utility:1;
                uint8_t hi0004_:6; // unused, maybe warning flags
            };
            int16_t t0005; //  maybe warning flags
            int16_t t0006; //  maybe warning flags
            int16_t t0007; //  maybe warning flags
            int16_t t0008; //  maybe warning flags
            int16_t t0009; //  maybe warning flags
            int16_t t0010; //  maybe warning flags
            int16_t t0011; //  maybe warning flags
            int16_t t0012; //  maybe warning flags
            struct                                                                         //int16_t t0013
            {
                uint8_t lo0013:7; // unused, maybe warning flags
                uint8_t pv_input_ok:1;
                uint8_t parallel_lock_phase_ok:1;
                uint8_t hi0013:7; // unused, maybe warning flags
            };
            int16_t softvare_version;                                                       //int16_t t0014
            int16_t log_number;                                                             //int16_t t0015
            int16_t t0016;
            int16_t t0017;
            int16_t t0018;
            int16_t t0019;
            int16_t t0020;
            int16_t inv_voltage;    // 0,1 volt
            int16_t inv_current;    // 0.01 a
            int16_t inv_freq;       // 0.01 hz
            int16_t inv_va;         // 1 va
            int16_t load_va;        // 1 va
            int16_t t0026;          // те саме що й inv_va тільки із знаком "-", співпадає з t0032, інколи є робіжність в 2-3 одиниці, це схоже на потужність яку воно споживає з мережі є думка що це повна потужність
            int16_t load_power;     // 1 w
            int16_t inverter_va_percent;    // t0028;
            int16_t inverter_watt_percent;  // t0029;
            int16_t load_current;   // 0.01 a
            int16_t low_load_currennt;
            int16_t t0032; // див. t0026 на телефоні ніде не відображається
            int16_t grid_voltage;   // 0.1 v
            int16_t grid_current;   // 0.01 a
            int16_t grid_freq ;     // 0.01 hz
            int16_t parallel_voltage;
            int16_t parallel_current;
            int16_t parallel_frequency;
            int16_t batt_voltage;   // 0.01 v
            int16_t batt_charge_current; //  0.1 a, negative if battery is discharging
            int16_t t0041;
            int16_t t0042;
            int16_t pv_voltage;     // 0.1 v
            int16_t pv_current;     // 0.01 a
            int16_t pv_power;       // 1 w
            int16_t bus_voltage;    // 0.1 v
            int16_t t0047;
            int16_t t0048; // тут є якесь значення але воно ніде не відображається.
            int16_t inverter_voltage_dc_component; // t0049
            struct                                 // t0050
            {
                uint8_t fan1_speed_percent;
                uint8_t fan2_speed_percent;
            };
            struct                                 // t0051;
            {
                uint8_t ntc2_temperature;
                uint8_t ntc3_temperature;
            };
            struct                                 // t0052;
            {
                uint8_t ntc4_temperature;
                uint8_t bts_temperature;
            };
            int16_t bms_battery_soc;     // t0053;
            int16_t bms_battery_voltage; // t0054;
            int16_t bms_battery_current; // t0055;
            int16_t bms_01cell_voltage;  // t0056;
            int16_t bms_02cell_voltage;  // t0057;
            int16_t bms_03cell_voltage;  // t0058;
            int16_t bms_04cell_voltage;  // t0059;
            int16_t bms_05cell_voltage;  // t0060;
            int16_t bms_06cell_voltage;  // t0061;
            int16_t bms_07cell_voltage;  // t0062;
            int16_t bms_08cell_voltage;  // t0063;
            int16_t bms_09cell_voltage;  // t0064;
            int16_t bms_10cell_voltage;  // t0065;
            int16_t bms_11cell_voltage;  // t0066;
            int16_t bms_12cell_voltage;  // t0067;
            int16_t bms_13cell_voltage;  // t0068;
            int16_t bms_14cell_voltage;  // t0069;
            int16_t bms_15cell_voltage;  // t0070;
            int16_t bms_16cell_voltage;  // t0071;
        };
    };

    uint16_t crc;   // modbus crc16

};
#pragma pack(pop)
typedef   inv8851_state_s inv8851_state_t;


const int inv8851_config_pkt_len = 100;
const int inv8851_config_cmd_write  = 0x1000 ;

#define INV8851_CONFIG_PKT_LEN          (100)
#define INV8851_CONFIG_CMD_WRITE        0x1000

/*
 * Inverter config. 100 bytes len
 */
#pragma pack(push, 1)
struct inv8851_config_s {

    uint16_t proto;         // 0x8851
    uint16_t command;       // 0x0003 - read ?  0x0010 - write ?
    uint16_t addr;          // 0x0000 - for state , 0x0200 for config
    uint16_t data_size;     // кількість байт з даними, подібно до модбас тут 90/2=45 розмір words

    union
    {
        uint16_t words[45];
        struct
        {
            int16_t energy_priority;     // output energy priority / charger priority
                // 0x10a0 - pv-grid-battery (sub)  bit 2 = 0
                // 0x10a4 - pv-battery-grid (sbu)  bit 2 = 1
                // 0x1084 - sbu + snu charge mode
                // 0x10a0 - - charge only from solar  (oso) a
                // 0x1080 - - charge from pv and grid (snu) 8
                // 0x1090 - pv > grid charge (cso)          9
                // output source пріоріті (01) 0x2010-sub  0x2410-sbu це мабуть регістер прапорів 11-й біт схоже залежить від параметра (01)
                // старша 2 буда коли параметр (16) був oso, як включив snu змінилась на 0
            int16_t t0002;
            int16_t t0003;
            int16_t output_voltage;     // output voltage (08)
            int16_t output_freq;        // output frequency (09)
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
            int16_t batt_cut_off_voltage;           //  low dc cut-off voltage (29)  0.01 v
            int16_t t0017;
            int16_t t0018;
            int16_t t0019;
            int16_t t0020;
            int16_t batt_bulk_chg_voltage;          // bulk charge voltage (26)   0.01 v
            int16_t t0022;
            int16_t batt_float_chg_voltage;         // floating charge voltage (27)            0.01 v
            int16_t batt_pont_back_to_util_volt;    // voltage point back to utility (13)      0.01 v
            int16_t util_chg_current;               // maximum utilty charge current (11)      0.1 a  112 offset
            int16_t total_chg_current;              // maximum charge current (02)             0.1 a  114
            int16_t batt_chg_cut_off_current;       // battery charge cut-off current (12)     0.1 a
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
            int16_t batt_eq_voltage;                // battery equalization voltage (34)       0.01 v
            int16_t batt_eq_time;                   // battery equalization time (35)
            int16_t batt_eq_timeout;                // battery equalization timeout (36)
            int16_t batt_eq_interval;               // equalization interval(37)

        };
    };

    uint16_t crc;   // modbus crc16
};
#pragma pack(pop)

typedef inv8851_config_s inv8851_config_t;



#endif // _inv_8851_h
