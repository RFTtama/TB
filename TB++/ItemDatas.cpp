#include "ItemClass.h"
#include "TBdefine.h"
#include <string.h>

ItemClass* ItemPtr = new ItemClass[ITEMNUM];

void InitItems(void) {
	strcpy_s((ItemPtr + 0)->name, "奇妙な石");
	strcpy_s((ItemPtr + 0)->description, "奇妙な力を受けて震えている。 水切りをするには手ごろな形。");
}