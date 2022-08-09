#include "ItemClass.h"
#include "TBdefine.h"
#include <string.h>

ItemClass* ItemPtr = new ItemClass[ITEMNUM];

void InitItems(void) {
	strcpy_s((ItemPtr + 0)->name, "Šï–­‚ÈÎ");
	strcpy_s((ItemPtr + 0)->description, "Šï–­‚È—Í‚ğó‚¯‚Äk‚¦‚Ä‚¢‚éB …Ø‚è‚ğ‚·‚é‚É‚Íè‚²‚ë‚ÈŒ`B");
}