// RBotFirmware
// Rob Dobson 2016-18

#pragma once

#include "math.h"
#include "RobotConsts.h"

class AxisFloats
{
public:
  float _pt[RobotConsts::MAX_AXES];
  uint8_t _validityFlags;

public:
  AxisFloats()
  {
    clear();
  }
  AxisFloats(const AxisFloats& other)
  {
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      _pt[i] = other._pt[i];
    _validityFlags = other._validityFlags;
  }
  AxisFloats(float x, float y)
  {
    _pt[0]         = x;
    _pt[1]         = y;
    _pt[2]         = 0;
    _validityFlags = 0x03;
  }
  AxisFloats(float x, float y, float z)
  {
    _pt[0]         = x;
    _pt[1]         = y;
    _pt[2]         = z;
    _validityFlags = 0x07;
  }
  AxisFloats(float x, float y, float z, bool xValid, bool yValid, bool zValid)
  {
    _pt[0]          = x;
    _pt[1]          = y;
    _pt[2]          = z;
    _validityFlags  = xValid ? 0x01 : 0;
    _validityFlags |= yValid ? 0x02 : 0;
    _validityFlags |= zValid ? 0x04 : 0;
  }
  void clear()
  {
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      _pt[i] = 0;
    _validityFlags = 0;
  }
  inline float getValNoCk(int axisIdx)
  {
    return _pt[axisIdx];
  }
  float getVal(int axisIdx)
  {
    if (axisIdx >= 0 && axisIdx < RobotConsts::MAX_AXES)
      return _pt[axisIdx];
    return 0;
  }
  void setVal(int axisIdx, float val)
  {
    if (axisIdx >= 0 && axisIdx < RobotConsts::MAX_AXES)
    {
      int axisMask = 0x01 << axisIdx;
      _pt[axisIdx]    = val;
      _validityFlags |= axisMask;
    }
  }
  void set(float val0, float val1, float val2 = 0)
  {
    _pt[0]         = val0;
    _pt[1]         = val1;
    _pt[2]         = val2;
    _validityFlags = 0x07;
  }
  void setValid(int axisIdx, bool isValid)
  {
    if (axisIdx >= 0 && axisIdx < RobotConsts::MAX_AXES)
    {
      int axisMask = 0x01 << axisIdx;
      if (isValid)
        _validityFlags |= axisMask;
      else
        _validityFlags &= ~axisMask;
    }
  }
  bool isValid(int axisIdx)
  {
    if (axisIdx >= 0 && axisIdx < RobotConsts::MAX_AXES)
    {
      int axisMask = 0x01 << axisIdx;
      return (_validityFlags & axisMask) != 0;
    }
    return false;
  }
  bool anyValid()
  {
    return (_validityFlags != 0);
  }
  float X()
  {
    return _pt[0];
  }
  void X(float val)
  {
    _pt[0]          = val;
    _validityFlags |= 0x01;
  }
  float Y()
  {
    return _pt[1];
  }
  void Y(float val)
  {
    _pt[1]          = val;
    _validityFlags |= 0x02;
  }
  float Z()
  {
    return _pt[2];
  }
  void Z(float val)
  {
    _pt[2]          = val;
    _validityFlags |= 0x04;
  }
  void operator=(const AxisFloats& other)
  {
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      _pt[i] = other._pt[i];
    _validityFlags = other._validityFlags;
  }
  AxisFloats operator-(const AxisFloats& pt)
  {
    AxisFloats result;
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      result._pt[i] = _pt[i] - pt._pt[i];
    return result;
  }
  AxisFloats operator-(float val)
  {
    AxisFloats result;
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      result._pt[i] = _pt[i] - val;
    return result;
  }
  AxisFloats operator+(const AxisFloats& pt)
  {
    AxisFloats result;
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      result._pt[i] = _pt[i] + pt._pt[i];
    return result;
  }
  AxisFloats operator+(float val)
  {
    AxisFloats result;
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      result._pt[i] = _pt[i] + val;
    return result;
  }
  AxisFloats operator/(const AxisFloats& pt)
  {
    AxisFloats result;
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
    {
      if (pt._pt[i] != 0)
        result._pt[i] = _pt[i] / pt._pt[i];
    }
    return result;
  }
  AxisFloats operator/(float val)
  {
    AxisFloats result;
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
    {
      if (val != 0)
        result._pt[i] = _pt[i] / val;
    }
    return result;
  }
  AxisFloats operator*(const AxisFloats& pt)
  {
    AxisFloats result;
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
    {
      result._pt[i] = _pt[i] * pt._pt[i];
    }
    return result;
  }
  AxisFloats operator*(float val)
  {
    AxisFloats result;
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
    {
      result._pt[i] = _pt[i] * val;
    }
    return result;
  }
  float distanceTo(const AxisFloats& pt, bool includeDist[] = NULL)
  {
    float distSum = 0;
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
    {
      if ((includeDist == NULL) || includeDist[i])
      {
        float sq = _pt[i] - pt._pt[i];
        sq       = sq * sq;
        distSum += sq;
      }
    }
    return sqrt(distSum);
  }
  void logDebugStr(const char* prefixStr)
  {
    Log.trace("%s X %0.2f Y %0.2f Z %0.2f", prefixStr, _pt[0], _pt[1], _pt[2]);
  }
  String toJSON()
  {
    String jsonStr;
    if (RobotConsts::MAX_AXES >= 2)
    {
      jsonStr = "\"X\":" + String::format("%0.3f", _pt[0]) +
                ",\"Y\":" + String::format("%0.3f", _pt[1]);
    }
    if (RobotConsts::MAX_AXES >= 3)
    {
      jsonStr += ",\"Z\":" + String::format("%0.3f", _pt[2]);
    }
    return "{" + jsonStr + "}";
  }
};

