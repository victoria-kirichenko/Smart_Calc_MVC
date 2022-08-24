#include "model.h"

#include <stdlib.h>

#include <iostream>

using namespace s21;

Model::Model() { data_ = 0.0; }

double Model::get_data() { return data_; }

double Model::calculate(string& str, double x) {
  valid(str);
  string for_num;
  std::size_t len = 0, i = 0, str_len = str.length();
  // what are fuck? vector? why not?
  stack<double> Num;
  stack<char> Sim;

  while (i != str_len) {
    if ((str[i] <= '9' && str[i] >= '0') || str[i] == '.' || str[i] == 'e') {
      for_num = str.substr(i);
      Num.push(GetNumAndLen(for_num, &len));
      i += (int)len;
    } else {
      char ch = str[i];
      if (ch == ')') {
        IfClosedBracket(Num, Sim);
      } else if (Sim.empty()) {
        IfUnarWhenStackNumIsEmpty(Num, Sim, ch, x);
      } else if (prior(ch) > prior(Sim.top()) || ch == '(' || ch == 'x') {
        IfUnarWhenStackNumIsFill(Num, Sim, ch, x, str[i - 1]);
      } else {
        IfSimInputLessOrEgual(Num, Sim, ch);
      }
      i++;
    }
  }
  while (!Sim.empty()) {
    (prior(Sim.top()) == 4) ? CalculateNumOne(&Num, &Sim)
                            : CalculateNumTwo(&Num, &Sim);
  }
  data_ = Num.top();
  Num.pop();
  return data_;
}

double Model::GetNumAndLen(string str, std::size_t* len) {
  double num;
  *len = 0;
  if (str[0] == 'e') {
    str.insert(0, 1, '1');
    num = std::stod(str, len);
    *len -= 1;
  } else {
    num = std::stod(str, len);
  }
  return num;
}

void Model::IfClosedBracket(stack<double>& Num, stack<char>& Sim) {
  if (prior(Sim.top()) == 4) Sim.push('(');
  if (Sim.top() == '(') {
    Sim.pop();
    if (!Sim.empty() && prior(Sim.top()) == 4) {
      CalculateNumOne(&Num, &Sim);
    }
  } else {
    while (Sim.top() != '(') {
      CalculateNumTwo(&Num, &Sim);
    }
    Sim.pop();
  }
}

void Model::IfUnarWhenStackNumIsEmpty(stack<double>& Num, stack<char>& Sim,
                                      const char& ch, const double& x) {
  if (Num.empty() && prior(ch) == 1) {
    Num.push(0.0);
  }
  (ch == 'x') ? Num.push(x) : Sim.push(ch);
}

void Model::IfUnarWhenStackNumIsFill(stack<double>& Num, stack<char>& Sim,
                                     const char& ch, const double& x,
                                     const char& prev) {
  if (prior(ch) == 1 && prev == '(') {
    Num.push(0.0);
  }
  (ch == 'x') ? Num.push(x) : Sim.push(ch);
}

void Model::IfSimInputLessOrEgual(stack<double>& Num, stack<char>& Sim,
                                  const char& ch) {
  if (prior(Sim.top()) == 3 && prior(ch) == 3) {
  } else {
    while (!Sim.empty() && prior(ch) <= prior(Sim.top())) {
      (prior(Sim.top()) == 4) ? CalculateNumOne(&Num, &Sim)
                              : CalculateNumTwo(&Num, &Sim);
    }
  }
  Sim.push(ch);
}

void Model::CalculateNumOne(stack<double>* Num, stack<char>* Sim) {
  double temp_num = Num->top();
  Num->pop();
  Num->push(OperationOne(temp_num, Sim->top()));
  Sim->pop();
}

void Model::CalculateNumTwo(stack<double>* Num, stack<char>* Sim) {
  double a, b;
  b = Num->top();
  Num->pop();
  a = Num->top();
  Num->pop();
  Num->push(OperationTwo(a, b, Sim->top()));
  Sim->pop();
}

double Model::OperationOne(double& a, int sim) {
  double (*arr[117])(double);
  arr[115] = &sin;
  arr[99] = &cos;
  arr[116] = &tan;
  arr[113] = &SqrtOperation;
  arr[105] = &AsinOperation;
  arr[111] = &AcosOperation;
  arr[97] = &atan;
  arr[108] = &LogOperation;
  arr[110] = &LnOperation;
  return arr[sim](a);
}

double Model::OperationTwo(double& a, double& b, int sim) {
  double (*arr[110])(double, double);
  arr[43] = &SumOperation;
  arr[45] = &SubOperation;
  arr[42] = &MulOperation;
  arr[47] = &DivOperation;
  arr[94] = &pow;
  arr[109] = &ModOperation;
  return arr[sim](a, b);
}

double Model::SqrtOperation(double a) {
  if (a < 0) {
    throw std::invalid_argument("Error! In Sqrt negative value.");
  }
  return sqrt(a);
}

double Model::AsinOperation(double a) {
  if (a > 1 || a < -1) {
    throw std::invalid_argument("Error! Invalid value for asin.");
  }
  return asin(a);
}

double Model::AcosOperation(double a) {
  if (a > 1 || a < -1) {
    throw std::invalid_argument("Error! Invalid value for acos.");
  }
  return acos(a);
}

double Model::LogOperation(double a) {
  if (a <= 0) {
    throw std::invalid_argument("Error! Invalid value for log.");
  }
  return log10(a);
}

double Model::LnOperation(double a) {
  if (a <= 0) {
    throw std::invalid_argument("Error! Invalid value for ln.");
  }
  return log(a);
}

double Model::SumOperation(double a, double b) { return a + b; }

double Model::SubOperation(double a, double b) { return a - b; }

double Model::MulOperation(double a, double b) { return a * b; }

double Model::DivOperation(double a, double b) { return a / b; }

double Model::ModOperation(double a, double b) {
  if (b == 0) {
    throw std::invalid_argument("Error! Divided by zero.");
  }
  return fmod(a, b);
}

int Model::prior(char sim) {
  int prior;
  if (sim == '(' || sim == 'x') {
    prior = 0;
  } else if (sim == '+' || sim == '-') {
    prior = 1;
  } else if (sim == '*' || sim == '/' || sim == 'm') {
    prior = 2;
  } else if (sim == '^') {
    prior = 3;
  } else {
    prior = 4;
  }
  return prior;
}

void Model::valid(const string& str) {
  int bracket = 0, i = 0;
  while (str[i] != '\0') {
    if (str[i] == ')') {
      bracket--;
    }
    if (bracket < 0) {
      throw std::invalid_argument("Incorrect Input!");
    }
    if (str[i] == '(') {
      bracket++;
    }
    i++;
  }
  if (bracket != 0) {
    throw std::invalid_argument("Incorrect Input!");
  }
}

std::pair<std::vector<double>, std::vector<double>> Model::graph(
    string& str, std::vector<double>& data) {
  double h = data.back();
  data.pop_back();
  double x_min = data.back();
  data.pop_back();
  double x_max = data.back();
  data.pop_back();
  data.pop_back();
  data.pop_back();
  double X;
  std::pair<std::vector<double>, std::vector<double>> res;
  for (X = x_min; X <= x_max; X += h) {
    res.first.push_back(X);
    calculate(str, X);
    res.second.push_back(data_);
  }
  return res;
}
