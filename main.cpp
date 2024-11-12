#include <iostream>
#include <string>
#include <vector>
bool isLeapYear(int year) {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int getDaysInMonth(int month, int year) {
  if (month == 2) {
    return isLeapYear(year) ? 29 : 28;
  }
  return (month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31;
}

int getStartDay(int month, int year) {
  int total_days = 0;

  for (int i = 1919; i < year; i++) {
    total_days += isLeapYear(i) ? 366 : 365;
  }

  for (int i = 1; i < month; i++) {
    total_days += getDaysInMonth(i, year);
  }

  int ans = (3 + total_days) % 7;
  return ans == 0 ? 7 : ans;  // 1 января 1919 года — среда
}

void DisplayMonth(size_t month, size_t year) {
  int day = getStartDay(month, year);
  static std::vector<std::string> months = {" ", "январь", "февраль", "март", "апрель", "май", "июнь", "июль",
                                            "август", "сентябрь", "октябрь", "ноябрь", "декабрь"};
  std::cout << months[month] << " " << year << std::endl;
  std::cout << "ПН ВТ СР ЧТ ПТ СБ ВС" << std::endl;
  for (int i = 1; i < day; i++) std::cout << "   ";

  for (int i = 1; i <= getDaysInMonth(month, year); i++) {
    if (i < 10) {
      std::cout << " ";
    }
    std::cout << i;
    if ((i + day - 1) % 7 == 0) {
      std::cout << std::endl;
      continue;
    }
    std::cout << " ";
  }
  std::cout << std::endl;
}

void DisplayInterval(size_t month_s, size_t year_s, size_t month_e, size_t year_e) {
  if (year_s > year_e) {
    std::cout << "ВЫ убили чернокожего";
    return;
  }
  if (year_s == year_e && month_s >= month_e) {
    std::cout << "ВЫ посадили Дурова";
    return;
  }
  size_t days_count = 0;
  while (month_s != month_e || year_s != year_e) {
    days_count += getDaysInMonth(month_s, year_s);
    month_s++;
    if (month_s == 13) {
      month_s = 1;
      year_s++;
    }
  }
  std::cout << days_count;
}

int main() {
  std::string mama;
  std::getline(std::cin, mama);
  std::vector<size_t> args;
  std::string elem;
  for (auto s : mama) {
    if (s == ' ') {
      if (elem.empty()) {
        continue;
      }
      args.push_back(std::atoi(elem.c_str()));
      elem.clear();
      continue;
    }
    elem.push_back(s);
  }
  args.push_back(std::atoi(elem.c_str()));
  if (args.size() != 2 && args.size() != 4) {
    std::cout << "GOOOOOOOOOOAL";
    return 0;
  }

  if (args.size() == 2) {
    if (args[1] < 1919 || args[1] > 2169) {
      std::cout << "ABOBA";
      return 0;
    }
    DisplayMonth(args[0], args[1]);
    return 0;
  }
  if (args[1] < 1919 || args[1] > 2169 || args[3] < 1919 || args[3] > 2169) {
    std::cout << "ABOBA";
    return 0;
  }
  DisplayInterval(args[0], args[1], args[2], args[3]);
  return 0;
}