class AxisValidBools
{
public:
  struct BoolBitValues
  {
    bool bX : 1;
    bool bY : 1;
    bool bZ : 1;
  };
  union
  {
    BoolBitValues _bits;
    uint16_t _uint;
  };

public:
  AxisValidBools()
  {
    _uint = 0;
  }
  AxisValidBools(const AxisValidBools& other)
  {
    _uint = other._uint;
  }
  void operator=(const AxisValidBools& other)
  {
    _uint = other._uint;
  }
  bool isValid(int axisIdx)
  {
    return _uint & (1 << axisIdx);
  }
  AxisValidBools(bool xValid, bool yValid, bool zValid)
  {
    _uint = 0;
    _bits.bX = xValid;
    _bits.bY = yValid;
    _bits.bZ = zValid;
  }
  bool XValid()
  {
    return _bits.bX;
  }
  bool YValid()
  {
    return _bits.bY;
  }
  bool ZValid()
  {
    return _bits.bZ;
  }
  bool operator[](int boolIdx)
  {
    return isValid(boolIdx);
  }
  void setVal(int boolIdx, bool val)
  {
    if (val)
      _uint |= (1 << boolIdx);
    else
      _uint &= (0xffff ^ (1 << boolIdx));
  }
};

class AxisMinMaxBools
{
public:
  static constexpr int MIN_MAX_VALID_BIT = 31;

  static constexpr int MIN_MAX_VALUES_MASK = 0x3fffffff;

  static constexpr int MIN_VAL_IDX = 0;
  static constexpr int MAX_VAL_IDX = 1;

  static constexpr int VALS_PER_AXIS = RobotConsts::MAX_ENDSTOPS_PER_AXIS;
  static constexpr int BITS_PER_VAL = 2;
  static constexpr int BITS_PER_VAL_MASK = 0x03;

  enum AxisMinMaxEnum {
    END_TEST_NONE = 0,
    END_STOP_NONE = 0,
    END_TEST_HIT = 1,
    END_STOP_HIT = 1,
    END_TEST_NOT_HIT = 2,
    END_STOP_NOT_HIT = 2
  };

