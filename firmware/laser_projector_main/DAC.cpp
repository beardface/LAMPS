#include "SPI.h"
#include "DAC.h"

#include <inttypes.h>
#include "Arduino.h"

///
/// Calculates the size of the DAC LSB which is stored in the DAC
/// object. For the TLV5620 each channel has an independent range and
/// the LSB size is stored for each channel. The macros are used to
/// initalize the DAC object and by functions that change the range
/// (TLV5620).
///

#define dac_tlv5620_lsb (_ref * (_range[ch] ? 2 : 1) / _num_steps);
#define dac_tlv5618_lsb (2 * _ref / _num_steps);

/// 
/// Constructs a DAC_TLV5620 object and Assigns a pin number for the
/// TLV5620 LOAD and LATCH pin.  The pin numbers should be Arduino pin
/// numbers (2..13).  Initializes the range of each DAC channel to 2 *
/// Vref (which is 2 * 1.24V for the NB1A).
///
/// \param[in] load_pin pin number attached to the TLV5620 LOAD pin
/// \param[in] latch_pin pin number attached to the TLV5620 LATCH pin
///

DAC_TLV5620::DAC_TLV5620(unsigned char load_pin, unsigned char latch_pin) {
  unsigned char ch;
  _load_pin = load_pin;
  _latch_pin = latch_pin;
  for (ch = 0; ch < DAC_TLV5620_NUM_CHS; ch++) {
    _range[ch] = DAC_REFX2;
    _lsb[ch]   = dac_tlv5620_lsb;
  }
  digitalWrite(_load_pin,  1);
  digitalWrite(_latch_pin, 1);
  pinMode(_load_pin, OUTPUT);
  pinMode(_latch_pin, OUTPUT);
};


///
/// <code>write_data</code> is used to output data, using the SPI port, to the
/// TLV5620. It is called by <code>set_voltage</code> and <code>set_code</code>.
/// 
/// \param[in] ch channel to output data to -- valid channels are {A, B, C, D}
/// \param[in] range the output voltage range -- valid ranges are {REF, REFX2}
/// \param[in] code the DAC code -- valid codes are 0..255
/// \returns 0 = success
///
/// \todo Add error codes
///
/// The data transfer for the TLV5620 consists of the following steps --
/// <ul>
/// <li> Set LOAD High ...... data is clocked on the falling edge of CLK
/// <li> Pulse LOAD Low ..... transfer data from the serial-in register to the selected DAC
/// <li> Set LATCH Low ...... output voltage is updated
/// </ul>
///

char DAC_TLV5620::write_data(dac_tlv5620_chs ch, dac_tlv5620_ranges range, 
			     unsigned char code) {
  unsigned char dac_data[2];
  dac_data[0] = ((ch & 0x03) << 1) | ((range & 0x01) << 0); 
  dac_data[1] = code;
  digitalWrite(_latch_pin, 1);
  digitalWrite(_load_pin,  1);
  spi.write(dac_data, 2);
  digitalWrite(_load_pin,  0);
  delayMicroseconds(10); 
  digitalWrite(_load_pin,  1);
  delayMicroseconds(10); 
  digitalWrite(_latch_pin, 0);
  delayMicroseconds(10); 
  digitalWrite(_latch_pin, 1);
  return(0);
};

///
/// Writes a code to a single DAC channel. The DAC channel output voltage
/// is updated. 
///
/// \param[in] ch channel to output data to -- valid channels are {A, B, C, D}
/// \param[in] code the DAC code -- valid codes are 0..255
/// \returns 0 = success
///
char DAC_TLV5620::set_code(dac_tlv5620_chs ch, unsigned char code) { 
  return(write_data(ch, _range[ch], code));
}

///
/// Sets the DAC range for a single DAC channel. The DAC output voltage
/// is not changed. The range is saved in ths DAC_TLV5620 object. The next
/// set_code or set_voltage command will use the new range. 
///
/// \param[in] ch channel to output data to -- valid channels are {A, B, C, D}
/// \param[in] range the output voltage range -- valid ranges are {REF, REFX2}
/// \returns void
///
void DAC_TLV5620::set_range(dac_tlv5620_chs ch, dac_tlv5620_ranges range) { 
  _range[ch] = range; 
  _lsb[ch] = dac_tlv5620_lsb;
} 

///
/// Sets the output voltage for a single DAC channel. The DAC output voltage
/// is updated. If the voltage, v, is greater than FS DAC voltage than the 
/// DAC voltage is set to the FS value. If the voltage, v, is less than 0 then
/// the DAC voltage is set to 0. 
/// 
/// \param[in] ch channel to output data to -- valid channels are {A, B, C, D}
/// \param[in] v the value of the voltage to output -- valid voltage values are 0..Vref. 
/// \returns 0 = success
/// 

char DAC_TLV5620::set_voltage(dac_tlv5620_chs ch, double v) {
  if (v > _lsb[ch] * _fs_code - DBL_EPSILON) return(set_code(ch, _fs_code));
  if (v < DBL_EPSILON) return(set_code(ch, 0));
  return(set_code(ch, (unsigned char)(v / _lsb[ch])));
}


// ********************
// 5618
// ********************


