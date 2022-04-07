/**
 * @file logger.hpp
 * @brief 
 * @author lijiaqi (lijiaqi5@xiaomi.com)
 * 
 * @copyright Copyright (c) 2022  xiaomi.com
 * 
 * @par Modify log:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2022-04-07 <td>1.0     <td>lijiaqi     <td>Initial
 * </table>
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>

#include "parser/parser.hpp"

class Logger : public parser::ILogger {
 public:
  explicit Logger(QWidget* obj) : mObj(obj) {}

 public:
  void log(parser::LogLevel level, std::string msg) override {
    switch (level) {
      case parser::LogLevel::kVERBOSE:
      case parser::LogLevel::kDEBUG:
      case parser::LogLevel::kINFO:
        qDebug() << msg.c_str();
        break;
        // case parser::LogLevel::kINFO:
        //     QMessageBox::information(mObj, "Info", msg.c_str());
        break;
      case parser::LogLevel::kWARNING:
      case parser::LogLevel::kERROR:
        QMessageBox::warning(mObj, "Warning", msg.c_str());
        break;
      // case parser::LogLevel::kERROR:
      //     QMessageBox::critical(mObj, "Error", msg.c_str());
      //     break;
      default:
        break;
    }
  }

 private:
  QWidget* mObj;
};

#endif  // LOGGER_HPP_
