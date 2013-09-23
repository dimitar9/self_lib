#include "table_printer.h"
#include <ostream>
#include <stdio.h>
class TablePrinter;
int main()
{
    std::ostringstream os;
    TablePrinter tp(&os);
    tp.AddColumn("Name", 10);
    tp.PrintHeader();
    tp<<"David" ;
    tp<<"Tom" ;
    tp.PrintFooter();
    printf("%s\n", os.str().c_str());
    return 0;
}
