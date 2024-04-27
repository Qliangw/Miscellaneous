/**
 * @file 
 *
 * @brief Definitions related to firmware versioning.
 */

#ifndef __VERSION_H
#define __VERSION_H

#define FW_VERSION_MAJOR        0x01
#define FW_VERSION_MINOR        0x00
#define FW_VERSION_PATCH        0x01

#define COMBINE_VERSION(major, minor, patch) \
    (((major) & 0x03) << 6 | (((minor) & 0x03) << 4) | ((patch) & 0x0F))
        
#define FW_VERSION COMBINE_VERSION(FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_PATCH)

#define EXTRACT_YEAR(date) \
        (((date[7] - '0') * 1000) + \
         ((date[8] - '0') * 100) + \
         ((date[9] - '0') * 10) + \
         (date[10] - '0') - 2000)

#define EXTRACT_MONTH(date) \
    ((date[0] == 'J' && date[1] == 'a' && date[2] == 'n') ? 1 : \
      (date[0] == 'F' && date[1] == 'e' && date[2] == 'b') ? 2 : \
      (date[0] == 'M' && date[1] == 'a' && date[2] == 'r') ? 3 : \
      (date[0] == 'A' && date[1] == 'p' && date[2] == 'r') ? 4 : \
      (date[0] == 'M' && date[1] == 'a' && date[2] == 'y') ? 5 : \
      (date[0] == 'J' && date[1] == 'u' && date[2] == 'n') ? 6 : \
      (date[0] == 'J' && date[1] == 'u' && date[2] == 'l') ? 7 : \
      (date[0] == 'A' && date[1] == 'u' && date[2] == 'g') ? 8 : \
      (date[0] == 'S' && date[1] == 'e' && date[2] == 'p') ? 9 : \
      (date[0] == 'O' && date[1] == 'c' && date[2] == 't') ? 10 : \
      (date[0] == 'N' && date[1] == 'o' && date[2] == 'v') ? 11 : \
      (date[0] == 'D' && date[1] == 'e' && date[2] == 'c') ? 12 : 0)

#define EXTRACT_DAY(date) \
        ((date[4] == ' ') ? (date[5] - '0') : ((date[4] - '0') * 10 + (date[5] - '0')))

#define IS_PM(time_str) \
        (((time_str[0] - '0') * 10 + (time_str[1] - '0')) >= 12) ? 1 : 0

#define EXTARCT_SECOND(time_str) \
            ((time_str[6] - '0') * 10 + (time_str[7] - '0')) 
               
#define EXTARCT_MINUTE(time_str) \
                ((time_str[3] - '0') * 10 + (time_str[4] - '0'))

#define EXTARCT_HOUR(time_str) \
    ( (time_str[0] - '0') * 10 + (time_str[1] - '0') > 12 ? \
      (time_str[0] - '0') * 10 + (time_str[1] - '0') - 12 : \
      (time_str[0] - '0') * 10 + (time_str[1] - '0') == 0 ? 12 : \
      (time_str[0] - '0') * 10 + (time_str[1] - '0') )

/**
 * @brief Structure for storing firmware version and compilation information.
 *
 * @details
 * | Field      | Description                                         |
 * |------------|-----------------------------------------------------|
 * | version    | Firmware version number                             |
 * |            | - Bits 7-6: Major version                           |
 * |            | - Bits 5-4: Minor version                           |
 * |            | - Bits 3-0: Patch version                           |
 * | comp_date  | Compilation date string (Format: "Mmm dd yyyy")    |
 * | comp_time  | Compilation time string (Format: "hh:mm:ss")        |
 * | comp0      | Compilation year offset (year - 2000)               |
 * | comp1      | Compilation month and hour (12-hour format)         |
 * |            | - Bits 7-4: Month                                    |
 * |            | - Bits 3-0: Hour                                     |
 * | comp2      | Compilation date and PM flag                         |
 * |            | - Bits 7-3: Last five bits of date (1-31)           |
 * |            | - Bit 2: PM flag (1 for PM, 0 for AM)               |
 * |            | - Bits 1-0: Unused                                   |
 * | comp3      | Compilation minute                                   |
 * |            | - Bits 7-6: Unused                                   |
 * |            | - Bits 5-0: Minute                                   |
 */
struct version {
    const unsigned char version; /**< @brief Firmware version number */
//    const unsigned char comp_date[12]; /**< @brief Compilation date string */
//    const unsigned char comp_time[8]; /**< @brief Compilation time string */
    const unsigned char comp0; /**< @brief Compilation year offset (year - 2000) */
    const unsigned char comp1; /**< @brief Compilation month and hour */
    const unsigned char comp2; /**< @brief Compilation date and PM flag */
    const unsigned char comp3; /**< @brief Compilation minute */
    const unsigned char comp4;
};


/**
 * @brief Firmware version information instance.
 */
const struct version firmware_version = {
    .version        = FW_VERSION, /**< Firmware version value. */
//    .comp_date      = __DATE__,   /**< Compilation date. */
//    .comp_time      = __TIME__,   /**< Compilation time. */
    .comp0 = EXTRACT_YEAR(__DATE__),
    .comp1 = ((EXTRACT_MONTH(__DATE__) << 4 ) & 0xF0) | (EXTARCT_HOUR(__TIME__) & 0x0F),
    .comp2 = (EXTRACT_DAY(__DATE__) << 3) | ((IS_PM(__TIME__) & 0x01) << 2),
    .comp3 = EXTARCT_MINUTE(__TIME__) & 0x3F,
    .comp4 = EXTARCT_SECOND(__TIME__) & 0x3F,
};

#endif

