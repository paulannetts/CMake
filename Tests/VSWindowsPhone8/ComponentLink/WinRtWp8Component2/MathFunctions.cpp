#include "MathFunctions.h"
#include <math.h>

namespace WinRtWp8Component2
{
    double MathsWinRt::Sqrt(double in)
    {
      auto maths1 = ref new WinRtWp8Component1::MathsWinRt();
      auto res = maths1->Sqrt(in);
      return res;
    }
	
    double MathsWinRt::Square(double in)
    {
        return in * in;
    }

}