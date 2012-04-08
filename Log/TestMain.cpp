#include "Log.h"

using namespace LFC;
using namespace LOG;

int main()
{
	Log::setGobalLevel(LOG_WARNING);
	Log::setLogTarget(LOG_CONSOLE);
	
	Log::e("this is a ERROR Log, lv = %d\n", 5);
	Log::w("this is a WARNING Log, lv = %d\n", 4);
	Log::d("this is a DEBUG Log, lv = %d\n", 3);
	Log::i("this is a INFO Log, lv = %d\n", 2);
	Log::v("this is a VERBOSE Log, lv = %d\n", 1);

	return 0;
}