#include <array>
#include <assert.h>
#include <iostream>
#include <sstream>

class IPv4
{
private:
  std::array<unsigned char, 4> theData;

public:
  constexpr IPv4(): theData{{0}}
  {
  }
  constexpr IPv4(unsigned char aPart0, unsigned char aPart1, unsigned char aPart2, unsigned char aPart3):
    theData{{aPart0, aPart1, aPart2, aPart3}}
  {
  }

  explicit constexpr IPv4(unsigned long aData):
    theData{{static_cast<unsigned char>((aData >> 24) & 0xFF),
             static_cast<unsigned char>((aData >> 16) & 0xFF),
             static_cast<unsigned char>((aData >> 8) & 0xFF),
             static_cast<unsigned char>((aData & 0xFF))}}
  {
  }

  // Copy constructor
  IPv4(const IPv4& aOther) noexcept
  {
    theData = aOther.getData();
  }

  IPv4& operator=(const IPv4& aOther) noexcept
  {
    theData = aOther.getData();
    return *this;
  }

  std::string toString() const
  {
    std::stringstream stream;
    stream << *this;
    return stream.str();
  }

  constexpr unsigned long toUlong() const noexcept
  {
    return (static_cast<unsigned long>(theData[0]) << 24) | (static_cast<unsigned long>(theData[1]) << 16) |
           (static_cast<unsigned long>(theData[2]) << 8) | (static_cast<unsigned long>(theData[3]));
  }

  void setData(std::array<unsigned char, 4>& aData)
  {
    theData = aData;
  }

  std::array<unsigned char, 4> getData() const
  {
    return theData;
  }

  friend std::ostream& operator<<(std::ostream& aOstream, const IPv4& aAddress)
  {
    auto data = aAddress.getData();
    aOstream << static_cast<int>(data[0]) << "." << static_cast<int>(data[1]) << "." << static_cast<int>(data[2]) << "."
             << static_cast<int>(data[3]);

    return aOstream;
  }

  friend std::istream& operator>>(std::istream& aStream, IPv4& aAddress)
  {
    char data1, data2, data3;
    int bit1, bit2, bit3, bit4;

    aStream >> bit1 >> data1 >> bit2 >> data2 >> bit3 >> data3 >> bit4;
    if ((data1 == '.') && (data2 == '.') && (data3 == '.'))
    {
      aAddress = IPv4(bit1, bit2, bit3, bit4);
    }
    else
    {
      aStream.setstate(std::ios::failbit);
    }

    return aStream;
  }
};

int main()
{
  IPv4 address(168, 192, 0, 1);
  std::cout << address << std::endl;

  IPv4 ip;
  std::cout << ip << std::endl;
  std::cin >> ip;

  if (!std::cin.fail())
  {
    std::cout << ip << std::endl;
  }
}