/// 
/// Constructs a DAC_TLV5618 object and assigns a pin number for the
/// TLV5618 CHIP SELECT pin. The pin numbers should be an Arduino (2-13) or
/// Sanguino pin number (2-24). 
///
/// \param[in] cs_pin pin number attached to the TLV5618 chip select pin
/// \param[in] pwr power mode for the DAC -- NORMAL or POWER_DOWN. The default is NORMAL.
/// \param[in] spd speed of the DAC -- SLOW or FAST
///

DAC_TLV5618::DAC_TLV5618(unsigned char cs_pin, dac_tlv5618_pwrs pwr, dac_tlv5618_spds spd) {
  unsigned char ch;
  _cs_pin = cs_pin;
  _lsb = dac_tlv5618_lsb;
  _control.control_byte = pwr | spd;
  digitalWrite(_cs_pin,  1);
  pinMode(_cs_pin, OUTPUT);
};


///
/// <code>write_data</code> is used to output data, using the SPI port, to the
/// TLV5618. It is called by <code>set_voltage</code> and <code>set_code</code>.
///
/// \param[in] rs register select bits
/// \param[in] code the DAC code -- valid codes are 0..4095
/// \returns 0 = success
///
/// \todo Add error codes
///
///

char DAC_TLV5618::write_data(dac_tlv5618_rs rs, unsigned int code) {
  unsigned char dac_data[2];
  _control.control_byte &= DAC_TLV5618_RS_MASK;
  _control.control_byte |= rs;
  dac_data[0] = (unsigned char)(((code & 0xF00)>>8) | _control.control_byte);
  dac_data[1] = (unsigned char)(code & 0xFF);
  digitalWrite(_cs_pin, 0);
  delayMicroseconds(10); 
  spi.write(dac_data, 2);
  delayMicroseconds(10); 
  digitalWrite(_cs_pin,  1);
  return(0);
};


///
/// Writes the code corresponding to the voltage value, <code>v</code>, to the DAC.
///
/// If the register bits, <code>rs</code>, are set to
/// WRITE_B_AND_BUFFER then the code is written to DACB and to the
/// buffer. If <code>rs</code> is set to WRITE_BUFFER then the code is
/// only written to the buffer and there is no change to either DAC
/// output.  If <code>rs</code> is set to WRITE_A_UPDATE_B then the
/// code is written to DACA and the value stored in the buffer is
/// written to DACB.
/// 
/// If the voltage, v, is greater than FS DAC voltage then the DAC
/// voltage is set to the FS value. If the voltage, v, is less than 0
/// then the DAC voltage is set to 0. The TLV5618 has a voltage doubler
/// on each DAC channel. The FS voltage is 2 * VREF * 4095 / 4096. 
/// 
/// To perform simultaneous updates of both channels --
/// <ol>
/// <li>Use WRITE_BUFFER to write the data for DACB to the buffer
/// <li>Use WRITE_A_UPDATE_B which will write data to DACA and update DACB with the data in the buffer 
/// </ol>
/// 
/// Updating DACA <b>always</b> updates DACB with the data that is stored in the buffer.
/// On startup initialize the buffer using either WRITE_BUFFER or WRITE_B_AND_BUFFER.
/// 
/// \param[in] rs register select bits.  The valid values for <code>rs</code> are:
/// <dl>
/// <dt>WRITE_B_AND_BUFFER</dt>&nbsp;&nbsp; Write data to DACB and BUFFER
/// <dt>WRITE_BUFFER      </dt>&nbsp;&nbsp; Write data to BUFFER
/// <dt>WRITE_A_UPDATE_B  </dt>&nbsp;&nbsp; Write data to DACA and update DACB with BUFFER 
/// </dl>
/// <br>
///
/// \param[in] v the value of the voltage to output -- valid voltage values are 0..Vref. 
/// \returns 0 = success
/// 

char DAC_TLV5618::set_voltage(dac_tlv5618_rs rs, double v) {
  if (v > _lsb * _fs_code - DBL_EPSILON) return(set_code(rs, _fs_code));
  if (v < DBL_EPSILON) return(set_code(rs, 0));
  return(set_code(rs, (unsigned int)(v / _lsb)));
}

///
/// Writes a code to the DAC. 
///
/// \param[in] rs register to output data to 
/// \param[in] code the DAC code -- valid codes are 0..4095
/// \returns 0 = success
///
char DAC_TLV5618::set_code(dac_tlv5618_rs rs, unsigned int code) { 
  if (code > 4095) code = 4095;
  return(write_data(rs, code));
}

///
/// Changes the speed control bit. 
///
/// The update occurs on the next write to the DAC.
///
/// \param[in] spd -- values are SLOW or FAST
///
void DAC_TLV5618::set_speed(dac_tlv5618_spds spd) { 
  _control.control_bits.SPD = spd ? 1 : 0;
}

///
/// Changes the power control bit
/// 
/// The update occurs on the next write to the DAC.
///
/// \param[in] pwr -- values are NORMAL or POWER_DOWN
///

void DAC_TLV5618::set_power_control(dac_tlv5618_pwrs pwr) {
  _control.control_bits.PWR = pwr ? 1 : 0;
}

