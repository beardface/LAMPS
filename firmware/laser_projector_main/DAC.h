#ifndef __DAC_H__
#define __DAC_H__

extern "C" 
{
#include <float.h>
}

///
/// The TLV5620 is a four channel, 8 bits per channel DAC.
/// Each DAC has two FS ranges -- Vref and 2 * Vref.
/// 

#define DAC_TLV5620_NUM_CHS 4

enum dac_tlv5620_ranges { DAC_REF=0, DAC_REFX2=1 };
enum dac_tlv5620_chs    { DAC_CH_A=0, DAC_CH_B=1, DAC_CH_C=2, DAC_CH_D=3 };

///
/// DAC_TLV5620
///

class DAC_TLV5620 {
 private:
  unsigned char _load_pin;
  unsigned char _latch_pin;
  enum dac_tlv5620_ranges _range[DAC_TLV5620_NUM_CHS];
  double _lsb[DAC_TLV5620_NUM_CHS];
 public:
  static const double _ref = 1.24;             ///< Reference voltage of the TLV431
  static const unsigned char _fs_code   = 255; ///< Max value of an 8 bit unsigned char is = 2^8 - 1
  static const unsigned int  _num_steps = 256; ///< 8 bits, 256 values (0..255)
  DAC_TLV5620(unsigned char load_pin, unsigned char latch_pin);
  char write_data(dac_tlv5620_chs ch, dac_tlv5620_ranges range, 
		  unsigned char code);
  char set_voltage(dac_tlv5620_chs ch, double v);
  void set_range(dac_tlv5620_chs ch, dac_tlv5620_ranges range);
  char set_code(dac_tlv5620_chs ch, unsigned char code);
};


///
/// The TLV5618 is a two channel, 12 bits per channel DAC,
/// The FS range of the the DAC is VREF
///

#define DAC_TLV5618_NUM_CHS 2
#define DAC_TLV5618_RS_MASK 0x60

enum dac_tlv5618_rs   { DAC_WRITE_B_AND_BUFFER=0x00, DAC_WRITE_BUFFER=0x10, DAC_WRITE_A_UPDATE_B=0x80 };
enum dac_tlv5618_spds { DAC_SLOW=0x00, DAC_FAST=0x40 };
enum dac_tlv5618_pwrs { DAC_NORMAL=0x00, DAC_POWER_DOWN=0x20 };

///
/// DAC_TLV5618
///

class DAC_TLV5618 {
 private:
  unsigned char _cs_pin;
  double _lsb;
  union {
    struct {
      unsigned R1 : 1;
      unsigned SPD: 1;
      unsigned PWR: 1;
      unsigned R0 : 1;
      unsigned UNUSED: 4;
    } control_bits;
    unsigned char control_byte;
  } _control;
 public:
  static const double _ref = 1.24;              ///< Reference voltage of the TLV431
  static const unsigned int _fs_code   = 4095; ///< Max value of a 12 bit unsigned char is = 2^12 - 1
  static const unsigned int  _num_steps = 4096; ///< 12 bits, 256 values (0..4095)
  DAC_TLV5618(unsigned char cs_pin, dac_tlv5618_pwrs pwr=DAC_NORMAL, dac_tlv5618_spds spd=DAC_SLOW);
  char write_data(dac_tlv5618_rs rs, unsigned int code);
  char set_voltage(dac_tlv5618_rs rs, double v);
  char set_code(dac_tlv5618_rs rs, unsigned int code);
  void set_speed(dac_tlv5618_spds spd);
  void set_power_control(dac_tlv5618_pwrs pwr);

};



#endif