  uint32_t _uint;

public:
  AxisMinMaxBools()
  {
    _uint = 0;
  }
  AxisMinMaxBools(const AxisMinMaxBools& other)
  {
    _uint = other._uint;
  }
  void operator=(const AxisMinMaxBools& other)
  {
    _uint = other._uint;
  }
  bool isValid()
  {
    return _uint & (1 << MIN_MAX_VALID_BIT);
  }
  void set(int axisIdx, int endStopIdx, AxisMinMaxEnum checkType)
  {
    int valIdx = (axisIdx * VALS_PER_AXIS + endStopIdx) * BITS_PER_VAL;
    uint32_t valMask = (BITS_PER_VAL_MASK << valIdx);
    _uint &= (valMask ^ 0xffffffff);
    _uint |= checkType << valIdx;
    _uint |= (1 << MIN_MAX_VALID_BIT);
  }
  AxisMinMaxEnum get(int axisIdx, int endStopIdx)
  {
    int valIdx = (axisIdx * VALS_PER_AXIS + endStopIdx) * BITS_PER_VAL;
    return (AxisMinMaxEnum)((_uint >> valIdx) & BITS_PER_VAL_MASK);
  }
  void none()
  {
    _uint = 0;
  }
  void all()
  {
    uint32_t newUint = 0;
    for (int axisIdx = 0; axisIdx < RobotConsts::MAX_AXES; axisIdx++)
    {
      newUint = newUint << (VALS_PER_AXIS * BITS_PER_VAL);
      for (int valIdx = 0; valIdx < VALS_PER_AXIS; valIdx++)
        newUint |= END_TEST_HIT << (valIdx * BITS_PER_VAL);
    }
    _uint = newUint |= (1 << MIN_MAX_VALID_BIT);
  }
  bool any()
  {
    if (isValid())
      return (_uint & MIN_MAX_VALUES_MASK) != 0;
    return false;
  }
  uint32_t uintVal()
  {
    return _uint;
  }
};

class AxisInt32s
{
public:
  int32_t vals[RobotConsts::MAX_AXES];

public:
  AxisInt32s()
  {
    clear();
  }
  AxisInt32s(const AxisInt32s& u32s)
  {
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      vals[i] = u32s.vals[i];
  }
  void operator=(const AxisInt32s& u32s)
  {
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      vals[i] = u32s.vals[i];
  }
  AxisInt32s(int32_t xVal, int32_t yVal, int32_t zVal)
  {
    vals[0] = xVal;
    vals[1] = yVal;
    vals[2] = zVal;
  }
  void clear()
  {
    for (int i = 0; i < RobotConsts::MAX_AXES; i++)
      vals[i] = 0;
  }
  void set(int32_t val0, int32_t val1, int32_t val2 = 0)
  {
    vals[0] = val0;
    vals[1] = val1;
    vals[2] = val2;
  }
  int32_t X()
  {
    return vals[0];
  }
  int32_t Y()
  {
    return vals[1];
  }
  int32_t Z()
  {
    return vals[2];
  }
  int32_t getVal(int axisIdx)
  {
    if (axisIdx >= 0 && axisIdx < RobotConsts::MAX_AXES)
      return vals[axisIdx];
    return 0;
  }
  void setVal(int axisIdx, int32_t val)
  {
    if (axisIdx >= 0 && axisIdx < RobotConsts::MAX_AXES)
      vals[axisIdx] = val;
  }
  String toJSON()
  {
    String jsonStr;
    if (RobotConsts::MAX_AXES >= 2)
    {
      jsonStr = "\"X\":" + String::format("%ld", vals[0]) +
                ",\"Y\":" + String::format("%ld", vals[1]);
    }
    if (RobotConsts::MAX_AXES >= 3)
    {
      jsonStr += ",\"Z\":" + String::format("%ld", vals[2]);
    }
    return "{" + jsonStr + "}";
  }
};
