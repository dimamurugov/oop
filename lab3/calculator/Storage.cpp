//#include <iostream>
//#include <limits>
//#include "Storage.h"
//
//double Storage::getValue(const std::string &identifier) {
//    if (m_variables.count(identifier)) {
//        return m_variables[identifier];
//    }
//    return std::numeric_limits<double>::quiet_NaN();
//}
//
//void Storage::AddVariables(const std::string &identifier, double value) {
//    m_variables[identifier] = value;
//}
//
//void Storage::AddFunction(std::string identifier, Function* function) {
//    m_functions[identifier] = function;
//}
//
////void Storage::Print(MapType type) {
////    if (type == MapType::VARIABLES)
////    {
////        for(auto iter{m_variables.begin()}; iter != m_variables.end(); iter++)
////        {
////            std::cout << iter->first << ": " << iter->second << std::endl;
////        }
////    }
////    else
////    {
////        for(auto iter{m_functions.begin()}; iter != m_functions.end(); iter++)
////        {
////            std::cout << iter->first << ": " << iter->second.getValue() << std::endl;
////        }
////    }
////}
