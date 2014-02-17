// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MathFunctionsStaticLib.h"
 
namespace WinRtTopLevelComponent
{
  public ref class TheComponent sealed
  {
  public:
    int Main()
    {
      double inputValue = 247.23;
      auto math = ref new WinRtWp8Component1::MathsWinRt();
      auto math2 = ref new WinRtWp8Component2::MathsWinRt();
      auto outputValue1 = PowerOf3(inputValue);
      double outputValue2 = math->Sqrt(inputValue);
      double outputValue3 = math2->Square(inputValue);

      fprintf(stdout, "The square root of %g is %g\n",
        inputValue, outputValue2);
      return 0;
    }
  };
}
