#include <cmath>
#include <iostream>

int main()
{
  int Niteration = 10000;

  float w13 = 0.5, w23 = 0.4, w14 = 0.9, w24 = 1.0, w35 = -1.2, w45 = 1.1;
  float theta3 = 0.8, theta4 = -0.1, theta5 = 0.3;
  float alpha = 0.1;
  float N5Out, N5Err;
  float x1[4]{ 1,0,1,0 };
  float x2[4]{ 1,1,0,0 };
  float goals[4]{ 0,1,1,0 };

  int p = 1; //iteration number

  while (p <= (Niteration - 4))
  {
    float EpocSumErr = 0;
    for (int i = 0; i < 4; i++)
    {
      //Neuron 3
      float N3X = x1[i] * w13 + x2[i] * w23;
      float N3Y = 1 / (1 + exp((-(N3X - theta3))));
      //Neuron 4
      float N4X = x1[i] * w14 + x2[i] * w24;
      float N4Y = 1 / (1 + exp((-(N4X - theta4))));
      //Neuron 5
      float N5X = N3Y * w35 + N4Y * w45;
      float N5Y = 1 / (1 + exp((-(N5X - theta5))));
      //Error Calculation for Neuron 5
      float Err5 = goals[i] - N5Y;
      float Delta5 = N5Y*(1 - N5Y)*Err5;
      float WCurrent35 = w35;
      float WCurrent45 = w45;
      w35 = w35 + alpha * N3Y * Delta5;
      w45 = w45 + alpha * N4Y * Delta5;
      theta5 = theta5 + alpha * (-1) * Delta5;
      //Error Calculation for Neuron 3
      float Delta3 = N3Y*(1 - N3Y)*Delta5*WCurrent35;
      w13 = w13 + alpha * x1[i] * Delta3;
      w23 = w23 + alpha * x2[i] * Delta3;
      theta3 = theta3 + alpha * (-1) * Delta3;
      //Error Calculation for Neuron 4
      float Delta4 = N4Y*(1 - N4Y)*Delta5*WCurrent45;
      w14 = w14 + alpha * x1[i] * Delta4;
      w24 = w24 + alpha * x2[i] * Delta4;
      theta4 = theta4 + alpha * (-1) * Delta4;
      //Recalculate
      float TN3X = x1[i] * w13 + x2[i] * w23;
      float TN3Y = 1 / (1 + exp((-(N3X - theta3))));
      //Neuron 4
      float TN4X = x1[i] * w14 + x2[i] * w24;
      float TN4Y = 1 / (1 + exp((-(N4X - theta4))));
      //Neuron 5
      float TN5X = N3Y * w35 + N4Y * w45;
      float TN5Y = 1 / (1 + exp((-(N5X - theta5))));
      float TErr5 = goals[i] - N5Y;
      N5Err = TErr5;
      N5Out = TN5Y;
      EpocSumErr = EpocSumErr + pow(TErr5, 2);
    }
    if (EpocSumErr < 0.001)
    {
      std::cout << '\n' << "w1-3 " << w13;
      std::cout << '\n' << "w2-3 " << w23;
      std::cout << '\n' << "w1-4 " << w14;
      std::cout << '\n' << "w2-4 " << w24;
      std::cout << '\n' << "w3-5 " << w35;
      std::cout << '\n' << "w4-5 " << w45;
      std::cout << '\n' << '\n' << "Theta 3 - " << theta3;
      std::cout << '\n' << "Theta 4 - " << theta4;
      std::cout << '\n' << "Theta 5 - " << theta5;
      break;
    }
  }

  std::cin.get();

  return 0;
}