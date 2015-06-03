#include "Csv.h" 
#include <fstream>
using namespace std;

namespace QuantDigger {
namespace Util {
    

std::istream& operator>>(std::istream& str,CSVRow& data)
{
    data.readNextRow(str);
    return str;
} 

} /* Util */
}; /* QuantDigger */
