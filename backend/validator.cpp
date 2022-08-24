#include "validator.h"

#include <iostream>

using namespace s21;

QString Validator::CheckNumber(const QString& str, const QString& num) {
  QString temp = str;
  if ((temp.endsWith("0") && temp.length() == 1) || temp.contains("!")) {
    temp.clear();
    temp.insert(0, num);
    lexeme.clear();
    lexeme.push_back(num);
  } else if (num == '0' && !(temp.endsWith("/")) && !(temp.endsWith("x")) &&
             !(temp.endsWith(")"))) {
    temp.append(num);
    lexeme.push_back(num);
  } else if (num != '0') {
    if (!(temp.endsWith("x")) && !(temp.endsWith(")"))) {
      temp.append(num);
      lexeme.push_back(num);
    }
  }
  return temp;
}

QString Validator::CheckUnar(const QString& str) {
  QString temp = str;
  if (!temp.startsWith('0') && !(temp.length() == 0)) {
    (temp.startsWith("-")) ? temp.remove(0, 1) : temp.insert(0, "-");
  }
  return temp;
}

QString Validator::CheckInputTrigonometry(const QString& str, const char* ban,
                                          const QString& input) {
  QString temp = str;
  string label = str.toStdString();
  if (label[0] != '0' && label.length() > 0 && !temp.contains("!")) {
    if (input == "e+" || input == "e-") {
      if (temp.endsWith("e+") || temp.endsWith("e-")) {
        return temp;
      }
      for (int i = lexeme.size() - 1; i >= 0; --i) {
        if (lexeme[i] == "e+" || lexeme[i] == "e-") return temp;
        if ((lexeme[i] > '9' || lexeme[i] < '0') && lexeme[i] != '.') break;
      }
    }
    if (!strchr(ban, label[label.length() - 1])) {
      temp.append(input);
      lexeme.push_back(input);
    }
  } else {
    temp.clear();
    temp.insert(0, input);
    lexeme.clear();
    lexeme.push_back(input);
  }
  return temp;
}

QString Validator::CheckInputOperations(const QString& str,
                                        const QString& input) {
  QString temp = str;
  string label = str.toStdString();
  if (!(temp.contains("!")) && !(temp.endsWith(input)) &&
      (!(temp.startsWith("0")) || temp.length() > 1)) {
    if (input == "-") {
      if (!strchr("^+-*/.nsgd", label[label.length() - 1])) {
        temp.append(input);  // mod?
        lexeme.push_back(input);
      }
    } else {
      if (!strchr("(^+-*/.nsgd", label[label.length() - 1])) {
        temp.append(input);
        lexeme.push_back(input);
      }
    }
  }
  return temp;
}

QString Validator::CheckDelete(const QString& label) {
  QString temp = label;
  if (lexeme.isEmpty()) {
    temp.clear();
    temp.insert(0, "0");
    return temp;
  }
  temp.truncate(temp.length() - lexeme.back().length());
  lexeme.pop_back();
  if (lexeme.isEmpty()) temp.insert(0, "0");
  return temp;
}

void Validator::CheckX(const QString& x, int check) {
  string ch =
      "abcdfghijklmnopqrstuvwxyzабвгдёжзийклмнопрстуфхцчшщъыьэюя?&%$#@^*/,";
  string x_str = x.toLower().toStdString();
  int e = 0, minus = 0, plus = 0;
  for (size_t i = 0, len = x_str.length(); i < len; ++i) {
    for (size_t j = 0, len2 = ch.length(); j < len2; ++j) {
      if (x_str[i] == ch[j]) {
        throw std::logic_error("The value must be a number!");
      }
    }
    if (check == 2 && x_str[i] == 'e')
      throw std::logic_error("The number cannot be in exponential notation!");
    if (x_str[i] == 'e') e++;
    if (x_str[i] == '-') minus++;
    if (x_str[i] == '+') plus++;
  }
  if (e > 1 || (x_str[0] != '-' && minus > 1) || plus > 1 || minus > 2) {
    throw std::logic_error("The value must be a number!");
  }
  if ((check == 1 || check == 2) && x_str[0] == '-')
    throw std::logic_error("The value must be a positive number!");
}

void Validator::CheckInput(const QString& str) {
  string label = str.toStdString();
  if (strchr("-+*/^d.(nsg", label[label.length() - 1]) ||
      strchr("(", label[label.length() - 2])) {
    throw std::logic_error("Incorrect Input!");
  }
}

QString Validator::CheckDot(const QString& str) {
  QString temp = str;
  string label = str.toStdString();
  if (!strchr("(^+-*/.nsgd", label[label.length() - 1])) {
    int len = (int)temp.length() - 2;
    for (len; len >= 0; --len) {
      if (strchr("(^+-*/nsgd", label[len])) break;
      if (str[len] == '.') return temp;
    }
    temp.append(".");
    lexeme.push_back(".");
  }
  return temp;
}

void Validator::CheckCredit(const double& credit_sum_,
                            const double& credit_period_,
                            const double& interest_rate_) {
  if (credit_sum_ <= 0.0 || credit_period_ < 1 || interest_rate_ < 0.01) {
    throw std::invalid_argument("Incorrect Input!");
  }
}

string Validator::converter(QString& str) {
  int cnt = 0;
  while (cnt != 20) {
    str = RemovePartOfStr(str, "asin", 3, 1, 2);
    str = RemovePartOfStr(str, "acos", 3, 1, 2);
    str = RemovePartOfStr(str, "atan", 1, 3, 3);
    str = RemovePartOfStr(str, "mod", 1, 2, 3);
    str = RemovePartOfStr(str, "sin", 1, 2, 3);
    str = RemovePartOfStr(str, "cos", 1, 2, 3);
    str = RemovePartOfStr(str, "tan", 1, 2, 3);
    str = RemovePartOfStr(str, "sqrt", 2, 2, 1);
    str = RemovePartOfStr(str, "ln", 0, 0, 1);
    str = RemovePartOfStr(str, "log", 1, 2, 3);
    cnt++;
  }
  return str.toStdString();
}

QString Validator::RemovePartOfStr(const QString& str, const QString& del,
                                   int a, int b, int c) {
  QString label = str;
  int idx = label.indexOf(del);
  if (idx == -1) return label;
  if (a != 0 && b != 0) label.remove(idx + a, b);
  if (c != 3) label.remove(idx, c);
  return label;
}
